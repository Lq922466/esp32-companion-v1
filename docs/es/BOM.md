# Lista de materiales

[English](../BOM.md) | [中文](../zh-CN/BOM.md) | [Español](BOM.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
Las cantidades corresponden a la configuración indicada por el propietario. No están confirmados los precios, enlaces de compra, modelo exacto de los sensores IR ni valores nominales del UBEC y del adaptador.

| Pieza | Cantidad | Uso y comprobaciones |
|---|---:|---|
| ESP32-C3 SuperMini | 1 | Controlador |
| OLED SSD1306 I²C 128×64, 0x3C | 1 | Cara animada |
| Servo SG90 | 2 | Yaw para giro lateral y pitch para asentimiento |
| Módulo digital de proximidad IR | 2 | Detección izquierda/derecha; modelo exacto pendiente |
| Módulo TTP223 | 1 | Entrada táctil |
| UBEC con salida regulada de 5V | 1 | Alimentación de servos; comprobar compatibilidad con entrada de 12V y corriente suficiente |
| Adaptador de 12V | 1 | Solo a la entrada del UBEC; polaridad y corriente pendientes |
| Protoboard grande existente | 1 | Distribución de señales de baja corriente |
| Cartón corrugado de 3mm | Según necesidad | Carcasa medida y cortada según las piezas reales; sin plantilla |
| Cables puente, conectores de servo, cable USB de datos | Según necesidad | Cableado y programación |
| Pegamento, fijaciones, aislamiento y sujeciones de cables | Según necesidad | Montaje mecánico; selección real pendiente |

Dimensionar el UBEC y las conexiones según la corriente de pico de ambos SG90 reales. No suponer valores idénticos en imitaciones. La configuración prudente de esta guía alimenta el ESP32 por USB; falta confirmar la alimentación final del controlador. Véanse [cableado](WIRING.md) y [seguridad](SAFETY.md).
