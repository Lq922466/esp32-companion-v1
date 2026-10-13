# PaperRobot V2
Robot de compañía de cartón de INNNX., inspirado en **Made by Z**. V2 sigue siendo una adaptación; no se afirma que sea un diseño totalmente independiente.

[English](README.md) | [中文](README.zh-CN.md)

## Funciones presentes en el código recuperado
Seis diseños de cara: normal, feliz, parpadeo, curiosa, tímida y dormida. Ojos sólidos, transiciones suaves y parpadeo. Los sensores IR desplazan **toda la cara**, incluidos ojos y boca, y controlan yaw. Ambos sensores activos centran la cara y la cabeza. El tacto activa una cara feliz y un asentimiento con pitch. Hay límites de ángulo y velocidad y reintentos de inicialización del OLED.

Son conclusiones del código. La compilación se documenta en [Compilación y pruebas físicas](docs/es/TESTING.md). No se ha comprobado el funcionamiento físico durante esta preparación; el propietario indica que el montaje está terminado y ha aportado el vídeo real mostrado abajo. No equivale a una prueba documentada de todas las funciones.

## Hardware y montaje
ESP32-C3 SuperMini; SSD1306 128×64 I2C 0x3C, SDA GPIO0/SCL GPIO1; dos SG90, yaw GPIO4/pitch GPIO5; IR izquierdo GPIO6/derecho GPIO7; TTP223 GPIO10. UBEC de 5V para los servos y masa común. **El adaptador de 12V se conecta únicamente a la entrada del UBEC.** Se conserva la protoboard grande existente.

Carcasa de **cartón corrugado de 3mm, medido y cortado manualmente según las piezas reales**. No se utilizó ni se distribuye una plantilla PDF. Faltan medidas y fotografías reales del proceso.

Leer [Seguridad](docs/es/SAFETY.md) y [Cableado](docs/es/WIRING.md), ejecutar [pruebas independientes](docs/es/COMPONENT-TESTS.md) con los brazos de servo desmontados al principio, seguir [Fabricación y montaje](docs/es/ASSEMBLY.md) y cargar el [código V2 completo](firmware/PaperRobotV2/PaperRobotV2.ino) según [Firmware y funciones](docs/es/FIRMWARE.md).

## Documentación
[Materiales](docs/es/BOM.md) · [Cableado](docs/es/WIRING.md) · [Fabricación y montaje](docs/es/ASSEMBLY.md) · [Pruebas y código](docs/es/COMPONENT-TESTS.md) · [Firmware y funciones](docs/es/FIRMWARE.md) · [Resolución de problemas](docs/es/TROUBLESHOOTING.md) · [Seguridad](docs/es/SAFETY.md) · [Compilación y pruebas físicas](docs/es/TESTING.md) · [Créditos y diferencias](docs/es/ATTRIBUTION.md) · [Historial](docs/es/CHANGELOG.md) · [Licencias](docs/es/LICENSE-REVIEW.md)

## Material real pendiente
- Foto del robot terminado: pendiente de enlace real.
- [Ver/descargar el vídeo real del propietario](https://github.com/Lq922466/esp32-companion-v1/raw/refs/heads/main/media/PaperRobotV2-demo.mp4): aproximadamente 74 segundos, convertido de IMG_3257.mov a MP4 compatible con navegadores.

[![Fotograma real extraído del vídeo](media/demo-preview.jpg)](https://github.com/Lq922466/esp32-companion-v1/raw/refs/heads/main/media/PaperRobotV2-demo.mp4)

La vista previa es un fotograma, no una fotografía independiente del producto terminado.
- Fotos del montaje, medidas y resultados físicos: pendientes.

V2, V1 y los archivos históricos se conservan con sus hashes; los diagnósticos nuevos están identificados. No se ha aplicado una licencia general sin confirmar la titularidad y los permisos originales.

## Índice en español

[Abrir toda la documentación en español](docs/es/INDEX.md)
