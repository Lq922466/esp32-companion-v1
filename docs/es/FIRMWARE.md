# Firmware completo y explicación

[English](../FIRMWARE.md) | [中文](../zh-CN/FIRMWARE.md) | [Español](FIRMWARE.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
El [código completo PaperRobotV2.ino](../../firmware/PaperRobotV2/PaperRobotV2.ino) se conserva sin cambios. La [copia V1](../../firmware/archive/PaperRobotV1/PaperRobotV1.ino) está en un directorio separado. Las variantes históricas son evidencia de procedencia; no deben colocarse juntas en un mismo directorio de programa Arduino.

## Compilar y cargar
Instalar soporte ESP32 en Arduino IDE y seleccionar **ESP32C3 Dev Module**, objetivo genérico compatible, verificando la SuperMini real. Instalar Adafruit GFX, Adafruit SSD1306, Adafruit BusIO y ESP32Servo. Wire está incluido en el núcleo ESP32. Versiones usadas: [pruebas](TESTING.md). Referencia oficial: [instalación de Espressif](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

Abrir V2, seleccionar el puerto real y habilitar USB CDC on boot cuando corresponda para serie USB. Compilar y después cargar. Monitor serie: 115200 baudios. setup continúa sin esperar conexión serie al ordenador. Si falta el puerto, revisar cable de datos, cerrar otros usuarios del puerto y seguir BOOT/RESET de la placa. Compilar no demuestra carga correcta ni movimiento.

Desde la raíz del repositorio:
```sh
arduino-cli compile --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc firmware/PaperRobotV2
```

## Comportamiento del código
| Área | Función |
|---|---|
| Config | Pines, polaridad activa, límites, tiempos, orientación OLED y habilitación de servos |
| StableInput | Antirrebote 40ms y flanco de activación; tacto mantenido al arrancar exige soltar y volver a tocar |
| Axis | Servo 50Hz; extremos de pulso 1000–2000μs; centro 90°; máximo 1° por 20ms |
| updateBehavior | IR 1 izquierda, 2 derecha, 3 ambos; cara ±10px; yaw ±10°; espera táctil 2200ms |
| Estado feliz por tacto | Feliz 1800ms; un asentimiento suave de 1200ms y 6°; yaw vuelve hacia el centro |
| ReferenceFace | Seis conjuntos de expresión, ojos sólidos; transición smoothstep 180ms; boca, rubor y Z se desplazan juntos |
| drawFace | Intervalo 40ms, parpadeo 220ms, desplazamiento horizontal compartido y envío del búfer |
| serviceOLED | Espera inicial 300ms; reintento cada 1s; comprobación cada 2s; HELLO durante 1500ms antes de la cara |
| Reposo/sueño | Expresiones normal/curiosa/tímida aleatorias; sueño tras 45s sin actividad; cabeza centrada en reposo |

El parpadeo se dibuja como animación de cierre: el índice 2 de la tabla no se selecciona como emoción persistente. El control temporal de glance en reposo no mueve la cara en esta revisión; el desplazamiento lateral real depende de IR. No hay cámara, voz, red ni diálogo de IA.

IR usa LOW activo y tacto HIGH activo por defecto; confirmarlos por separado. Ambos IR activos centran cara/yaw. Durante tacto/felicidad, IR sigue desplazando toda la cara, pero yaw se centra y el asentimiento pitch tiene prioridad. Boca/punto, rubor y Z comparten el desplazamiento de los ojos.

`SERVOS_ENABLED=false` permite diagnosticar pantalla/sensores sin mover servos. `CALIBRATION_ONLY=true` ordena el centro; attach inicial sigue enviando centro inmediatamente. Dirección solo ±1, modificada tras pruebas sin carga. Ampliar límites exige revisar holguras. ACK OLED y búfer no vacío no prueban píxeles visibles.
