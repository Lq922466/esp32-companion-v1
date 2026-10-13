# Bill of materials / 配件清单 / Materiales

[中文](zh-CN/BOM.md) | [Español](es/BOM.md)
Quantities follow the owner-specified configuration; costs, supplier links and exact sensor/UBEC ratings remain unconfirmed.

| Part | Qty | Purpose / 用途 |
|---|---:|---|
| ESP32-C3 SuperMini | 1 | Controller / 主控 |
| SSD1306 I2C 128×64 OLED, 0x3C | 1 | Animated face / 表情 |
| SG90 servo | 2 | Yaw and pitch / 转头与点头 |
| Digital IR proximity module | 2 | Left/right presence; exact model pending |
| TTP223 module | 1 | Touch input / 触摸 |
| UBEC, regulated 5V output | 1 | Servo supply; verify 12V input rating and current capacity |
| 12V adapter | 1 | UBEC input only; polarity/current rating pending |
| Existing large breadboard | 1 | Low-current signal distribution / 现有大面包板 |
| 3mm corrugated cardboard | as needed | Hand-measured shell; no template |
| Jumpers, servo connectors, USB data cable | as needed | Connections and programming |
| Glue/fasteners, insulation, cable restraints | as needed | Mechanical mounting; actual choices pending |

Use actual SG90 peak-current specifications to size the UBEC and connections for both servos. Do not assume clone ratings. ESP32 is powered by USB in the documented conservative setup; the actual final ESP32 supply arrangement still needs confirmation.
