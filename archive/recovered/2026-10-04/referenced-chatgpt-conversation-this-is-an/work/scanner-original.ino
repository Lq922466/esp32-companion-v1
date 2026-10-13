#include <Wire.h>

#define SDA_PIN 0
#define SCL_PIN 1

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop() {
  Serial.println("Scanning I2C...");

  int found = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      found++;
    }
  }

  if (found == 0) {
    Serial.println("No I2C devices found");
  }

  Serial.println("----------------");
  delay(2000);
}