# ESP32 Companion Robot V1

**INNNX. · Robots & IoT**

[简体中文](README.zh-CN.md) | [Español](README.es.md) | **English** · [Project home](../README.md)

## 1. Introduction

This is an ESP32-based companion robot prototype. The repository publishes an Arduino sketch for the OLED facial-display module; it does not represent a completed robot. V1 is inspired by a reference project and remains in development.

## 2. Project goals

- Explore building a companion robot and adapt hardware materials and configuration to my needs.
- Start from the existing OLED facial-display code and progress toward hardware validation.
- Accurately document code, test results and version status, distinguishing actual achievements from future plans.

These are development goals, not completed achievements.

## 3. Hardware and technologies

| Item | Information confirmed from existing files |
| --- | --- |
| Board | ESP32 family; specific model requires physical confirmation |
| Display | SSD1306 OLED, 128×64 |
| Communication | I²C; code address `0x3C` |
| Pins | SDA GPIO 0, SCL GPIO 1; compatibility with the actual board requires confirmation |
| Environment | Arduino IDE, ESP32 board support |
| Language and dependencies | Arduino/C++, Wire, Adafruit GFX, Adafruit SSD1306 |
| Program | [`firmware/oled-face/oled-face.ino`](../firmware/oled-face/oled-face.ino) |
| Serial | `115200` baud |

This is not a complete, physically verified bill of materials. Other materials, the power arrangement and the detailed hardware adaptations are not documented.

## 4. Implemented functionality

Here, “implemented” means only that the code has been written:

| Function | Code status | Hardware validation |
| --- | --- | --- |
| Initialize I²C and SSD1306 | Written | Not confirmed |
| Clear the buffer, draw eyes and mouth, and submit the display buffer | Written; static graphics | Not confirmed |
| Serial status messages | Written; the success branch prints `OLED OK!`; the failure branch prints `OLED ERROR` and stops | Not confirmed |

The eyes use `fillRoundRect()`, the mouth uses two `drawLine()` calls, and `display.display()` submits the buffer. `loop()` is empty. Facial animation, conversation, networking, voice, motion control and autonomous behavior are not implemented.

## 5. Current development status

**V1 — Inspired Prototype / In Development**

This update reviewed files and code only; no hardware was connected, and the program was not recompiled, uploaded or tested. The repository has no hardware test records confirming display operation. This does not establish that hardware has never been tested; it means validation cannot currently be confirmed. The program's success message alone does not prove successful hardware validation.

The public scope is the existing OLED sketch and documentation; undocumented modules are not treated as implemented.

## 6. V1 inspiration and acknowledgements

**Original source: [Original Xiaohongshu creator](https://xhslink.cn/m/5y0F9KIVkvd).**

V1 was inspired by the robot project publicly shared by this creator. I referred to the creator's publicly shared building approach and adapted some hardware materials and configuration to my needs. V1 is therefore not a wholly independent original design. Thank you to the creator for sharing the building approach.

An attempt to check the link reached a page requiring login, and the creator's name could not be confirmed. “Original Xiaohongshu creator” is used without inventing a username. The attribution is based on information supplied by this project's author; the original project's technical details and the sketch's code provenance have not been independently verified.

This update copies none of the creator's code, images or other materials. Acknowledgements do not grant permission to reuse material. Without a detailed change list, no hardware comparison is invented. **V1's source reference and acknowledgements must remain permanently, even if later versions adopt different designs.**

## 7. V2 and V3 plans

| Version | Direction | Status |
| --- | --- | --- |
| V1 | Inspired Prototype | In Development |
| V2 | Independent Design | Planned |
| V3 | Future Independent Development | Planned |

V2, V3 and subsequent versions are planned to use solutions independently designed and developed by INNNX., no longer based on this creator's robot-building design. They are currently plans only: no completed versions, specific features or technical achievements can be confirmed. Fully independent originality must be assessed against actual implementation, dependencies and source records; a plan alone does not establish originality.

## 8. Usage and known limitations

1. Check the OLED interface, power, electrical levels and wiring against your actual board. Confirm that SDA GPIO 0, SCL GPIO 1 and address `0x3C` are suitable; compatibility is not guaranteed for every ESP32 board.
2. Install the appropriate ESP32 board support and the Adafruit GFX and Adafruit SSD1306 libraries in Arduino IDE.
3. Open the sketch linked above, select the correct board and port, and check settings before compiling and uploading on your own device.
4. Inspect serial output at `115200` baud and physically observe the OLED. Record the result and hardware used; do not present expected behavior as a completed test.

This procedure was not tested on hardware during this update. The code draws one static face once, stops on initialization failure, and leaves `loop()` empty. The repository has no complete wiring diagram, complete bill of materials, hardware validation evidence or record of permission to reuse the creator's materials. This update publishes no keys, personal information or third-party material.

[Project home](../README.md) · [Robots & IoT](https://github.com/Lq922466/Lq922466/blob/main/portfolio/robots-iot.md)
