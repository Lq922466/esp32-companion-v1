# Recuperación y selección del código

[English](../SOURCE-RECOVERY.md) | [中文](../zh-CN/SOURCE-RECOVERY.md) | [Español](SOURCE-RECOVERY.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
La búsqueda cubrió el espacio del proyecto, Documents, escritorio, Downloads e inventario de archivos del usuario. Se excluyeron ejemplos de bibliotecas/plataformas Arduino y archivos generados de compilación. No se encontraron diagnósticos independientes anteriores de IR, tacto o servos en las entregas examinadas; se crearon para este paquete. Esto no demuestra que no existan copias en otro disco o cuenta.

Se conservan 22 archivos `.ino`, incluidas copias duplicadas y revisiones V2 antiguas. [SOURCE-MANIFEST.json](../../archive/SOURCE-MANIFEST.json) registra ubicaciones relativas de origen, destinos archivados y SHA256 de los bytes. Los originales solo se leyeron/copiaron; no se modificaron originales ni archivos sincronizados en sources.

El V2 seleccionado procede de `2026-10-13/referenced-chatgpt-conversation-this-is-an-5/outputs/PaperRobotV2/PaperRobotV2.ino`: contiene movimiento de toda la cara, seis expresiones, límites yaw/pitch y reintentos OLED. SHA256: `f95854ab6551c3beb8494961c1674d4b094c2d2fffccea68b301bfedeab2e7a0`. Se eligió según la última entrega recuperada y el comportamiento solicitado, no como prueba del contenido actualmente grabado en la placa.

SHA256 de V1: `57a4d9df3a0edf126e0a2f52362ebdcdbd98fd1127e92ec4bb1a0583ac03e699`. Controla dos servos izquierda/derecha; no debe tratarse como V2 yaw/pitch ni cargarse sin revisar su comportamiento mecánico.

Se inspeccionó [Lq922466/esp32-companion-v1](https://github.com/Lq922466/esp32-companion-v1), instantánea anterior `b30bdd8`. Sus archivos están en archive/prior-public-repository. Se clonó como referencia y posteriormente el propietario autorizó publicar V2 en el mismo repositorio. La instantánea conserva el estado previo. No se modificó el portafolio INNNX.

Se recompilaron V2 y V1 seleccionados y nueve diagnósticos ejecutables. Las demás copias históricas se conservan para comparación; no se afirma haberlas recompilado todas. [Pruebas](TESTING.md) separa expectativas de evidencia observada.
