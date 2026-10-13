# 完整固件与功能说明

[English](../FIRMWARE.md) | [中文](FIRMWARE.md) | [Español](../es/FIRMWARE.md)

[中文资料目录](INDEX.md) · [项目首页](../../README.zh-CN.md)
[PaperRobotV2.ino 完整源码](../../firmware/PaperRobotV2/PaperRobotV2.ino) 原样保留。[V1 备份](../../firmware/archive/PaperRobotV1/PaperRobotV1.ino) 在独立目录。恢复的历史版本是来源证据，不要把它们一起放到一个 Arduino 草图目录。

## 编译与烧录
Arduino IDE 安装 ESP32 开发板支持，选择 **ESP32C3 Dev Module** 这一兼容通用目标，并核实实际 SuperMini。安装 Adafruit GFX、Adafruit SSD1306、Adafruit BusIO 和 ESP32Servo；Wire 随 ESP32 核心提供。具体编译版本见 [测试](TESTING.md)。官方参考：[Espressif 安装说明](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)。

打开 V2 程序，选择实际端口，需要 USB 串口时启用 USB CDC on boot，先编译再上传。串口监视器为 115200。setup 不等待电脑串口连接，会自行继续。端口不可用时检查数据线、关闭占用串口的软件，按实际板型的 BOOT／RESET 步骤操作。编译通过不证明烧录成功或舵机正常。

在仓库根目录可执行：
```sh
arduino-cli compile --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc firmware/PaperRobotV2
```

## 源码功能
| 区域 | 功能 |
|---|---|
| Config | 引脚、有效极性、角度限制、时间参数、OLED 方向和舵机开关 |
| StableInput | 40ms 去抖与有效边沿；上电已触摸时先释放再触摸才触发 |
| Axis | 舵机 50Hz；脉宽端点 1000–2000μs；中位 90°；每 20ms 最多移动 1° |
| updateBehavior | 红外状态 1 左、2 右、3 双侧；脸部 ±10px；yaw ±10°；触摸冷却 2200ms |
| 触摸开心状态 | 开心 1800ms；一次平滑 1200ms、幅度 6° 的点头；yaw 向中位返回 |
| ReferenceFace | 六组表情数据、实心眼；180ms smoothstep 过渡；嘴巴、腮红和 Z 同步平移 |
| drawFace | 40ms 帧间隔、220ms 眨眼、平滑共享水平偏移与刷新缓冲 |
| serviceOLED | 启动等待 300ms；每 1s 重试；每 2s 检查总线；HELLO 显示 1500ms 后切脸 |
| 待机／睡眠 | 随机正常／好奇／害羞；45s 无活动进入睡眠；待机头部回中 |

眨眼由闭眼动画实现，表情表索引 2 不作为持续情绪选择。此恢复版本的待机 glance 计时本身不移动脸部；真实横向平移由红外驱动。未实现摄像头、语音、联网或 AI 对话。

红外默认 LOW 有效，触摸 HIGH 有效，须分别实测确认。双红外有效时脸部与 yaw 回中。触摸／开心期间红外仍平移整张脸，但 yaw 回中，pitch 点头优先。嘴巴／圆点、腮红、Z 与眼睛使用同一横向偏移。

`SERVOS_ENABLED=false` 可测试屏幕／传感器而不驱动舵机。`CALIBRATION_ONLY=true` 命令回中，但初次 attach 仍会立刻输出中位。方向参数只用 ±1，空载实测后再修改；扩大角度前重新核实机械间隙。OLED ACK 与非空帧缓冲均不能证明屏幕像素已实际显示。
