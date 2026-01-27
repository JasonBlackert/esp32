#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "WIRELESS_NETWORK";
const char* password = "WIRELESS_PASSWORD";
const char* mqtt_server = "broker.hivemq.com"; // for testing purposes
const int mqtt_port = 1883;
const char* topic = "esp32/servo";

WiFiClient espClient;
PubSubClient client(espClient);

// const int DUTY_OFF = 105;
// const int DUTY_ON = 180;

Servo servo;
const int servoPin = 18;

void set_duty_cycle(int duty_cycle) {
  // attach, write, detach so light switch can be used independently
  servo.attach(servoPin);
  servo.write(duty_cycle);
  servo.detach();
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Read message in from MQTT topic esp32/servo
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  int duty_cycle = message.toInt();
  set_duty_cycle(duty_cycle);
}

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup_mqtt() {\
  Serial.println();
  Serial.print("Connecting to server ");
  Serial.println(mqtt_server);
  Serial.println(" on port ");
  Serial.println(mqtt_port);

  // Setup MQTT callback
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (client.connect("ESP32S_Client")) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Connection to MQTT broker failed");
  }

  client.subscribe("esp32/servo");
}

void setup() {
  Serial.begin(115200);
  delay(10);

  setup_wifi(); // Internet
  setup_mqtt(); // Callback
}

void loop() {
  // Maintain MQTT connection and handle incoming messages
  client.loop();
}
