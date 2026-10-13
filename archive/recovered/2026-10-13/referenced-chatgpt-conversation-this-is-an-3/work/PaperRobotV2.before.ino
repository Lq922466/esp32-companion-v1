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
constexpr uint32_t DEBOUNCE_MS=40, SERVO_TICK_MS=20, FRAME_MS=40;
constexpr uint32_t HAPPY_MS=1800, TOUCH_COOLDOWN_MS=2200, SLEEP_AFTER_MS=45000;
constexpr int PULSE_MIN_US=1000, PULSE_MAX_US=2000;
constexpr uint32_t OLED_STARTUP_MS=300, OLED_RETRY_MS=1000, OLED_HEALTH_MS=2000;
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
Adafruit_SSD1306 display(128,64,&Wire,-1);
bool oledOK=false, servosOK=false, happy=false, touchedOnce=false, blinking=false;
uint32_t lastServo=0,lastFrame=0,happyStart=0,lastTouch=0,lastActivity=0;
uint32_t blinkStart=0,blinkWaitStart=0,blinkWait=3000,idleStart=0,idleWait=2500;
uint32_t oledBoot=0,oledLastAttempt=0,oledLastHealth=0,oledLastReport=0;
bool oledAttempted=false;
uint8_t oledLastError=255;
int sensedBefore=0,idleMood=0; // 0正常、1好奇、2害羞
float gazeX=0,gazeY=0,targetGazeX=0,targetGazeY=0;

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
    oledOK=false; oledLastAttempt=now; oledAttempted=true;
    Serial.printf("OLED lost: addr=0x3C, I2C error=%u; retrying\n",oledLastError);
    return;
  }
  if(oledAttempted && uint32_t(now-oledLastAttempt)<OLED_RETRY_MS) return;
  oledLastAttempt=now;
  bool firstAttempt=!oledAttempted; oledAttempted=true;
  // 仅在恢复期间重建总线，仍显式指定原来的GPIO0/1。
  Wire.end();
  Wire.begin(SDA_PIN,SCL_PIN); Wire.setTimeOut(20);
  oledLastError=oledProbe(0x3C);
  if(oledLastError==0) {
    bool allocated=display.begin(SSD1306_SWITCHCAPVCC,0x3C,true,false);
    if(allocated && (oledLastError=oledProbe(0x3C))==0) {
      oledOK=true; oledLastHealth=now;
      display.clearDisplay(); // 下一绘图帧立即显示表情。
      lastFrame=now-FRAME_MS;
      Serial.println("OLED ready: 128x64, 0x3C, SDA=0, SCL=1");
      return;
    }
    if(!allocated) Serial.println("OLED buffer allocation failed");
  }
  if(firstAttempt || uint32_t(now-oledLastReport)>=5000) {
    oledLastReport=now;
    Serial.printf("OLED waiting: 0x3C error=%u, 0x3D ACK=%s; SDA=0 SCL=1; retry every 1s\n",
                  oledLastError,oledProbe(0x3D)==0?"yes":"no");
    // 0x3D仅作为诊断，不自动改变用户指定的0x3C地址。
  }
}

void updateBehavior(uint32_t now,bool touchEdge) {
  int sensed=(leftIR.stable?1:0)|(rightIR.stable?2:0);
  if(sensed!=sensedBefore || sensed || touch.stable) lastActivity=now;
  sensedBefore=sensed;
  if(touchEdge && !happy && (!touchedOnce || uint32_t(now-lastTouch)>=TOUCH_COOLDOWN_MS)) {
    happy=true; happyStart=lastTouch=lastActivity=now; touchedOnce=true;
    blinking=false; Serial.println("Touch: happy + pitch nod");
  }
  if(happy && uint32_t(now-happyStart)>=HAPPY_MS) {
    happy=false; blinkWaitStart=now; blinkWait=random(2500,5501);
  }
  float yawOffset=0,pitchOffset=0;
  if(happy) {
    targetGazeX=0; targetGazeY=0;
    // 一个完整轻点头：600ms下压，600ms返回，余下时间保持中位。
    uint32_t elapsed=now-happyStart;
    if(elapsed<1200) pitchOffset=PITCH_NOD*0.5f*(1.0f-cosf(2.0f*PI*elapsed/1200.0f));
  } else if(sensed) {
    // 双侧同时有效：中位，避免争抢；持续单侧检测：保持方向。
    int direction=sensed==1?-1:(sensed==2?1:0);
    targetGazeX=direction*5; targetGazeY=0; yawOffset=direction*YAW_LOOK;
  } else if(IDLE_RANDOM && uint32_t(now-idleStart)>=idleWait) {
    idleStart=now; idleWait=random(2200,4501);
    targetGazeX=random(-3,4); targetGazeY=random(-1,2);
    idleMood=random(0,5); if(idleMood>2) idleMood=0;
  } else if(!IDLE_RANDOM) { targetGazeX=targetGazeY=0; idleMood=0; }
  // 待机头部始终回中；随机仅用于眼神和表情。
  yaw.aim(CALIBRATION_ONLY?0:yawOffset); pitch.aim(CALIBRATION_ONLY?0:pitchOffset);
  if(!happy && !blinking && uint32_t(now-blinkWaitStart)>=blinkWait) { blinking=true; blinkStart=now; }
  if(blinking && uint32_t(now-blinkStart)>=220) {
    blinking=false; blinkWaitStart=now; blinkWait=IDLE_RANDOM?random(2500,5501):3500;
  }
}
void updateServos(uint32_t now) {
  if(!servosOK || uint32_t(now-lastServo)<SERVO_TICK_MS) return;
  lastServo=now; yaw.step(); pitch.step(); // 每20ms最多1度，不补跑积压帧。
}
// 所有图形只使用白/黑；黑瞳孔是白眼睛中的挖空。
void drawEye(int cx,int cy,int w,int h,float opening) {
  h=max(3,int(h*opening));
  display.fillRoundRect(cx-w/2,cy-h/2,w,h,min(w,h)/2,SSD1306_WHITE);
  if(h>=10) {
    int px=cx+int(lroundf(gazeX)),py=cy+int(lroundf(gazeY));
    int radius=min(5,(h-4)/2);
    display.fillCircle(px,py,radius,SSD1306_BLACK);
    if(radius>=4) display.drawPixel(px-1,py-2,SSD1306_WHITE);
  }
}
void happyEye(int cx) {
  // 采样圆滑弧线，双像素厚度。
  for(int x=-13;x<=13;++x) {
    int y=23+int(lroundf(9.0f*x*x/169.0f));
    display.drawPixel(cx+x,y,SSD1306_WHITE); display.drawPixel(cx+x,y+1,SSD1306_WHITE);
  }
}
void smile(int cy) {
  for(int x=-7;x<=7;++x) display.drawPixel(64+x,cy+int(lroundf(3*(1-x*x/49.0f))),SSD1306_WHITE);
}
void drawFace(uint32_t now) {
  if(!oledOK || uint32_t(now-lastFrame)<FRAME_MS) return;
  lastFrame=now; gazeX+=(targetGazeX-gazeX)*0.22f; gazeY+=(targetGazeY-gazeY)*0.22f;
  bool sleepy=!happy && !sensedBefore && !touch.stable && uint32_t(now-lastActivity)>=SLEEP_AFTER_MS;
  int mood=sensedBefore?1:idleMood;
  float opening=1;
  if(blinking) {
    float t=float(uint32_t(now-blinkStart))/220;
    opening=fabsf(2*t-1); // 柔和闭合/张开，无delay。
  }
  display.clearDisplay();
  if(happy) { happyEye(37); happyEye(91); smile(45); }
  else {
    int h=sleepy?10:(mood==2?20:28);
    drawEye(37,29,28,h,opening);
    drawEye(91,29,(!sleepy && mood==1)?23:28,(!sleepy && mood==1)?22:h,opening);
    if(sleepy) { display.drawCircle(64,49,3,SSD1306_WHITE); }
    else smile(mood==2?47:46);
  }
  if(happy || (!sleepy && mood==2)) {
    // 害羞腮红：斜线像素，不依赖颜色。
    for(int i=0;i<3;++i) {
      display.drawLine(18+i*4,43,16+i*4,47,SSD1306_WHITE);
      display.drawLine(104+i*4,43,102+i*4,47,SSD1306_WHITE);
    }
  }
  display.display(); // 有限I2C传输开销，非硬实时；动作逻辑不阻塞等待。
}
void setup() {
  Serial.begin(115200); // 不等待电脑连接。
  uint32_t now=millis();
  leftIR.begin(now); rightIR.begin(now); touch.begin(now);
  // 上电已触摸：不触发，先释放再触摸。
  randomSeed(esp_random());
  Wire.begin(SDA_PIN,SCL_PIN); Wire.setTimeOut(20);
  oledBoot=now;
  if(SERVOS_ENABLED) {
    bool a=yaw.begin(YAW_PIN), b=pitch.begin(PITCH_PIN); servosOK=a && b;
    if(!servosOK) { yaw.servo.detach(); pitch.servo.detach(); Serial.println("Servo attach failed; both disabled"); }
  }
  lastActivity=lastServo=blinkWaitStart=idleStart=now;
  Serial.println("PaperRobotV2 OLED recovery build ready; bench test before mechanical assembly");
}
void loop() {
  uint32_t now=millis(); leftIR.update(now); rightIR.update(now);
  bool edge=touch.update(now);
  updateBehavior(now,edge); updateServos(now); serviceOLED(now); drawFace(now);
}


