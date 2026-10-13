#include <ESP32Servo.h>
Servo servo;
void setup(){Serial.begin(115200);servo.setPeriodHertz(50);servo.attach(5,1000,2000);if(!servo.attached()){Serial.println("Attach failed");return;}servo.write(90);delay(3000);int angles[]={90,85,90,95,90};int current=90;for(int target:angles){while(current!=target){current+=target>current?1:-1;servo.write(current);delay(20);}Serial.printf("Commanded %d degrees\n",target);delay(1500);}}
void loop(){}
