# Pruebas independientes de componentes

[English](../COMPONENT-TESTS.md) | [中文](../zh-CN/COMPONENT-TESTS.md) | [Español](COMPONENT-TESTS.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
Los enlaces incluyen el código Arduino completo. Ejecutar un programa cada vez y conectar únicamente su módulo. Los diagnósticos nuevos no se presentan como código histórico del propietario. OLED_I2C_Scanner se conserva sin cambios; los programas integrados anteriores están en archive.

Toda salida serie usa 115200 baudios. Placa y dependencias: [firmware](FIRMWARE.md). Desconectar servos al probar lógica. Nunca conectar 12V a un GPIO de prueba.

| Programa | Uso | Observación esperada, no resultado realizado |
|---|---|---|
| [OLED_I2C_Scanner recuperado](../../tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino) | Detectar I²C en GPIO0/1 | ACK en 0x3C; no demuestra píxeles visibles |
| [ControllerSerial](../../tests/ControllerSerial/ControllerSerial.ino) | Controlador/USB | Mensaje serie cada segundo |
| [OLED_Display](../../tests/OLED_Display/OLED_Display.ino) | Visualización OLED | HELLO y borde visibles |
| [IR_Left](../../tests/IR_Left/IR_Left.ino) | IR izquierdo GPIO6 | Cambio de nivel bruto 0/1 al acercar un objeto |
| [IR_Right](../../tests/IR_Right/IR_Right.ino) | IR derecho GPIO7 | Cambio de nivel bruto 0/1 al acercar un objeto |
| [Touch_TTP223](../../tests/Touch_TTP223/Touch_TTP223.ino) | Tacto GPIO10 | HIGH al tocar y LOW al soltar en la configuración esperada |
| [Servo_Yaw](../../tests/Servo_Yaw/Servo_Yaw.ino) | Yaw GPIO4 sin carga | Secuencia ordenada 90,85,90,95,90° una vez; mensajes serie |
| [Servo_Pitch](../../tests/Servo_Pitch/Servo_Pitch.ino) | Pitch GPIO5 sin carga | La misma secuencia |
| [Servo_Center](../../tests/Servo_Center/Servo_Center.ino) | Ambos servos, brazos desmontados | Orden de 90° y mantenimiento; comprobar centro mecánico real |

## Procedimientos y aislamiento de fallos
1. Controlador: conectar solo USB, seleccionar placa/puerto y observar mensajes. Si faltan, comprobar cable de datos, CDC y otros programas que ocupen el puerto.
2. OLED: primero escáner y después OLED_Display. Sin ACK: alimentación, masa, SDA/SCL, dirección y pull-up. Con ACK pero sin HELLO: controlador de pantalla, resolución y alimentación. No usar la alimentación de los servos para diagnosticar OLED.
3. IR izquierdo/derecho: alimentar un módulo compatible cada vez a 3,3V y conectar OUT al GPIO asignado. Acercar/retirar la mano y registrar niveles en reposo y detección. El firmware espera LOW activo. Si permanece activo, ajustar sensibilidad y revisar luz/reflejos. No conectar salida de 5V directamente al ESP32.
4. TTP223: alimentación 3,3V y OUT a GPIO10. Tocar/soltar repetidamente, también a través del cartón real. Se espera HIGH momentáneo; si queda enclavado, revisar modo y polaridad. El firmware necesita una transición de liberado a activo.
5. Servo_Center: medir UBEC con multímetro primero; después conectar ambos servos sin brazos y con masa común. Se ordenan 90° inmediatamente; el mensaje serie no demuestra posición alcanzada. Montar brazos sin corriente.
6. Servo_Yaw/Servo_Pitch: un servo cada vez, sin carga ni brazo. Ejecutan una pequeña secuencia 85–95° una vez y mantienen 90°. Apagar ante vibración, calor o bloqueo. Sin movimiento: alimentación, masa, señal y attach. Sentido inverso: montaje y configuración final de dirección.
7. UBEC/adaptador: sin instrumentos de medida, Arduino no confirma tensión ni capacidad de corriente. Comprobar entrada nominal de 12V, medir salida 5V/polaridad sin carga y después bajo carga real de servos; registrar. 12V solo a la entrada. Comprobar continuidad y tensión de protoboard/cables con el estado de alimentación apropiado.
8. Cartón/soportes: inspeccionar estabilidad, holguras y tensión de cables físicamente. Un programa Arduino independiente no verifica resistencia estructural.

Probar módulos antes del conjunto y registrar observaciones en [pruebas](TESTING.md).
