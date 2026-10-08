#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define SDA_PIN 0
#define SCL_PIN 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED ERROR");
    while (true);
  }

  display.clearDisplay();

  // 左眼
  display.fillRoundRect(30, 18, 22, 32, 8, SSD1306_WHITE);

  // 右眼
  display.fillRoundRect(76, 18, 22, 32, 8, SSD1306_WHITE);

  // 小嘴巴
  display.drawLine(59, 47, 64, 50, SSD1306_WHITE);
  display.drawLine(64, 50, 69, 47, SSD1306_WHITE);

  display.display();

  Serial.println("OLED OK!");
}

void loop() {
}