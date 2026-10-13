# Robot de compañía ESP32 V1

**INNNX. · Robots & IoT**

[简体中文](README.zh-CN.md) | **Español** | [English](README.en.md) · [Inicio](../README.md)

## 1. Introducción

Este proyecto es un prototipo de robot de compañía basado en ESP32. El repositorio publica un sketch Arduino para el módulo de expresión facial OLED; no representa un robot completo terminado. V1 se inspira en un proyecto de referencia y sigue en desarrollo.

## 2. Objetivos

- Explorar la construcción de un robot de compañía y adaptar materiales y configuración a mis necesidades.
- Partir del código de expresión facial OLED existente para avanzar en la validación física.
- Documentar con precisión el código, los resultados de pruebas y las versiones, distinguiendo los resultados reales de los planes futuros.

Son objetivos de desarrollo, no resultados ya alcanzados.

## 3. Hardware y tecnologías

| Elemento | Información confirmada mediante los archivos existentes |
| --- | --- |
| Placa | Familia ESP32; modelo concreto pendiente de confirmación física |
| Pantalla | SSD1306 OLED, 128×64 |
| Comunicación | I²C; dirección `0x3C` en el código |
| Pines | SDA GPIO 0, SCL GPIO 1; compatibilidad con la placa real pendiente de confirmar |
| Entorno | Arduino IDE, soporte para placas ESP32 |
| Lenguaje y dependencias | Arduino/C++, Wire, Adafruit GFX, Adafruit SSD1306 |
| Programa | [`firmware/oled-face/oled-face.ino`](../firmware/oled-face/oled-face.ino) |
| Puerto serie | `115200` baudios |

No es una lista completa de materiales verificada físicamente. Los demás materiales, la alimentación y los detalles de las adaptaciones no están documentados.

## 4. Funciones implementadas

Aquí «implementado» significa únicamente que el código está escrito:

| Función | Estado del código | Validación física |
| --- | --- | --- |
| Inicialización de I²C y SSD1306 | Código escrito | No confirmada |
| Limpieza del búfer, dibujo de ojos y boca y envío a la pantalla | Código escrito; gráficos estáticos | No confirmada |
| Mensajes de estado por puerto serie | Código escrito; la rama de éxito muestra `OLED OK!`; la de fallo muestra `OLED ERROR` y se detiene | No confirmada |

Los ojos usan `fillRoundRect()`, la boca dos llamadas a `drawLine()` y `display.display()` envía el búfer. `loop()` está vacío. No hay implementaciones de animación facial, conversación, conectividad de red, voz, control de movimiento ni comportamiento autónomo.

## 5. Estado actual

**V1 — Inspired Prototype / In Development**

Esta actualización solo revisó archivos y código; no conectó hardware ni recompiló, cargó o probó el programa. El repositorio no contiene registros de pruebas físicas que confirmen el funcionamiento de la pantalla. Esto no demuestra que nunca se haya probado, sino que no puede confirmarse actualmente. El mensaje de éxito del programa no prueba por sí solo la validación física.

El alcance público es el sketch OLED existente y su documentación; los módulos no documentados no se consideran implementados.

## 6. Inspiración y agradecimientos de V1

**Fuente original: [Creador original en Xiaohongshu](https://xhslink.cn/m/5y0F9KIVkvd).**

V1 se inspira en el proyecto robótico compartido públicamente por este creador. Tomé como referencia sus ideas de construcción y adapté algunos materiales y la configuración del hardware a mis necesidades. Por tanto, V1 no es un diseño totalmente independiente y original. Agradezco al creador que compartiera sus ideas de construcción.

Al comprobar el enlace, la página de destino solicitó iniciar sesión y no se pudo confirmar el nombre. Se utiliza «Creador original en Xiaohongshu» sin inventar un usuario. La atribución se basa en la información proporcionada por el autor de este proyecto; los detalles técnicos del proyecto original y la procedencia del código del sketch no se han verificado de forma independiente.

Esta actualización no copia código, imágenes ni otros materiales del creador. Los agradecimientos no equivalen a una autorización de uso. Sin un desglose de los cambios, no se inventa una comparativa de hardware. **La fuente y los agradecimientos de V1 deben conservarse permanentemente, aunque las versiones posteriores adopten otros diseños.**

## 7. Planes para V2 y V3

| Versión | Dirección | Estado |
| --- | --- | --- |
| V1 | Inspired Prototype | In Development |
| V2 | Independent Design | Planned |
| V3 | Future Independent Development | Planned |

V2, V3 y las versiones posteriores se planifican con soluciones diseñadas y desarrolladas de forma independiente por INNNX., sin basarse en el diseño de construcción robótica de este creador. Actualmente son solo planes: no hay versiones terminadas, funciones concretas ni resultados técnicos que confirmar. La originalidad completamente independiente deberá evaluarse según la implementación real, las dependencias y las fuentes; un plan no demuestra por sí solo esa originalidad.

## 8. Uso y limitaciones conocidas

1. Comprueba la interfaz OLED, la alimentación, los niveles eléctricos y el cableado según tu placa real. Confirma la compatibilidad de SDA GPIO 0, SCL GPIO 1 y dirección `0x3C`; no está garantizada para todas las placas ESP32.
2. Instala el soporte ESP32 correspondiente y las bibliotecas Adafruit GFX y Adafruit SSD1306 en Arduino IDE.
3. Abre el sketch indicado, selecciona la placa y el puerto correctos y revisa la configuración antes de compilar y cargar por tu cuenta.
4. Observa la salida serie a `115200` baudios y la pantalla físicamente. Registra el resultado y el hardware utilizado; no presentes el comportamiento esperado como una prueba realizada.

Este procedimiento no se probó físicamente en esta actualización. El código dibuja una cara estática una sola vez, se detiene si falla la inicialización y deja `loop()` vacío. El repositorio no contiene esquema completo de cableado, lista completa de materiales, evidencias de validación física ni registro de autorización para materiales del creador. Esta actualización no publica claves, información personal ni materiales de terceros.

[Inicio](../README.md) · [Robots & IoT](https://github.com/Lq922466/Lq922466/blob/main/portfolio/robots-iot.md)
