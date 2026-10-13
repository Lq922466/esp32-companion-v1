# Wiring / 接线 / Cableado
Disconnect power before wiring. GPIO numbers refer to ESP32-C3 GPIO, not physical header position.

| Device | Signal | GPIO | Power |
|---|---|---:|---|
| OLED | SDA / SCL | 0 / 1 | 3.3V if module supports it; GND common |
| SG90 yaw | signal | 4 | UBEC 5V and common GND |
| SG90 pitch | signal | 5 | UBEC 5V and common GND |
| Left IR | digital OUT | 6 | 3.3V-compatible supply and output required |
| Right IR | digital OUT | 7 | 3.3V-compatible supply and output required |
| TTP223 | OUT | 10 | 3.3V for a compatible module; common GND |

```text
12V adapter + / - -> UBEC INPUT + / -
UBEC OUTPUT 5V -> both servo V+
UBEC OUTPUT GND -> servo GND and ESP32 GND
USB -> ESP32 power/programming
ESP32 3.3V -> compatible OLED / touch / IR modules
ESP32 GPIO -> module signals (table above)
```

**Never connect 12V to ESP32, OLED, sensors, servos or breadboard logic rails.** Measure UBEC output and polarity before plugging servos in. Do not join external 5V to USB 5V without verifying the board power circuit.

ESP32-C3 inputs are 3.3V logic: if an IR module needs 5V or outputs 5V, use suitable level conversion and confirm its circuit. A pull-up in firmware is not a voltage converter. Keep I2C pull-ups on the 3.3V side. Check board/module datasheets rather than trusting wire color or a seller photo.

Keep the large breadboard; verify whether its rails split midway. Label 3.3V, 5V and GND. Prefer rated direct connections for servo current rather than long breadboard/jumper paths. Do not mechanically load GPIO headers. SG90 wire colors vary: confirm signal/+/- on the actual unit.

中文：12V 只进 UBEC，5V 只给舵机，ESP32 与模块共地。模块输出必须兼容 3.3V；不要将 5V 信号直接送进 GPIO。西语：12V solo al UBEC; masa común y señales compatibles con 3,3V.
