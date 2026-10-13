#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 d(128,64,&Wire,-1);
void setup(){Serial.begin(115200);Wire.begin(0,1);delay(300);if(!d.begin(SSD1306_SWITCHCAPVCC,0x3C,true,false)){Serial.println("OLED init failed");return;}d.clearDisplay();d.setTextColor(SSD1306_WHITE);d.setTextSize(2);d.setCursor(28,22);d.print("HELLO");d.drawRect(0,0,128,64,SSD1306_WHITE);d.display();Serial.println("Buffer submitted; verify visible pixels");}
void loop(){}
