# Troubleshooting / 故障排查
| Symptom | Checks and action |
|---|---|
| No upload port | Data-capable USB cable, correct port, board power, close serial programs; inspect BOOT/RESET procedure for this board |
| OLED scanner has no ACK | Supply/GND, swapped SDA/SCL, GPIO numbering, solder joints, compatible pull-ups and short wires |
| 0x3D instead of 0x3C | Confirm actual module; final code only uses 0x3C and reports 0x3D diagnostically |
| ACK but black screen | ACK proves bus response only; check SSD1306 vs SH1106 controller, 128×64 geometry, panel/reset/power and physical OLED test |
| HELLO visible but face absent | Capture serial after 1.5s, check face-frame counters and buffer; compare exact uploaded source; do not infer visible pixels from serial alone |
| IR always active | Test raw GPIO level separately; adjust module potentiometer, remove reflective surfaces, check ambient light and output polarity |
| Touch remains active | Check TTP223 toggle/momentary and polarity jumpers; firmware expects momentary active HIGH; test through actual shell |
| Servo does not move | UBEC output voltage, common ground, correct signal pin, servo enable, connector orientation; test one unloaded servo |
| Servo moves backward | Change relevant direction constant only after unloaded test; confirm mechanical yaw/pitch assignment |
| Jitter/reset during motion | Power droop and peak current, ground continuity, thin/long wires, breadboard contacts, mechanical stall; disconnect servos to isolate |
| Touch does not retrigger | Release then touch; respect 2200ms cooldown; boot-held touch is intentionally ignored |
| Both IR active | Centering is intended; not a left/right priority fault |

Record actual observations, power measurements, exact firmware hash and serial logs. Never replace a missing test with an expected result.
