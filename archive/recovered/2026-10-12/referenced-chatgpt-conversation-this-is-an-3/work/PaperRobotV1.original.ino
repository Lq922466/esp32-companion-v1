#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// ESP32-C3 SuperMini: 保留全部已测试引脚。
constexpr uint8_t SDA_PIN=0, SCL_PIN=1, LEFT_SERVO_PIN=4, RIGHT_SERVO_PIN=5;
constexpr uint8_t LEFT_IR_PIN=6, RIGHT_IR_PIN=7, TOUCH_PIN=10;
// 首次安装前确认90度为无碰撞中位。只在这里调整机械参数。
constexpr int LEFT_HOME=90, RIGHT_HOME=90;
constexpr int LEFT_MIN=80, LEFT_MAX=100, RIGHT_MIN=80, RIGHT_MAX=100;
constexpr int LEFT_DIRECTION=1, RIGHT_DIRECTION=-1; // 反装时修改为相反符号
static_assert(0<=LEFT_MIN && LEFT_MIN<=LEFT_HOME && LEFT_HOME<=LEFT_MAX && LEFT_MAX<=180,
              "Invalid left servo limits/home");
static_assert(0<=RIGHT_MIN && RIGHT_MIN<=RIGHT_HOME && RIGHT_HOME<=RIGHT_MAX && RIGHT_MAX<=180,
              "Invalid right servo limits/home");
constexpr uint32_t DEBOUNCE_MS=30, SERVO_TICK_MS=20, FRAME_MS=40;
constexpr uint32_t CELEBRATE_MS=2400, TOUCH_COOLDOWN_MS=3000;

Adafruit_SSD1306 display(128,64,&Wire,-1);
Servo leftServo, rightServo;
bool oledOK=false, servosOK=false;
int leftAngle=LEFT_HOME, rightAngle=RIGHT_HOME;
int leftTarget=LEFT_HOME, rightTarget=RIGHT_HOME;
uint32_t lastServo=0, lastFrame=0, celebrateStart=0, lastTouch=0;
uint32_t blinkStart=0, nextBlink=0;
bool celebrating=false, touchedBefore=false, blinking=false;
int gaze=0;

// 使用类方法，避免Arduino自动生成函数原型时自定义参数类型的问题。
class StableInput {
 public:
  uint8_t pin; bool activeHigh, raw=false, stable=false; uint32_t changed=0;
  StableInput(uint8_t p,bool high):pin(p),activeHigh(high) {}
  void begin(uint32_t now) {
    pinMode(pin,activeHigh ? INPUT : INPUT_PULLUP);
    raw=stable=(digitalRead(pin)==(activeHigh ? HIGH : LOW)); changed=now;
  }
  bool update(uint32_t now) {
    bool sample=(digitalRead(pin)==(activeHigh ? HIGH : LOW));
    if(sample!=raw) { raw=sample; changed=now; }
    if(raw!=stable && uint32_t(now-changed)>=DEBOUNCE_MS) {
      stable=raw; return stable; // 仅有效状态上升沿返回true
    }
    return false;
  }
};
StableInput leftIR(LEFT_IR_PIN,false), rightIR(RIGHT_IR_PIN,false), touch(TOUCH_PIN,true);

int stepToward(int current,int target) {
  if(current<target) return current+1;
  if(current>target) return current-1;
  return current;
}

void updateBehavior(uint32_t now,bool touchEdge) {
  if(touchEdge && !celebrating && (!touchedBefore || uint32_t(now-lastTouch)>=TOUCH_COOLDOWN_MS)) {
    celebrating=true; celebrateStart=now; lastTouch=now; touchedBefore=true;
    blinking=false; Serial.println("Touch: happy!");
  }
  if(celebrating && uint32_t(now-celebrateStart)>=CELEBRATE_MS) {
    celebrating=false; nextBlink=now; blinkStart=now; // 重置普通眨眼计时
  }
  leftTarget=LEFT_HOME; rightTarget=RIGHT_HOME; gaze=0;
  // 优先级：触摸庆祝 > 双侧感应 > 单侧感应 > 待机。
  if(celebrating) {
    uint32_t phase=uint32_t(now-celebrateStart)/600;
    // 左手抬起、回中，右手抬起、回中；不同时挥动两只手。
    if(phase==0 && rightAngle==RIGHT_HOME) leftTarget=LEFT_HOME+LEFT_DIRECTION*8;
    if(phase==2 && leftAngle==LEFT_HOME) rightTarget=RIGHT_HOME+RIGHT_DIRECTION*8;
  } else if(leftIR.stable && rightIR.stable) {
    // 两侧同时检测时看正前方，双手回中，避免争抢和反复切换。
  } else if(leftIR.stable) {
    gaze=-1;
    if(rightAngle==RIGHT_HOME) leftTarget=LEFT_HOME+LEFT_DIRECTION*6;
  } else if(rightIR.stable) {
    gaze=1;
    if(leftAngle==LEFT_HOME) rightTarget=RIGHT_HOME+RIGHT_DIRECTION*6;
  }
  leftTarget=constrain(leftTarget,LEFT_MIN,LEFT_MAX);
  rightTarget=constrain(rightTarget,RIGHT_MIN,RIGHT_MAX);
}

void updateServos(uint32_t now) {
  if(!servosOK || uint32_t(now-lastServo)<SERVO_TICK_MS) return;
  lastServo=now; // 不补跑延迟帧，始终每次最多1度
  leftAngle=stepToward(leftAngle,leftTarget);
  rightAngle=stepToward(rightAngle,rightTarget);
  leftServo.write(leftAngle); rightServo.write(rightAngle);
}

void drawFace(uint32_t now) {
  if(!oledOK || uint32_t(now-lastFrame)<FRAME_MS) return;
  lastFrame=now;
  if(!celebrating) {
    if(!blinking && uint32_t(now-nextBlink)>=3500) { blinking=true; blinkStart=now; }
    if(blinking && uint32_t(now-blinkStart)>=160) { blinking=false; nextBlink=now; }
  }
  display.clearDisplay();
  int x1=38+gaze*9, x2=90+gaze*9;
  if(celebrating) {
    // 两个倒V形开心眼睛。
    for(int offset=0; offset<3; ++offset) {
      display.drawLine(25,34+offset,38,22+offset,SSD1306_WHITE);
      display.drawLine(38,22+offset,51,34+offset,SSD1306_WHITE);
      display.drawLine(77,34+offset,90,22+offset,SSD1306_WHITE);
      display.drawLine(90,22+offset,103,34+offset,SSD1306_WHITE);
    }
    display.drawLine(57,47,64,51,SSD1306_WHITE);
    display.drawLine(64,51,71,47,SSD1306_WHITE);
  } else if(blinking) {
    display.fillRoundRect(x1-13,30,26,4,2,SSD1306_WHITE);
    display.fillRoundRect(x2-13,30,26,4,2,SSD1306_WHITE);
  } else {
    display.fillRoundRect(x1-13,19,26,26,7,SSD1306_WHITE);
    display.fillRoundRect(x2-13,19,26,26,7,SSD1306_WHITE);
  }
  display.display(); // I2C传输耗时有限；没有delay或等待动作完成的循环
}

void setup() {
  Serial.begin(115200); // 不等待USB串口连接
  uint32_t now=millis();
  leftIR.begin(now); rightIR.begin(now); touch.begin(now);
  // 上电已按住触摸时不触发；释放后再触摸才产生上升沿。
  Wire.begin(SDA_PIN,SCL_PIN); Wire.setTimeOut(20);
  oledOK=display.begin(SSD1306_SWITCHCAPVCC,0x3C,true,false);
  if(!oledOK) Serial.println("OLED init failed; other functions continue.");
  leftServo.setPeriodHertz(50); rightServo.setPeriodHertz(50);
  leftServo.attach(LEFT_SERVO_PIN,1000,2000);
  rightServo.attach(RIGHT_SERVO_PIN,1000,2000);
  servosOK=leftServo.attached() && rightServo.attached();
  if(servosOK) { leftServo.write(LEFT_HOME); rightServo.write(RIGHT_HOME); }
  else { leftServo.detach(); rightServo.detach(); Serial.println("Servo attach failed."); }
  nextBlink=now; lastServo=now;
  Serial.println("PaperRobot V1 ready.");
}

void loop() {
  uint32_t now=millis();
  leftIR.update(now); rightIR.update(now);
  bool touchEdge=touch.update(now);
  updateBehavior(now,touchEdge);
  updateServos(now);
  drawFace(now);
}
