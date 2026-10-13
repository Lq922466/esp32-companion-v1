    Serial.println("Touch: happy + pitch nod");
  }
  if(happy && uint32_t(now-happyStart)>=HAPPY_MS) {
    happy=false; blinkWaitStart=now; blinkWait=random(2500,5501);
  }
  float yawOffset=0,pitchOffset=0;
  if(happy) {
    targetGazeY=0;
    // 一个完整轻点头：600ms下压，600ms返回，余下时间保持中位。
    uint32_t elapsed=now-happyStart;
    if(elapsed<1200) pitchOffset=PITCH_NOD*0.5f*(1.0f-cosf(2.0f*PI*elapsed/1200.0f));
  } else if(sensed) {
    // 双侧同时有效：中位，避免争抢；持续单侧检测：保持方向。
    int direction=sensed==1?-1:(sensed==2?1:0);
    targetGazeY=0; yawOffset=direction*YAW_LOOK;
  } else {
    targetGazeY=0;
    bool sleepy=!touch.stable && uint32_t(now-lastActivity)>=SLEEP_AFTER_MS;
    if(!IDLE_RANDOM || sleepy || touch.stable) {
      idleGlancing=false; idleMood=0; idleStart=now;
    } else {
      if(idleGlancing && uint32_t(now-idleGlanceStart)>=IDLE_GLANCE_MS) {
        idleGlancing=false; idleStart=now; idleWait=random(2200,4501);
      }
      if(!idleGlancing && uint32_t(now-idleStart)>=idleWait) {
        idleGlancing=true; idleGlanceStart=now;
        idleGlanceDirection=random(0,2)==0?-1:1;
        idleMood=random(0,5); if(idleMood>2) idleMood=0;
      }
      // Keep idle moods; without IR the face smoothly returns to center.
    }
  }
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
// Reference faces: solid vertical white capsule eyes, never pupils or rings.
// All geometry is inside 128x64; labels and reference-card borders are omitted.
class ReferenceFace {
 public:
  // 0 normal, 1 happy, 2 blink, 3 curious, 4 shy, 5 sleeping.
  // width/height pairs, eye baseline/bend, mouth width/bend, cheeks, Z, dot.
  static constexpr float poses[6][12] = {
    {16,24,16,24,26,  0, 6,3,0,0,0,38},
    {24, 3,24, 3,31,-10,10,4,0,0,0,38},
    {20, 2,20, 2,28,  0, 6,3,0,0,0,38},
    {16,22,20,28,26,  0, 4,0,0,0,1,39},
    {24, 2,24, 2,25,  6, 6,2,1,0,0,39},
    {22, 2,22, 2,28,  0, 6,2,0,1,0,39}
  };
  int frameOffsetX=0;
  int faceX(int x) const { return x+frameOffsetX; }
  float current[12], from[12];
  int target=0;
  uint32_t started=0;
  bool ready=false;
  void sample(uint32_t now) {
    // Smoothstep: zero velocity at both ends of a face change.
    float t=constrain(float(uint32_t(now-started))/180.0f,0.0f,1.0f);
    t=t*t*(3.0f-2.0f*t);
    for(int i=0;i<12;++i) current[i]=from[i]+(poses[target][i]-from[i])*t;
  }
  void transition(int pose,uint32_t now) {
    if(!ready) {
      for(int i=0;i<12;++i) current[i]=from[i]=poses[pose][i];
      target=pose; started=now; ready=true;
    }
    sample(now);
    if(pose!=target) {
      for(int i=0;i<12;++i) from[i]=current[i];
      target=pose; started=now;
    }
  }
  void eye(int cx,float width,float height,float cy,float bend) {
    int w=int(lroundf(width)), h=max(2,int(lroundf(height)));
    if(fabsf(bend)<0.5f) {
      // Filled capsule: no BLACK drawing, no outlined eye, no pupil.
      display.fillRoundRect(cx-w/2,int(lroundf(cy))-h/2,w,h,
                            min(w,h)/2,SSD1306_WHITE);
      return;
    }
    int half=w/2;
    int prevY=int(lroundf(cy));
    for(int x=-half;x<=half;++x) {
      float u=float(x)/half;
      int y=int(lroundf(cy+bend*(1.0f-u*u)));
      if(x>-half) {
        for(int k=0;k<h;++k)
          display.drawLine(cx+x-1,prevY-h/2+k,cx+x,y-h/2+k,SSD1306_WHITE);
      }
      prevY=y;
    }
  }
  void mouth(int cx,float width,float cy,float bend) {
    int half=max(2,int(lroundf(width/2)));
    int prevY=int(lroundf(cy));
    for(int x=-half;x<=half;++x) {
      float u=float(x)/half;
      int y=int(lroundf(cy+bend*(1.0f-u*u)));
      if(x>-half) display.drawLine(cx+x-1,prevY,cx+x,y,SSD1306_WHITE);
      prevY=y;
    }
  }
  void render(int pose,uint32_t now,float opening,int dx,int dy) {
    frameOffsetX=constrain(dx,-GAZE_LOOK_PX,GAZE_LOOK_PX);
    transition(pose,now);
    // Blink retains the reference's horizontal closed-eye pose at mid-blink.
    float closed=1.0f-opening;
    float leftW=current[0]+(20-current[0])*closed;
    float rightW=current[2]+(20-current[2])*closed;
    float cy=current[4]+(28-current[4])*closed;
    eye(faceX(43),leftW,2+(current[1]-2)*opening,cy+dy,current[5]*opening);
    eye(faceX(85),rightW,2+(current[3]-2)*opening,cy+dy,current[5]*opening);
    if(current[10]>0.5f && closed<0.5f) display.fillCircle(faceX(64),int(lroundf(current[11]))+dy,2,SSD1306_WHITE);
    else mouth(faceX(64),current[6]+(6-current[6])*closed,
               current[11]+(38-current[11])*closed+dy,current[7]+(3-current[7])*closed);
    if(current[8]*opening>0.5f) {
      // Two restrained blush strokes beside the shy downward-curving eyes.
      display.drawLine(faceX(25),37+dy,faceX(30),35+dy,SSD1306_WHITE);
      display.drawLine(faceX(31),38+dy,faceX(35),36+dy,SSD1306_WHITE);
      display.drawLine(faceX(93),36+dy,faceX(97),38+dy,SSD1306_WHITE);
      display.drawLine(faceX(98),35+dy,faceX(103),37+dy,SSD1306_WHITE);
    }
    if(current[9]>0.5f) {
      int y=12+dy+int((now/750)%2); // Quiet one-pixel floating Z.
      display.drawFastHLine(faceX(98),y,7,SSD1306_WHITE);
      display.drawLine(faceX(104),y,faceX(98),y+8,SSD1306_WHITE);
      display.drawFastHLine(faceX(98),y+8,7,SSD1306_WHITE);
    }
  }
};
constexpr float ReferenceFace::poses[6][12];
ReferenceFace referenceFace;
void drawFace(uint32_t now) {
  if(!oledOK || uint32_t(now-lastFrame)<FRAME_MS) return;
  if(oledHello) {
    if(uint32_t(now-oledHelloStart)<OLED_HELLO_MS) return;
    oledHello=false;
    Serial.println("OLED switching HELLO -> face");
  }
  lastFrame=now;
  faceOffsetX+=(targetFaceOffsetX-faceOffsetX)*0.22f;
  if(fabsf(targetFaceOffsetX-faceOffsetX)<0.01f) faceOffsetX=targetFaceOffsetX;
  gazeY+=(targetGazeY-gazeY)*0.22f;
  bool sleepy=!happy && !sensedBefore && !touch.stable && uint32_t(now-lastActivity)>=SLEEP_AFTER_MS;
  int mood=sensedBefore?0:idleMood;
  int pose=happy?1:(sleepy?5:(mood==1?3:(mood==2?4:0)));
  float opening=1;
  if(blinking && !happy && !sleepy) {
    float t=constrain(float(uint32_t(now-blinkStart))/220.0f,0.0f,1.0f);
    // Cosine closes/reopens gently and holds the reference blink for ~40ms.
    float distance=constrain((fabsf(2*t-1)-0.18f)/0.82f,0.0f,1.0f);
    opening=0.5f-0.5f*cosf(PI*distance);
  }
  // One translation for all face elements: eyes, mouth/dot, blush and Z.
  int dx=constrain(int(lroundf(faceOffsetX)),-GAZE_LOOK_PX,GAZE_LOOK_PX);
  int dy=constrain(int(lroundf(gazeY*0.3f)),-1,1);
  display.clearDisplay();
  referenceFace.render(pose,now,opening,dx,dy);
  display.display(); // Flush every rendered face frame.
  ++oledFrames;
  if(oledFrames==1 || uint32_t(now-oledLastFrameReport)>=5000) {
    oledLastFrameReport=now;
    uint16_t litBytes=0;
    const uint8_t *buffer=display.getBuffer();
    for(uint16_t i=0;i<128*64/8;++i) if(buffer[i]) ++litBytes;
    Serial.printf("OLED face frames=%lu, nonzero buffer bytes=%u, rotation=%u, ACK error=%u\n",
                  (unsigned long)oledFrames,litBytes,OLED_ROTATION,oledProbe(0x3C));
    // display.display() returns void; ACK and buffer content cannot verify pixels.
  }
}
void setup() {
  Serial.begin(115200); // 不等待电脑连接。
  uint32_t now=millis();
  leftIR.begin(now); rightIR.begin(now); touch.begin(now);
  // 上电已触摸：不触发，先释放再触摸。
  randomSeed(esp_random());
  bool busReady=Wire.begin(0,1); // Must precede display.begin; keep GPIO0/1.
  Wire.setClock(OLED_CLOCK_HZ); Wire.setTimeOut(20);
  if(!busReady) Serial.println("OLED Wire.begin(0,1) failed");
  oledBoot=now;
  if(SERVOS_ENABLED) {
    bool a=yaw.begin(YAW_PIN), b=pitch.begin(PITCH_PIN); servosOK=a && b;
    if(!servosOK) { yaw.servo.detach(); pitch.servo.detach(); Serial.println("Servo attach failed; both disabled"); }
  }