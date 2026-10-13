#include <Arduino.h>
constexpr int PIN=10;
void setup(){Serial.begin(115200);pinMode(PIN,INPUT);}
void loop(){Serial.printf("GPIO%d raw=%d\n",PIN,digitalRead(PIN));delay(100);}
