# Independent component tests / 各配件独立测试

[中文](zh-CN/COMPONENT-TESTS.md) | [Español](es/COMPONENT-TESTS.md)
Each linked file contains the complete Arduino test code. Run one sketch at a time with only the relevant module connected. New diagnostics authored for this package are not claimed to be the owner's historical test code. The recovered OLED_I2C_Scanner is preserved byte-for-byte; other recovered integrated sketches are retained in archive.

All serial output uses 115200 baud. Use the ESP32-C3 target and dependencies in FIRMWARE. Disconnect servos while testing logic. Never connect 12V to a test GPIO.

| Sketch | Purpose | Expected observation (not an actual pass) |
|---|---|---|
| [Recovered OLED_I2C_Scanner](../tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino) | Discover I2C device on GPIO0/1 | 0x3C ACK; does not prove visible pixels |
| [ControllerSerial](../tests/ControllerSerial/ControllerSerial.ino) | Controller/USB check | Serial message each second |
| [OLED_Display](../tests/OLED_Display/OLED_Display.ino) | OLED pixel check | HELLO and border visible |
| [IR_Left](../tests/IR_Left/IR_Left.ino) | Left IR GPIO6 | Raw 0/1 changes when object approaches |
| [IR_Right](../tests/IR_Right/IR_Right.ino) | Right IR GPIO7 | Raw 0/1 changes when object approaches |
| [Touch_TTP223](../tests/Touch_TTP223/Touch_TTP223.ino) | Touch GPIO10 | Raw HIGH on touch and LOW on release in expected configuration |
| [Servo_Yaw](../tests/Servo_Yaw/Servo_Yaw.ino) | Yaw GPIO4 unloaded | 90, 85, 90, 95, 90 degrees once, commanded over serial |
| [Servo_Pitch](../tests/Servo_Pitch/Servo_Pitch.ino) | Pitch GPIO5 unloaded | 90, 85, 90, 95, 90 degrees once, commanded over serial |
| [Servo_Center](../tests/Servo_Center/Servo_Center.ino) | Both servos, horns removed | Both command 90 degrees and hold; actual neutral must be checked |

## Test procedures and fault isolation
1. Controller: connect USB only; select correct board/port and observe messages. If absent, check USB data cable, CDC setting and port ownership.
2. OLED: scanner first, then OLED_Display. Scanner failure: power, GND, swapped pins, address and pull-ups. ACK with no HELLO: panel/controller type, geometry and module power. Do not use servo power to diagnose the OLED.
3. IR_Left and IR_Right: power one compatible module from 3.3V, connect OUT to its assigned pin; move a hand in/out and record idle/active raw level. Final firmware assumes LOW active. Adjust sensitivity and check ambient light/reflections if stuck. Do not connect a 5V output directly to ESP32.
4. Touch: connect TTP223 at 3.3V, GPIO10; touch/release repeatedly, also through the actual cardboard. Expected momentary HIGH active; if latched, inspect toggle/polarity configuration. Final firmware needs a released-to-active edge.
5. Servo_Center: measure UBEC with a multimeter first, then connect two servos with horns removed and common ground. Code commands 90° immediately; serial output does not prove the shaft reached it. Mount horns only with power removed.
6. Servo_Yaw / Servo_Pitch: one servo at a time, unloaded, horns removed. Each test commands a small 85–95° sequence once, then holds 90°. Switch off if jitter, heat or stalls. No movement: check supply/GND/signal/attach. Direction reversed: verify mounting and final direction configuration.
7. UBEC/adapter: no Arduino program can safely confirm output voltage or current capacity without measurement hardware. Inspect rated 12V input, measure 5V output/polarity unloaded, then measure under actual servo load; record readings. Keep 12V only on input. Breadboard/lead integrity is checked by continuity and voltage measurements with appropriate power state.
8. Cardboard/mounts: inspect stability, clearance and wiring strain physically; no standalone Arduino sketch verifies structural strength.

中文：代码链接包含完整测试源码；OLED 扫描为已有程序，其余为此次新增诊断，不冒充历史调试代码。预期结果不是已通过测试。先 USB、OLED、单侧红外、触摸、舵机回中和单舵机测试，再组合运行。UBEC 必须用万用表测量，不能靠程序证明安全。
Español: los enlaces contienen código completo; el escáner fue recuperado y los demás diagnósticos son nuevos. Los resultados esperados no son pruebas realizadas. El UBEC necesita mediciones físicas.
