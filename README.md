# ESP32

### Blink LED
Self-explanatory

### Servo Control
#### servo.py
Used for min, mid, max positions

#### servo_control_wireless.ino
This methodology use MQTT to connect to a public server to control the motor
positions via angular commands. See example as follows.

`mosquitto_pub -h broker.hivemq.com -t esp32/servo -m "int: angle"` <br>
`mosquitto_pub -h broker.hivemq.com -t esp32/servo -m "180"`