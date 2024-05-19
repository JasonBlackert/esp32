#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "WIRELESS NETWORK";
const char* password = "WIRELESS PASSWORD";
const char* mqtt_server = "broker.hivemq.com"; //"10.0.0.12";
const int mqtt_port = 1883;
const char* topic = "esp32/servo";

WiFiClient espClient;
PubSubClient client(espClient);

Servo servo;
const int servoPin = 18;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  //int angle = message.toInt();
  //servo.write(angle);

  if (message == "0") {
    servo.write(0);
  } else if (message == "180") {
    servo.write(180);
  } else if (message == "75") {
    servo.write(75);
  } else if (message == "10") {
    servo.write(10);
  }
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


void setup() {
  Serial.begin(115200);
  delay(10);

  servo.attach(servoPin);
  servo.write(0); // Initialize the servo to 0 degrees

  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (client.connect("ESP32S_Client")) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.println("Connection to MQTT broker failed");
  }

  client.subscribe("esp32/servo");
}

void loop() {
  // Maintain MQTT connection and handle incoming messages
  client.loop();
}
