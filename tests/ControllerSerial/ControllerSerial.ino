#include <Arduino.h>
void setup(){Serial.begin(115200);}
void loop(){Serial.printf("ESP32-C3 alive, millis=%lu\n",(unsigned long)millis());delay(1000);}
