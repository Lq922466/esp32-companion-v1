# 编译与实物测试记录

[English](../TESTING.md) | [中文](TESTING.md) | [Español](../es/TESTING.md)

[中文资料目录](INDEX.md) · [项目首页](../../README.zh-CN.md)
[编译结果 JSON](../compile-results.json) 与 [环境版本](../compile-logs/environment.txt) 已生成，完整日志保存在 docs/compile-logs。编译、上传和实物测试是不同步骤；旧编译产物不能证明此项目的新一轮编译通过。

## 实物逐项记录：本次仍待补充
| 检查 | 预期行为 | 实际结果／证据 |
|---|---|---|
| USB 与串口 | 115200 输出、持续供电 | 待记录 |
| UBEC 空载 | 实测稳压 5V、正确极性 | 待记录 |
| OLED | 扫描 0x3C ACK，并实际可见像素 | 待记录 |
| 左右红外 | 两侧原始电平独立变化 | 待记录 |
| TTP223 | 瞬时触摸有效、释放恢复 | 待记录 |
| 空载 yaw／pitch | 90° 回中和保守小幅动作 | 待记录 |
| 待机脸 | 实心眼、眨眼、好奇／害羞随机；45s 后睡眠 | 待记录 |
| 单侧红外联动 | 整脸 ±10px，yaw 跟随 | 待记录 |
| 双侧红外 | 脸部与 yaw 回中 | 待记录 |
| 触摸联动 | 开心和一次点头；冷却后释放再触摸 | 待记录 |
| 触摸加红外 | 脸跟随红外、pitch 点头、yaw 回中 | 待记录 |
| 持续运行 | 无复位、堵转、发热、线缆拉力；选择并记录时长 | 待记录 |

每次记录日期、板型／核心／库版本、源码 SHA256、实际接线、输入极性、测量电压、观察者、串口日志和真实照片／视频。观察后才标通过或失败。本次没有硬件烧录、端口操作或逐项实物通过声明。

## 重新编译：2026-10-13
所选 11 个程序全部通过 `esp32:esp32:esp32c3:CDCOnBoot=cdc` 编译。ESP32 核心 3.3.12；ESP32Servo 3.2.1；SSD1306 2.5.17；GFX 1.12.6；BusIO 1.17.4。

首次遇到 Windows 工具链路径过长及缓存清理错误；复用 R: 短路径映射和独立 D: 编译路径后解决，没有改写恢复源码。最终日志与哈希见上方链接。历史版本全部保留，但没有全部重新编译。

| 程序 | 编译 | 实物测试 |
|---|---|---|
| [tests/ControllerSerial/ControllerSerial.ino](../../tests/ControllerSerial/ControllerSerial.ino) | 通过 | 本次未执行 |
| [tests/IR_Left/IR_Left.ino](../../tests/IR_Left/IR_Left.ino) | 通过 | 本次未执行 |
| [tests/IR_Right/IR_Right.ino](../../tests/IR_Right/IR_Right.ino) | 通过 | 本次未执行 |
| [tests/OLED_Display/OLED_Display.ino](../../tests/OLED_Display/OLED_Display.ino) | 通过 | 本次未执行 |
| [tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino](../../tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino) | 通过 | 本次未执行 |
| [tests/Servo_Center/Servo_Center.ino](../../tests/Servo_Center/Servo_Center.ino) | 通过 | 本次未执行 |
| [tests/Servo_Pitch/Servo_Pitch.ino](../../tests/Servo_Pitch/Servo_Pitch.ino) | 通过 | 本次未执行 |
| [tests/Servo_Yaw/Servo_Yaw.ino](../../tests/Servo_Yaw/Servo_Yaw.ino) | 通过 | 本次未执行 |
| [tests/Touch_TTP223/Touch_TTP223.ino](../../tests/Touch_TTP223/Touch_TTP223.ino) | 通过 | 本次未执行 |
| [firmware/PaperRobotV2/PaperRobotV2.ino](../../firmware/PaperRobotV2/PaperRobotV2.ino) | 通过 | 本次未执行 |
| [firmware/archive/PaperRobotV1/PaperRobotV1.ino](../../firmware/archive/PaperRobotV1/PaperRobotV1.ino) | 通过 | 本次未执行 |

## 用户演示：2026-10-13
用户已提供 [真实视频](../../media/PaperRobotV2-demo.mp4)，发布为浏览器兼容 MP4 和真实截图，完整媒体解码通过。这是作品证据，但实际烧录哈希与逐项实物记录未确认，上表保持待补充。详见 [视频来源](MEDIA.md)。
