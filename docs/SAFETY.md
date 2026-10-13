# Safety / 安全 / Seguridad
- 12V adapter connects only to a UBEC rated for that input. Verify output is 5V with correct polarity before attaching servos.
- Use USB for the controller in this guide. Do not feed 12V to any logic module, servo or ESP32 pin; do not backfeed USB from another supply.
- Keep grounds common; check 3.3V logic compatibility, current ratings and insulated connections. Disconnect supplies before rewiring.
- Servo startup commands 90° immediately. Remove horns for first startup; software cannot know the real mechanical neutral. Keep fingers, wires and cardboard clear of pinch points; stop power if a servo stalls, chatters or heats.
- Do not hold the shaft against its command. Balance head weight and check secure mounts. SG90 travel and pulse calibration vary among clones.
- Cardboard is combustible. Keep UBEC and connections ventilated; stop at heat, smoke or smell. Do not leave unattended or cover live connections in glue.
- Cut on a mat away from hands. Allow hot glue to cool before installing electronics; protect boards from conductive hardware and glue pressure.

中文：12V 仅接 UBEC 输入；舵机首次启动拆舵盘；共地、3.3V 电平、断电接线。堵转或发热立即断电。纸板可燃，保持通风和检修空间。
Español: 12V únicamente al UBEC; quitar brazos al primer encendido; masa común, lógica de 3,3V y cableado sin corriente. Cortar alimentación si hay bloqueo o calor.
