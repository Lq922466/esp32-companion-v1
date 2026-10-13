# Cableado

[English](../WIRING.md) | [中文](../zh-CN/WIRING.md) | [Español](WIRING.md)

[Índice de documentación](INDEX.md) · [Inicio](../../README.es.md)
Desconectar la alimentación antes de cablear. Los números GPIO corresponden al ESP32-C3, no a la posición física de los pines del conector.

| Dispositivo | Señal | GPIO | Alimentación |
|---|---|---:|---|
| OLED | SDA / SCL | 0 / 1 | 3,3V si el módulo lo admite; masa común |
| SG90 yaw | Señal | 4 | UBEC 5V y masa común |
| SG90 pitch | Señal | 5 | UBEC 5V y masa común |
| IR izquierdo | OUT digital | 6 | Alimentación y salida compatibles con 3,3V |
| IR derecho | OUT digital | 7 | Alimentación y salida compatibles con 3,3V |
| TTP223 | OUT | 10 | 3,3V para un módulo compatible; masa común |

```text
Adaptador 12V + / - → entrada UBEC + / -
Salida UBEC 5V → V+ de ambos servos
Salida UBEC GND → GND de servos y ESP32
USB → alimentación/programación del ESP32
ESP32 3,3V → módulos OLED/táctil/IR compatibles
GPIO del ESP32 → señales de la tabla anterior
```

**Nunca conectar 12V al ESP32, OLED, sensores, servos ni a los carriles de alimentación de la lógica.** Medir tensión y polaridad del UBEC antes de conectar servos. No unir 5V externos con los 5V USB sin verificar el circuito de alimentación de la placa.

Las entradas del ESP32-C3 son de 3,3V. Si un módulo IR necesita 5V o entrega 5V, comprobar su circuito y usar conversión de nivel adecuada. Una resistencia pull-up configurada por firmware no convierte tensión. Las pull-up de I²C deben estar en el lado de 3,3V. Consultar las fichas de la placa y módulos reales; no confiar únicamente en colores o fotos del vendedor.

Conservar la protoboard grande y comprobar si sus carriles están interrumpidos en el centro. Etiquetar 3,3V, 5V y GND. Para la corriente de los servos, preferir conexiones directas de capacidad nominal adecuada frente a recorridos largos por protoboard y cables finos. No cargar mecánicamente los conectores GPIO. Los colores de los SG90 varían: comprobar señal, positivo y negativo en cada unidad. Véase [seguridad](SAFETY.md).
