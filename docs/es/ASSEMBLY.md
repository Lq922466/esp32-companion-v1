# Proceso de fabricación y montaje

[English](../ASSEMBLY.md) | [中文](../zh-CN/ASSEMBLY.md) | [Español](ASSEMBLY.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
Esta es una guía de reproducción basada en el hardware especificado, no un registro fotográfico completo del trabajo real del propietario. Están confirmados el cartón corrugado de 3mm, la medición y el corte manuales, la protoboard grande existente y el UBEC. Faltan dimensiones exactas, fijaciones, cronología y fotos del proceso. El [vídeo real](MEDIA.md) ya está disponible, pero no sustituye ese registro.

1. Inventariar las piezas e inspeccionar conexiones. Probar primero USB/controlador y después OLED, cada IR, tacto y cada servo por separado; registrar resultados.
2. Medir OLED, placa, protoboard, conectores y espacio ocupado por los servos reales. Marcar los paneles de cabeza y cuerpo directamente sobre cartón de 3mm. Reservar ventana del OLED, líneas de detección, acceso USB, abertura desmontable de mantenimiento y holgura de cables. Cortar sobre una base; no se necesita plantilla PDF.
3. Presentar el cuerpo alrededor de la protoboard y el UBEC. Mantener accesibles los conectores de alimentación, aislar la parte inferior de las placas y dejar ventilación. No tapar con pegamento USB, botones BOOT/RESET ni contactos expuestos.
4. Quitar ambos brazos de servo y ejecutar la prueba de centrado a 90°. Desconectar la corriente y montar los brazos según la posición neutra medida. No forzar un eje alimentado.
5. Se recomienda yaw alrededor de un eje vertical en cuerpo/cuello y pitch alrededor de un eje horizontal que soporte la cabeza. Es una disposición funcional recomendada, no una confirmación del montaje interno real. Equilibrar la cabeza, reforzar los soportes de cartón y comprobar la holgura de ambos ejes sin corriente.
6. Montar OLED sin ejercer presión sobre su PCB. Colocar IR a izquierda/derecha con detección despejada y tacto tras una superficie fina accesible. Probar a través del cartón real; grosor y fijación afectan a la sensibilidad.
7. Dejar holgura de cable para yaw/pitch y sujetarlo lejos de los brazos. Conectar primero masa común, luego señales y fuentes adecuadas. Medir el UBEC antes de conectarlo.
8. Cargar V2 primero sin carga mecánica. Los límites yaw 80–100° y pitch 82–98° son límites de software, no garantía de seguridad mecánica. Verificar centro, sentido y recorrido libre antes de colocar la cabeza y probar gradualmente.
9. Mantener acceso de mantenimiento hasta completar [el registro de pruebas](TESTING.md). Cerrar la carcasa tras comprobar calor, tensión de cables, estabilidad frente a reinicios y puntos de atrapamiento.

## Registro real pendiente
| Etapa | Fecha | Foto real del proceso | Medidas / observación |
|---|---|---|---|
| Piezas y pruebas de módulos | Pendiente | Pendiente | Pendiente |
| Marcado y corte del cartón | Pendiente | Pendiente | Dimensiones de paneles pendientes |
| Fijación y centrado de servos | Pendiente | Pendiente | Orientación de brazos pendiente |
| Cableado protoboard/UBEC | Pendiente | Pendiente | Alimentación final del controlador sin confirmar |
| Montaje y comprobaciones finales | Pendiente | Pendiente | Pendiente |

La tabla no constituye validación física realizada. Véanse [pruebas de componentes](COMPONENT-TESTS.md), [cableado](WIRING.md) y [seguridad](SAFETY.md).
