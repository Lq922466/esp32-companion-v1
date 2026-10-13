# Evidencia de compilación y pruebas físicas

[English](../TESTING.md) | [中文](../zh-CN/TESTING.md) | [Español](TESTING.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
Ya existen [resultados JSON](../compile-results.json) y [versiones del entorno](../compile-logs/environment.txt); registros completos en docs/compile-logs. Compilación, carga y prueba física son pasos distintos. Los artefactos históricos no prueban una compilación nueva correcta.

## Registro físico: pendiente en esta tarea
| Comprobación | Comportamiento esperado | Resultado real / evidencia |
|---|---|---|
| USB y serie | Mensajes a 115200 y placa alimentada | Pendiente |
| UBEC sin carga | 5V regulados medidos y polaridad correcta | Pendiente |
| OLED | ACK 0x3C y píxeles realmente visibles | Pendiente |
| IR izquierdo/derecho | Niveles brutos cambian independientemente | Pendiente |
| TTP223 | Activación momentánea y retorno al soltar | Pendiente |
| Yaw/pitch sin carga | Centro 90° y movimientos prudentes | Pendiente |
| Cara en reposo | Ojos sólidos, parpadeo, curiosa/tímida aleatoria; sueño a 45s | Pendiente |
| Integración IR lateral | Cara completa ±10px y yaw sigue | Pendiente |
| Ambos IR | Cara/yaw centrados | Pendiente |
| Integración táctil | Feliz y un asentimiento; soltar/tocar tras espera | Pendiente |
| Tacto con IR | Cara sigue IR, pitch asiente y yaw centrado | Pendiente |
| Funcionamiento sostenido | Sin reinicios, bloqueos, calor o tensión de cables; registrar duración | Pendiente |

Registrar fecha, placa/núcleo/bibliotecas, SHA256, cableado real, polaridad de entradas, medidas eléctricas, observador, serie y fotos/vídeo reales. Marcar aprobado/fallido solo tras observar. Esta tarea no afirma cargas en hardware, acceso al puerto ni aprobación física por prueba.

## Nueva compilación: 2026-10-13
Los 11 programas seleccionados aprobaron para `esp32:esp32:esp32c3:CDCOnBoot=cdc`. Núcleo ESP32 3.3.12; ESP32Servo 3.2.1; SSD1306 2.5.17; GFX 1.12.6; BusIO 1.17.4.

Los primeros intentos encontraron rutas largas de Windows y errores de limpieza de caché. Se resolvieron usando el mapeo corto R: existente y una ruta de compilación D: separada, sin modificar código recuperado. Registros finales y hashes en los enlaces anteriores. Se conservaron las variantes históricas, pero no se recompilaron todas.

| Programa | Compilación | Prueba física |
|---|---|---|
| [tests/ControllerSerial/ControllerSerial.ino](../../tests/ControllerSerial/ControllerSerial.ino) | Aprobada | No realizada en esta tarea |
| [tests/IR_Left/IR_Left.ino](../../tests/IR_Left/IR_Left.ino) | Aprobada | No realizada en esta tarea |
| [tests/IR_Right/IR_Right.ino](../../tests/IR_Right/IR_Right.ino) | Aprobada | No realizada en esta tarea |
| [tests/OLED_Display/OLED_Display.ino](../../tests/OLED_Display/OLED_Display.ino) | Aprobada | No realizada en esta tarea |
| [tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino](../../tests/OLED_I2C_Scanner/OLED_I2C_Scanner.ino) | Aprobada | No realizada en esta tarea |
| [tests/Servo_Center/Servo_Center.ino](../../tests/Servo_Center/Servo_Center.ino) | Aprobada | No realizada en esta tarea |
| [tests/Servo_Pitch/Servo_Pitch.ino](../../tests/Servo_Pitch/Servo_Pitch.ino) | Aprobada | No realizada en esta tarea |
| [tests/Servo_Yaw/Servo_Yaw.ino](../../tests/Servo_Yaw/Servo_Yaw.ino) | Aprobada | No realizada en esta tarea |
| [tests/Touch_TTP223/Touch_TTP223.ino](../../tests/Touch_TTP223/Touch_TTP223.ino) | Aprobada | No realizada en esta tarea |
| [firmware/PaperRobotV2/PaperRobotV2.ino](../../firmware/PaperRobotV2/PaperRobotV2.ino) | Aprobada | No realizada en esta tarea |
| [firmware/archive/PaperRobotV1/PaperRobotV1.ino](../../firmware/archive/PaperRobotV1/PaperRobotV1.ino) | Aprobada | No realizada en esta tarea |

## Demostración del propietario: 2026-10-13
Se aportó [vídeo real](../../media/PaperRobotV2-demo.mp4), publicado como MP4 compatible con navegador y fotograma real. La decodificación completa aprobó. Es evidencia de la construcción; hash cargado y registro físico por prueba siguen sin confirmar. La tabla continúa pendiente. Véase [procedencia del vídeo](MEDIA.md).
