#include <ArduinoMqttClient.h> // MQTT library
#include <WiFiNINA.h> // Wi-Fi library
#include "wifi_secrets.h"

char *wifi_ssid = WIFI_SSID;
char *wifi_password = WIFI_PASSWORD;
const char *mqtt_broker = "test.mosquitto.org"; // mqtt broker
int port = 1883; // tcp port
const char *topic = "gps_location";
const int interval =  8000; // interval for sending messages (after 8 seconds)
unsigned long previousMillis = 0;
int count = 0;

WiFiClient wifiClient; // creates a wifi client
MqttClient mqttClient(wifiClient); // connects the wifi client to the mqtt client

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for USB port to be connected
  }

  // attempt to connect to the wifi network
  Serial.print("Connecting to WiFi network: ");
  Serial.println(wifi_ssid);
  while (WiFi.begin(wifi_ssid, wifi_password) != WL_CONNECTED) {
    Serial.print(".");
    delay(3000);
  }
  Serial.println("Connected to WiFi network...");
  Serial.println();

  // attempt to connect to mqtt broker
  Serial.print("Connecting to MQTT broker: ");
  Serial.println(mqtt_broker);
  if (!mqttClient.connect(mqtt_broker, port)) {
    Serial.print("Error connecting to MQTT broker: ");
    Serial.println(mqttClient.connectError());
    while (1);
  }
  Serial.println("Connected to MQTT broker...");
  Serial.println();
}

void loop() {
  mqttClient.poll(); // polling sends keep alive in order to avoid being disconnected to the broker
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Sending location data to topic: ");
    Serial.println(topic);
    Serial.println();
    mqttClient.beginMessage(topic);
    mqttClient.print("Hello world");
    mqttClient.endMessage();
    Serial.println();
  }
}
