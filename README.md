# BenQ Projector RS-232 (ESPHome External Component)

An ESPHome external component that:

- Polls a BenQ projector over RS-232 for power status
- Exposes the raw reply and power state as entities
- Provides a **native Home Assistant switch entity** to turn the projector on/off  
  (no HA template switch required)

---
## 🔌 Hardware

| I Used | Notes |
|----------------|-------|
| ESP-WROOM-32   | ESP Board with wifi |
| MAX232CSE      | RS-232 Serial interface  |



## 🔌 Wiring

| RS232 Converter | ESP32 |
|----------------|-------|
| TX             | TX    |
| RX             | RX    |
| GND            | GND   |
| VCC            | 3.3V / 5V |

---

## 📦 Install / Use

1. Place the file contents into your ESPHome folder in Home Assistant (I used Samba Share to access directory)
2. Open ESPHome Web UI in the ESPHome App (previously know as Add-Ons)
3. Assemble and add the ESP32 device into ESPHome (add firmware or whatever to get it in as new device, you'll write over anything when installing)
4. If you do not already have a `secrets.yaml` file:
   - Update `secrets.yaml.example` with the wifi information
   - Rename it to `secrets.yaml` and save
5. Validate the YAML in ESPHome
6. Install/flash the software to the device (this can take time, when you see magenta text displaying the status of the device it is done)


---

## 📝 Notes

- `optimistic: true`  
  Updates the switch state immediately when pressed

- `optimistic: false`  
  Updates only after the next RS-232 poll/reply

- No source changes are required to add basic power commands

- AI was used as a coding assistant, but the project was developed, tested,
  and integrated manually

---

## 📜 License

MIT License — see `LICENSE`
