# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Toolchain

- **Arduino sketches (`.ino`)**: Flash via Arduino IDE or `arduino-cli`. The ESP32 board package must be installed.
- **Python scripts**: Require `gpiozero` and `pigpio` (with `pigpiod` daemon running). Intended to run directly on a Raspberry Pi or similar SBC, not the ESP32.

## Repository Structure

This is a collection of standalone ESP32/embedded projects. Each subdirectory is an independent project with no shared build system.

### `servo-control/`

Two separate approaches to servo control:

- **`servo_control_wireless.ino`** — Arduino sketch for the ESP32. Connects to WiFi, subscribes to the MQTT topic `esp32/servo` on a broker, and writes the received integer (angle 0–180) to a servo on GPIO 18. Uses `PubSubClient` and `ESP32Servo` libraries. The attach/write/detach pattern in `set_duty_cycle()` allows the physical switch to operate independently of the servo.

- **`servo.py`** — Python script using `gpiozero` with `PiGPIOFactory`. Cycles the servo through min → mid positions on GPIO 18. Useful for testing PWM pulse widths (`min_pulse_width=0.5ms`, `max_pulse_width=2.5ms`).

## Configuration

The `.ino` sketch requires WiFi and MQTT credentials set at the top of the file:

```cpp
const char* ssid = "NETWORK_NAME";
const char* password = "NETWORK_PASSWORD";
const char* mqtt_server = "broker.hivemq.com"; // or a local broker IP
const int mqtt_port = 1883;
```

## Sending Commands

```bash
# Send an angle (0–180) to the servo via MQTT
mosquitto_pub -h broker.hivemq.com -t esp32/servo -m "180"
```

## Libraries Required (Arduino)

- `PubSubClient` — MQTT client
- `ESP32Servo` — Servo control for ESP32 (avoids conflicts with built-in `Servo.h`)
- `WiFi.h` — Built into the ESP32 Arduino core
