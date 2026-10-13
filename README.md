# PaperRobot V2
ESP32-C3 cardboard companion robot by INNNX. Inspired by **Made by Z**; this V2 remains an adaptation, not a claim of fully independent design.

[中文](README.zh-CN.md) | [Español](README.es.md)

## What the recovered firmware implements
Six face designs (normal, happy, blink, curious, shy, sleeping), filled capsule eyes, smooth expression transitions and blinking. Left/right IR inputs translate the **entire face**, including eyes and mouth, and command yaw. Both IR inputs active means centered. Touch triggers a happy expression and one pitch nod. Head movement is limited and rate controlled; OLED initialization retries after failure.

These are source-code findings. Compilation results are in [TESTING](docs/TESTING.md); physical operation has not been verified during this packaging task. The owner reports the build is completed; no photo/video test evidence is included yet.

## Hardware and getting started
ESP32-C3 SuperMini; SSD1306 128×64 I2C 0x3C (SDA 0/SCL 1); two SG90 servos (yaw 4/pitch 5); IR left 6/right 7; TTP223 touch 10. External UBEC provides 5V for servos, with common ground. **12V adapter connects only to UBEC input.** Keep the existing large breadboard.

The shell uses **3mm corrugated cardboard, measured and cut manually against the actual parts**. No cutting PDF template was used or is distributed. Dimensions must be measured on the actual build.

1. Read [SAFETY](docs/SAFETY.md) and [WIRING](docs/WIRING.md).
2. Run [independent component tests](docs/COMPONENT-TESTS.md), with servo horns removed initially.
3. Follow [ASSEMBLY](docs/ASSEMBLY.md), then upload [complete V2 source](firmware/PaperRobotV2/PaperRobotV2.ino) using [FIRMWARE](docs/FIRMWARE.md).
4. Record actual results using [TESTING](docs/TESTING.md).

## Project documentation
[BOM](docs/BOM.md) · [WIRING](docs/WIRING.md) · [ASSEMBLY](docs/ASSEMBLY.md) · [COMPONENT-TESTS](docs/COMPONENT-TESTS.md) · [FIRMWARE](docs/FIRMWARE.md) · [TROUBLESHOOTING](docs/TROUBLESHOOTING.md) · [SAFETY](docs/SAFETY.md) · [TESTING](docs/TESTING.md) · [Credits and differences](docs/ATTRIBUTION.md) · [History](CHANGELOG.md) · [License review](LICENSE-REVIEW.md)

## Real build media — awaiting owner
- Finished robot photo: **pending real image/link**.
- Demonstration video: **pending real video/link** (idle expressions, left/right/both sensing, touch nod).
- Assembly photos and dimensions: **pending owner evidence**.

No synthetic photographs, invented videos or claimed physical test passes are included.

## Preserved source
V2 is copied byte-for-byte from the latest recovered delivery. V1 is preserved under firmware/archive. All recovered project sketches and source hashes are retained in archive; earlier public OLED code and documentation remain in archive/prior-public-repository. Newly authored diagnostic sketches are explicitly identified in COMPONENT-TESTS. See [source inventory](archive/SOURCE-MANIFEST.json).

No blanket open-source license has been assigned until source ownership and upstream permissions are confirmed.
