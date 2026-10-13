#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <math.h>
// PaperRobotV2：复用V1去抖、上升沿、有限速动作和OLED容错。
// 先拆下舵盘/空载测试！启动即输出中位；软件无法保证未知机械中位安全。
namespace Config {
constexpr uint8_t SDA_PIN=0, SCL_PIN=1, YAW_PIN=4, PITCH_PIN=5;
constexpr uint8_t LEFT_IR_PIN=6, RIGHT_IR_PIN=7, TOUCH_PIN=10;
constexpr bool IR_ACTIVE_HIGH=false, TOUCH_ACTIVE_HIGH=true;
constexpr bool SERVOS_ENABLED=true, CALIBRATION_ONLY=false;
constexpr bool IDLE_RANDOM=true;
constexpr int YAW_HOME=90, YAW_MIN=80, YAW_MAX=100, YAW_DIRECTION=1;
constexpr int PITCH_HOME=90, PITCH_MIN=82, PITCH_MAX=98, PITCH_DIRECTION=1;
constexpr int YAW_LOOK=10, PITCH_NOD=6;
constexpr int GAZE_LOOK_PX=10;
// Centered face bounds including blink/transitions: x=25..104.
// Default +/-10 gives x=15..114, safely inside 128 pixels.
static_assert(GAZE_LOOK_PX>=0 && GAZE_LOOK_PX<=23,"Face offset exceeds OLED bounds");
constexpr uint32_t IDLE_GLANCE_MS=550;
constexpr uint32_t DEBOUNCE_MS=40, SERVO_TICK_MS=20, FRAME_MS=40;
constexpr uint32_t HAPPY_MS=1800, TOUCH_COOLDOWN_MS=2200, SLEEP_AFTER_MS=45000;
constexpr int PULSE_MIN_US=1000, PULSE_MAX_US=2000;
constexpr uint32_t OLED_STARTUP_MS=300, OLED_RETRY_MS=1000, OLED_HEALTH_MS=2000;
constexpr uint32_t OLED_HELLO_MS=1500, OLED_CLOCK_HZ=400000;
constexpr uint8_t OLED_ROTATION=0; // 0 normal; 2 rotates 180 degrees.
}
using namespace Config;
static_assert(0<=YAW_MIN && YAW_MIN<=YAW_HOME && YAW_HOME<=YAW_MAX && YAW_MAX<=180,"Yaw limits");
static_assert(0<=PITCH_MIN && PITCH_MIN<=PITCH_HOME && PITCH_HOME<=PITCH_MAX && PITCH_MAX<=180,"Pitch limits");
static_assert((YAW_DIRECTION==1 || YAW_DIRECTION==-1) && (PITCH_DIRECTION==1 || PITCH_DIRECTION==-1),"Direction +/-1");
class StableInput {
 public:
  uint8_t pin; bool high, raw=false, stable=false; uint32_t changed=0;
  StableInput(uint8_t p,bool h):pin(p),high(h) {}
  void begin(uint32_t now) {
    pinMode(pin,high ? INPUT : INPUT_PULLUP);
    raw=stable=(digitalRead(pin)==(high ? HIGH : LOW)); changed=now;
  }
  bool update(uint32_t now) {
    bool sample=(digitalRead(pin)==(high ? HIGH : LOW));
    if(sample!=raw) { raw=sample; changed=now; }
    if(raw!=stable && uint32_t(now-changed)>=DEBOUNCE_MS) {
      stable=raw; return stable;
    }
    return false;
  }
};
// 类方法避免Arduino自动原型对自定义类型的处理问题。
class Axis {
 public:
  Servo servo; int home,lo,hi,dir,current,target;
  Axis(int h,int l,int u,int d):home(h),lo(l),hi(u),dir(d),current(h),target(h) {}
  void aim(float offset) { target=constrain(home+int(lroundf(dir*offset)),lo,hi); }
  void step() {
    if(current<target) ++current; else if(current>target) --current;
    servo.write(constrain(current,lo,hi));
  }
  bool begin(uint8_t pin) {
    servo.setPeriodHertz(50); servo.attach(pin,PULSE_MIN_US,PULSE_MAX_US);
    if(servo.attached()) { servo.write(home); return true; }
    return false;
  }
};
StableInput leftIR(LEFT_IR_PIN,IR_ACTIVE_HIGH), rightIR(RIGHT_IR_PIN,IR_ACTIVE_HIGH), touch(TOUCH_PIN,TOUCH_ACTIVE_HIGH);
Axis yaw(YAW_HOME,YAW_MIN,YAW_MAX,YAW_DIRECTION), pitch(PITCH_HOME,PITCH_MIN,PITCH_MAX,PITCH_DIRECTION);
Adafruit_SSD1306 display(128,64,&Wire,-1,OLED_CLOCK_HZ,OLED_CLOCK_HZ);
bool oledOK=false, servosOK=false, happy=false, touchedOnce=false, blinking=false;
uint32_t lastServo=0,lastFrame=0,happyStart=0,lastTouch=0,lastActivity=0;
uint32_t blinkStart=0,blinkWaitStart=0,blinkWait=3000,idleStart=0,idleWait=2500;
uint32_t oledBoot=0,oledLastAttempt=0,oledLastHealth=0,oledLastReport=0;
bool oledAttempted=false, oledHello=false;
uint32_t oledHelloStart=0, oledFrames=0, oledLastFrameReport=0;
uint8_t oledLastError=255;
int sensedBefore=0,idleMood=0; // 0正常、1好奇、2害羞
float faceOffsetX=0, targetFaceOffsetX=0;
float gazeY=0,targetGazeY=0;
bool idleGlancing=false;
uint32_t idleGlanceStart=0;
int idleGlanceDirection=1;

// OLED服务：启动留300ms电源稳定时间；失败不会永久关闭绘图。
// 所有等待用millis调度。begin/display仍有有限I2C传输开销。
uint8_t oledProbe(uint8_t address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission();
}
void serviceOLED(uint32_t now) {
  if(uint32_t(now-oledBoot)<OLED_STARTUP_MS) return;
  if(oledOK) {
    if(uint32_t(now-oledLastHealth)<OLED_HEALTH_MS) return;
    oledLastHealth=now;
    oledLastError=oledProbe(0x3C);
    if(oledLastError==0) return;