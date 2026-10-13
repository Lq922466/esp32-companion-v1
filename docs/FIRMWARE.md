# Firmware / 固件 / Firmware

[中文](zh-CN/FIRMWARE.md) | [Español](es/FIRMWARE.md)
Complete recovered source: [PaperRobotV2.ino](../firmware/PaperRobotV2/PaperRobotV2.ino). It is preserved unchanged. V1 backup is in firmware/archive/PaperRobotV1; recovered variants are evidence, not alternative files to place together in one sketch directory.

## Build and upload
Use Arduino IDE with ESP32 board support; select **ESP32C3 Dev Module** for this compatible generic target (confirm actual SuperMini board). Install Adafruit GFX, Adafruit SSD1306, Adafruit BusIO and ESP32Servo. Wire is included in the ESP32 core. See TESTING for exact locally used versions.

Official setup reference: [Espressif Arduino-ESP32 installation](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

Open firmware/PaperRobotV2/PaperRobotV2.ino, select the actual port, enable USB CDC on boot for USB serial when appropriate, compile, then upload. Serial monitor is 115200 baud. Do not wait for serial attachment: setup deliberately continues independently. If a port is unavailable, use a data cable, close other port users and follow board-specific BOOT/RESET instructions. Compilation does not verify upload or movement.

```sh
arduino-cli compile --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc firmware/PaperRobotV2
```

## Source behavior
| Source area | Function |
|---|---|
| Config | Pins, polarity, limits, timing, OLED rotation and servo enable switches |
| StableInput | 40ms debounce; activation edge; boot-held touch does not trigger until release/re-touch |
| Axis | 50Hz servo; 1000–2000us pulse endpoints; home 90°; max one degree per 20ms |
| updateBehavior | IR state 1 left, 2 right, 3 both; face ±10px; yaw ±10°; touch cooldown 2200ms |
| Touch happy state | 1800ms happy; one smooth 1200ms nod of 6°; yaw returns toward home during touch |
| ReferenceFace | Six pose data sets; solid eyes; 180ms smoothstep transitions; translated mouth, blush and Z |
| drawFace | 40ms frame interval; 220ms blink; smooth shared horizontal offset; buffer flush |
| serviceOLED | 300ms startup delay; 1s retry; 2s health probe; 1500ms HELLO before face |
| Idle/sleep | Random normal/curious/shy moods; sleep after 45s inactivity; idle head centered |

Blink is rendered as an eye-closing animation; pose table index 2 is not selected as a persistent mood. Idle glance bookkeeping does not move the face in this recovered revision; actual lateral face movement is IR-driven. No camera, voice, networking or AI dialogue is implemented.

IR defaults active LOW; touch active HIGH. Confirm independently. Both IRs active center the face and yaw. During happy/touch, IR still translates the whole face, but yaw is centered and pitch nod takes priority. Mouth/dot, cheeks and Z share the same horizontal offset as the eyes.

SERVOS_ENABLED=false allows display/sensor diagnostics without driving servos. CALIBRATION_ONLY=true commands home; initial attach still outputs home immediately. Direction constants are ±1; change only after physical unloaded tests. Increasing limits requires rechecking clearance. OLED ACK and nonzero framebuffer cannot prove visible pixels.
