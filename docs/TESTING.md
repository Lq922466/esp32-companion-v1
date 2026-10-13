# Testing evidence
Compilation report will be generated in compile-results.json and compile-logs/. Compilation is separate from upload and physical testing. Historical build artifacts do not prove this package passed a fresh compile.

## Physical test log — all pending in this task
| Check | Expected behavior | Actual result / evidence |
|---|---|---|
| USB and serial | 115200 messages, board stays powered | pending |
| UBEC without load | Measured regulated 5V, correct polarity | pending |
| OLED | Scanner ACK 0x3C; actual visible pixels | pending |
| IR left/right | Raw levels change independently | pending |
| TTP223 | Momentary level on touch, release returns | pending |
| Yaw/pitch unloaded | Center 90°, conservative test movements | pending |
| Idle face | Solid eyes, blink, random curious/shy; sleeping after 45s | pending |
| Left/right IR integration | Whole face moves ±10px and yaw follows | pending |
| Both IR integration | Face/yaw center | pending |
| Touch integration | Happy and one nod; release/re-touch after cooldown | pending |
| Touch with IR | Face follows IR; pitch nod and yaw home | pending |
| Sustained operation | No resets, stalls, heating or wire strain | pending; choose and record duration |

For every run record date, board/core/library versions, exact source SHA256, actual wiring, input polarity, voltage measurements, observer, serial log and real video/photo. Tests must be marked pass/fail only after observation. No hardware upload, port access or physical pass is asserted by this task.

## Fresh compilation — 2026-10-13

All 11 selected sketches passed a fresh compile for `esp32:esp32:esp32c3:CDCOnBoot=cdc`. ESP32 core 3.3.12; ESP32Servo 3.2.1; Adafruit SSD1306 2.5.17; GFX 1.12.6; BusIO 1.17.4.

The initial attempts encountered Windows toolchain path length and cache cleanup errors. Reusing the existing short R: toolchain mapping and a separate D: build path resolved these environment errors without modifying recovered source. Final logs and SHA256 hashes are in [compile-results.json](compile-results.json) and compile-logs. Historical variants were retained but not all recompiled.

| Sketch | Compile | Physical test |
|---|---|---|
| tests/ControllerSerial/ControllerSerial.ino | PASS | Not performed |
| tests/IR_Left/IR_Left.ino | PASS | Not performed |
| tests/IR_Right/IR_Right.ino | PASS | Not performed |
| tests/OLED_Display/OLED_Display.ino | PASS | Not performed |
| tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino | PASS | Not performed |
| tests/Servo_Center/Servo_Center.ino | PASS | Not performed |
| tests/Servo_Pitch/Servo_Pitch.ino | PASS | Not performed |
| tests/Servo_Yaw/Servo_Yaw.ino | PASS | Not performed |
| tests/Touch_TTP223/Touch_TTP223.ino | PASS | Not performed |
| firmware/PaperRobotV2/PaperRobotV2.ino | PASS | Not performed |
| firmware/archive/PaperRobotV1/PaperRobotV1.ino | PASS | Not performed |
