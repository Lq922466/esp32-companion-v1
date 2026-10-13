# PaperRobot V2
Robot de compañía de cartón de INNNX., inspirado en **Made by Z**. V2 sigue siendo una adaptación; no se afirma que sea un diseño totalmente independiente.

[English](README.md) | [中文](README.zh-CN.md)

## Funciones presentes en el código recuperado
Seis diseños de cara: normal, feliz, parpadeo, curiosa, tímida y dormida. Ojos sólidos, transiciones suaves y parpadeo. Los sensores IR desplazan **toda la cara**, incluidos ojos y boca, y controlan yaw. Ambos sensores activos centran la cara y la cabeza. El tacto activa una cara feliz y un asentimiento con pitch. Hay límites de ángulo y velocidad y reintentos de inicialización del OLED.

Son conclusiones del código. La compilación se documenta en [TESTING](docs/TESTING.md). No se ha comprobado el funcionamiento físico durante esta preparación; el propietario indica que el montaje está terminado y aportará las pruebas visuales.

## Hardware y montaje
ESP32-C3 SuperMini; SSD1306 128×64 I2C 0x3C, SDA GPIO0/SCL GPIO1; dos SG90, yaw GPIO4/pitch GPIO5; IR izquierdo GPIO6/derecho GPIO7; TTP223 GPIO10. UBEC de 5V para los servos y masa común. **El adaptador de 12V se conecta únicamente a la entrada del UBEC.** Se conserva la protoboard grande existente.

Carcasa de **cartón corrugado de 3mm, medido y cortado manualmente según las piezas reales**. No se utilizó ni se distribuye una plantilla PDF. Faltan medidas y fotografías reales del proceso.

Leer [SAFETY](docs/SAFETY.md) y [WIRING](docs/WIRING.md), ejecutar [pruebas independientes](docs/COMPONENT-TESTS.md) con los brazos de servo desmontados al principio, seguir [ASSEMBLY](docs/ASSEMBLY.md) y cargar el [código V2 completo](firmware/PaperRobotV2/PaperRobotV2.ino) según [FIRMWARE](docs/FIRMWARE.md).

## Documentación
[BOM](docs/BOM.md) · [WIRING](docs/WIRING.md) · [ASSEMBLY](docs/ASSEMBLY.md) · [COMPONENT-TESTS](docs/COMPONENT-TESTS.md) · [FIRMWARE](docs/FIRMWARE.md) · [TROUBLESHOOTING](docs/TROUBLESHOOTING.md) · [SAFETY](docs/SAFETY.md) · [TESTING](docs/TESTING.md) · [Créditos y diferencias](docs/ATTRIBUTION.md) · [Historial](CHANGELOG.md) · [Licencias](LICENSE-REVIEW.md)

## Material real pendiente
- Foto del robot terminado: pendiente de enlace real.
- Vídeo: pendiente; mostrar reposo, IR izquierdo/derecho/ambos y tacto.
- Fotos del montaje, medidas y resultados físicos: pendientes.

V2, V1 y los archivos históricos se conservan con sus hashes; los diagnósticos nuevos están identificados. No se ha aplicado una licencia general sin confirmar la titularidad y los permisos originales.
