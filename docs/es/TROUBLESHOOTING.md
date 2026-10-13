# Resolución de problemas

[English](../TROUBLESHOOTING.md) | [中文](../zh-CN/TROUBLESHOOTING.md) | [Español](TROUBLESHOOTING.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
| Síntoma | Comprobación y acción |
|---|---|
| No aparece puerto de carga | Cable USB de datos, puerto correcto, alimentación, cerrar programas serie y revisar BOOT/RESET de la placa |
| Escáner OLED sin ACK | Alimentación/masa, SDA/SCL invertidos, números GPIO, soldaduras, pull-up compatibles y cables cortos |
| 0x3D en lugar de 0x3C | Confirmar módulo real; el programa final solo usa 0x3C y comunica 0x3D como diagnóstico |
| ACK con pantalla negra | ACK solo demuestra respuesta del bus; comprobar SSD1306/SH1106, 128×64, panel/reset/alimentación y probar físicamente |
| HELLO visible pero sin cara | Capturar serie tras 1,5s, revisar contador de fotogramas y búfer y comparar código cargado; no inferir visualización solo por serie |
| IR siempre activo | Leer niveles brutos individualmente; ajustar potenciómetro, retirar superficies reflectantes y revisar luz/polaridad |
| Tacto permanece activo | Revisar modo enclavado/momentáneo y puentes de polaridad TTP223; se espera HIGH momentáneo; probar a través de carcasa real |
| Servo no se mueve | Tensión UBEC, masa común, GPIO de señal, habilitación, orientación del conector; probar uno sin carga |
| Servo gira al revés | Cambiar dirección correspondiente solo tras prueba sin carga; confirmar asignación mecánica yaw/pitch |
| Vibraciones/reinicio al moverse | Caída de tensión, corriente de pico, continuidad de masa, cables finos/largos, contactos de protoboard y bloqueo; desconectar servos para aislar |
| Tacto no se repite | Soltar y volver a tocar; respetar 2200ms; tacto mantenido al arrancar se ignora deliberadamente |
| Ambos IR activos | El centrado es intencionado; no es un fallo de prioridad |

Registrar observaciones reales, medidas eléctricas, hash exacto del firmware y mensajes serie. No sustituir una prueba ausente por el resultado esperado. Véanse [pruebas independientes](COMPONENT-TESTS.md) y [registro](TESTING.md).
