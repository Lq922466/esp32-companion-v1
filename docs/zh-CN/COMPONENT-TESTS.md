# 各配件独立测试程序

[English](../COMPONENT-TESTS.md) | [中文](COMPONENT-TESTS.md) | [Español](../es/COMPONENT-TESTS.md)

[中文资料目录](INDEX.md) · [项目首页](../../README.zh-CN.md)
下表链接包含完整 Arduino 测试源码。一次只运行一个程序，只接对应模块。本次新增诊断程序不冒充用户历史调试代码；找到的 OLED_I2C_Scanner 原样保留，其他历史集成程序保存在 archive。

串口统一为 115200 波特率，开发板和依赖见 [固件](FIRMWARE.md)。测试逻辑模块时断开舵机。禁止把 12V 接到任何测试 GPIO。

| 程序 | 用途 | 预期观察（不是实际通过记录） |
|---|---|---|
| [OLED_I2C_Scanner（已有）](../../tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino) | 扫描 GPIO0/1 上的 I²C 设备 | 0x3C 应答；不证明屏幕可见 |
| [ControllerSerial](../../tests/ControllerSerial/ControllerSerial.ino) | 主控／USB 检查 | 每秒串口输出一次 |
| [OLED_Display](../../tests/OLED_Display/OLED_Display.ino) | OLED 像素显示 | 可见 HELLO 和边框 |
| [IR_Left](../../tests/IR_Left/IR_Left.ino) | 左红外 GPIO6 | 物体接近时原始 0/1 电平变化 |
| [IR_Right](../../tests/IR_Right/IR_Right.ino) | 右红外 GPIO7 | 物体接近时原始 0/1 电平变化 |
| [Touch_TTP223](../../tests/Touch_TTP223/Touch_TTP223.ino) | 触摸 GPIO10 | 预期配置下，触摸 HIGH，释放 LOW |
| [Servo_Yaw](../../tests/Servo_Yaw/Servo_Yaw.ino) | Yaw GPIO4 空载 | 指令顺序 90、85、90、95、90°，运行一次并输出串口信息 |
| [Servo_Pitch](../../tests/Servo_Pitch/Servo_Pitch.ino) | Pitch GPIO5 空载 | 同上 |
| [Servo_Center](../../tests/Servo_Center/Servo_Center.ino) | 两舵机回中，先拆舵盘 | 命令 90° 并保持；机械中位仍需观察 |

## 操作与故障排查
1. 主控：只接 USB，选正确板型和端口，观察串口。无输出时检查数据线、CDC 设置和串口占用。
2. OLED：先运行扫描，再运行 OLED_Display。无应答时检查电源、共地、SDA/SCL、地址和上拉；有应答但无 HELLO 时检查屏幕控制器、分辨率与供电。不要依靠舵机电源诊断 OLED。
3. 左／右红外：一次接一个兼容模块，用 3.3V 供电并接对应 OUT。手靠近／远离，记录空闲和有效电平。最终固件默认 LOW 有效。一直有效时调灵敏度、排查环境光和反射；5V 输出不能直接 ESP32。
4. TTP223：3.3V 供电，OUT 接 GPIO10；反复触摸／释放，并隔着真实纸板测试。预期是瞬时 HIGH 有效。若锁存，检查触发模式和极性设置；最终固件需要从释放到有效的边沿。
5. Servo_Center：先用万用表测 UBEC，再连接拆下舵盘的两舵机并共地。程序启动立即命令 90°，串口输出不证明轴已到位。必须断电装舵盘。
6. Servo_Yaw／Servo_Pitch：每次测试一只，空载、拆舵盘。小幅 85–95° 序列只运行一次，随后保持 90°。抖动、发热或堵转立即断电。无动作检查供电、地、信号和 attach；方向相反检查安装及最终方向参数。
7. UBEC／适配器：没有测量硬件时，Arduino 程序不能确认输出电压或电流容量。核实 12V 输入额定值，测量空载 5V 和极性，再测真实舵机负载下的输出并记录。12V 只接输入。面包板和导线需在合适的断电／通电状态下做连续性与电压检查。
8. 纸板／固定件：实物检查稳固性、间隙与线缆拉力；独立 Arduino 程序不能验证结构强度。

先单件测试再组合运行，实际结果填写到 [测试记录](TESTING.md)。
