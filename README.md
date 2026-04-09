# ESP32

### Servo Control

#### servo.py
Cycles the servo through min, mid, and max positions using `gpiozero` on GPIO 18. Run directly on the host device.

#### servo_control_wireless.ino
Connects to WiFi and subscribes to the MQTT topic `esp32/servo`. Publishes an integer angle (0–180) to move the servo.

**Setup:** Copy `servo-control/secrets.h.example` to `servo-control/secrets.h` and fill in your WiFi and MQTT broker details.

**Usage:**
```bash
mosquitto_pub -h <mqtt_server> -t esp32/servo -m "180"
```
