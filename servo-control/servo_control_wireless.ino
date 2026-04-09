#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>
#include "secrets.h"

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
const char* mqtt_server = MQTT_SERVER;
const int mqtt_port = 1883;
const char* topic = "esp32/servo";

WiFiClient espClient;
PubSubClient client(espClient);

Servo servo;
const int servoPin = 18;

void set_duty_cycle(int angle) {
  // attach/detach so the physical switch can be used independently
  servo.attach(servoPin);
  servo.write(angle);
  servo.detach();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  set_duty_cycle(message.toInt());
}

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected — IP: ");
  Serial.println(WiFi.localIP());
}

void setup_mqtt() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (client.connect("ESP32S_Client")) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Connection to MQTT broker failed");
  }

  client.subscribe(topic);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  setup_mqtt();
}

void loop() {
  client.loop();
}
