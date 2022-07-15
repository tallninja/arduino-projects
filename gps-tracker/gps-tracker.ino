/*
* Author: Ernest Wambua
* Date: 14/07/2022
*/

#include <ArduinoJson.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ArduinoMqttClient.h> // MQTT library
#include <WiFiEsp.h> // Wi-Fi library
#include <WiFiEspUdp.h>
#include <WiFiEspClient.h>
#include "wifi_secrets.h"

const uint32_t GPSBaud = 4800;
char *wifi_ssid = WIFI_SSID;
char *wifi_password = WIFI_PASSWORD;
int wifi_status = WL_IDLE_STATUS;
const char *mqtt_broker = "test.mosquitto.org"; // mqtt broker
int port = 1883; // tcp port
const char *topic = "gps_location";
const int interval =  8000; // interval for sending megps_ssages (after 8 seconds)
unsigned long previousMillis = 0;
int count = 0;

TinyGPSPlus gps; // gps object
SoftwareSerial gps_ss(0, 1); // RX, TX
SoftwareSerial wifi_ss(2, 3); // RX, TX
WiFiEspClient wifiClient; // creates a wifi client
MqttClient mqttClient(wifiClient); // connects the wifi client to the mqtt client

void setup() {
  Serial.begin(9600);
  gps_ss.begin(GPSBaud);
  while (!Serial); // wait for USB port connection
  initWifi(); // connect to WiFi network
  connectMqtt(); // connect to mqtt broker
}

void loop() {
  // getting gps data
  DynamicJsonDocument doc(1024); // arduino json
  String locationData; // location data in JSON format
  wifi_status = WiFi.status();
  // attempt to reconnect to wifi if we loose connection
  if (wifi_status != WL_CONNECTED) {
    connectWifi();
  }
  // attempt to reconnect to mqtt broker if we loose connection
  if (!mqttClient.connected()) {
    connectMqtt();
  }
  
  while (gps_ss.available() > 0) {
    if (gps.encode(gps_ss.read())) {
      // handle the gps data
      if (gps.date.isValid()) {
        doc["date"] = gps.date.day() + '/' + gps.date.month() + '/' + gps.date.year();
      }
      if (gps.time.isValid()) {
        doc["time"] = gps.time.hour() + ':' + gps.time.minute() + ':' + gps.time.second();
      }
      if (gps.location.isValid()) {
        doc["coords"][0] = gps.location.lat();
        doc["coords"][1] = gps.location.lng(); 
      }
      serializeJson(doc, locationData); // prints the JSON object to a string
    }

    if (millis() > 5000 && gps.charsProcessed() < 10) {
      Serial.println("No GPS detected: check wiring.");
      while(true);
    }
  }
  
  mqttClient.poll(); // polling sends keep alive in order to avoid being disconnected to the broker
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Sending location data to topic: ");
    Serial.println(topic);
    Serial.println(locationData); // print the gps location data
    mqttClient.beginMessage(topic);
    mqttClient.print(locationData); // send the gps location data
    mqttClient.endMessage();
    Serial.println();
  }
}

// WiFi connection
void initWifi() {
  wifi_ss.begin(9600); // initialize serial for ESP WiFi module
  WiFi.init(&wifi_ss); // initialize ESP module
  // check if WiFi module is connected
  wifi_status = WiFi.status();
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wifi shiled not present");
    while (true); // don't continue with execution
  }
  connectWifi();
}

void connectWifi() {
  // attempt to connect to the wifi network
  Serial.print("Connecting to WiFi network: ");
  Serial.println(wifi_ssid);
  while (wifi_status != WL_CONNECTED) {
    Serial.print(".");
    wifi_status = WiFi.begin(wifi_ssid, wifi_password);
    delay(500); // wait for 500 millis to attempt to reconnect to WiFi network
  }
  Serial.println("Connected to WiFi network...");
  Serial.println();
}

// attempt to connect to mqtt broker
void connectMqtt() {
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

// References
// https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device
// https://create.arduino.cc/projecthub/ruchir1674/how-to-interface-gps-module-neo-6m-with-arduino-8f90ad
// https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/DeviceExample/DeviceExample.ino
// https://arduinojson.org/?utm_source=meta&utm_medium=library.properties
// https://thingsboard.io/docs/samples/arduino/temperature/
