#include <ESP32Servo.h>
Servo yaw,pitch;
void setup(){Serial.begin(115200);yaw.setPeriodHertz(50);pitch.setPeriodHertz(50);yaw.attach(4,1000,2000);pitch.attach(5,1000,2000);yaw.write(90);pitch.write(90);Serial.println("90 degrees commanded; horns must be removed first");}
void loop(){}
