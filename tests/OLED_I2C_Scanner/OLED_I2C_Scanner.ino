#include <Wire.h>

constexpr int SDA_PIN = 0;
constexpr int SCL_PIN = 1;

void setup() {
  Serial.begin(115200);
  unsigned long started = millis();
  while (!Serial && millis() - started < 3000) delay(10);
  delay(300);
  Serial.println("ESP32-C3 USB CDC I2C scanner started");
  Wire.begin(SDA_PIN, SCL_PIN, 100000);
  Wire.setTimeOut(50);
}

void loop() {
  Serial.println("Scanning I2C (SDA=GPIO0, SCL=GPIO1)...");
  int found = 0;
  int errors = 0;
  for (uint8_t address = 1; address < 127; ++address) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf("Found device at 0x%02X\n", address);
      ++found;
    } else if (error != 2) {
      ++errors;
    }
  }
  if (!found) Serial.println("No I2C devices found");
  if (errors) Serial.printf("I2C bus errors/timeouts: %d\n", errors);
  Serial.println("----------------");
  delay(2000);
}
