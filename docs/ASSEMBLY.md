# Assembly and build record / 制作与组装
This is a reconstruction guide based on the specified hardware, not a claimed photo-by-photo record of the owner's work. Confirmed facts: 3mm corrugated cardboard, hand measurement/cutting, existing large breadboard and UBEC. Exact dimensions, fasteners, chronology and photographs are pending.

1. Inventory parts and inspect connections. Test USB/controller first, then OLED, each IR sensor, touch and each servo separately; record results.
2. Measure the actual OLED, board, breadboard, connectors and servo envelope. Mark head/body panels directly on 3mm cardboard. Reserve OLED viewing area, sensor sight lines, USB access, removable service opening and cable movement clearance. Cut on a mat; no PDF pattern is required.
3. Dry-fit the body around the existing large breadboard and UBEC. Keep power connectors accessible, isolate board undersides, and leave ventilation. Do not glue over the USB socket, BOOT/RESET buttons or exposed contacts.
4. With both servo horns removed, run the 90-degree centering test. Disconnect power, then attach horns to the measured neutral position. Do not force a powered shaft.
5. Arrange yaw about a vertical axis at the body/neck; pitch about a horizontal axis supporting the head. This is a recommended functional arrangement, not a verified photograph of this build. Keep head mass balanced; reinforce cardboard at mounts and check both axes by hand with power off.
6. Mount the OLED in the head without stressing its PCB. Place IR sensors left/right with unobstructed detection paths; place touch under a thin accessible surface and test through the actual cardboard. Thickness and mounting can affect sensitivity.
7. Route wires with slack for yaw/pitch and secure them away from horns. Wire common ground first, then signals and rated supplies. Measure the UBEC before connection.
8. Upload final V2 initially without mechanical load. Default yaw 80–100°, pitch 82–98° are software limits, not proof of mechanical safety. Verify neutral, direction and free travel, then fit the head and test gradually.
9. Keep service access until every test in TESTING is recorded. Close the shell only after checking heat, wire strain, reset stability and pinch clearance.

## Owner build record to complete
| Stage | Date | Real photo | Measurements / observation |
|---|---|---|---|
| Parts and module tests | pending | pending | pending |
| Cardboard marking/cutting | pending | pending | panel dimensions pending |
| Servo mount and centering | pending | pending | horn orientation pending |
| Breadboard/UBEC and wiring | pending | pending | final ESP32 supply pending |
| Final assembly and checks | pending | pending | pending |

中文：先单件测试，再按实物测量裁切 3mm 瓦楞纸板；舵机先拆舵盘回中，再断电装舵盘。保留大面包板、检修口和线缆活动余量。上表待真实资料补全，不能当作已验证制作记录。
Español: probar cada módulo, medir y cortar cartón de 3mm, centrar servos sin brazos y montarlos sin corriente. Mantener acceso de mantenimiento y holgura de cables. El historial real está pendiente.
