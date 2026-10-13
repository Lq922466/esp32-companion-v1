# Seguridad y precauciones

[English](../SAFETY.md) | [中文](../zh-CN/SAFETY.md) | [Español](SAFETY.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
- Conectar el adaptador de 12V solo a un UBEC que admita esa entrada. Verificar salida 5V y polaridad antes de conectar servos.
- Esta guía alimenta el controlador por USB. No aplicar 12V a módulos de lógica, servos ni pines ESP32; no realimentar USB desde otra fuente.
- Mantener masa común y comprobar compatibilidad de lógica 3,3V, capacidad de corriente y aislamiento. Desconectar fuentes antes de cambiar cables.
- Los servos reciben 90° al arrancar. Quitar brazos en el primer encendido: el software desconoce el centro mecánico. Mantener dedos, cables y cartón lejos de atrapamientos. Apagar ante bloqueo, ruido anormal, vibración o calor.
- No impedir que el eje siga su orden. Equilibrar la cabeza y comprobar fijaciones. Recorrido y calibración de pulso varían entre imitaciones SG90.
- El cartón es combustible. Ventilar UBEC y conexiones; detener ante calor, humo u olor. No dejar funcionando sin vigilancia ni cubrir conexiones activas con pegamento.
- Cortar sobre una base lejos de las manos. Dejar enfriar pegamento caliente antes de instalar electrónica; proteger placas de fijaciones conductoras y presión del pegamento.

Véanse [cableado](WIRING.md) y [primeras pruebas](COMPONENT-TESTS.md).
