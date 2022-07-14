/*
* Author: Ernest Wambua
* Date: 14/07/2022
*/

#include <ArduinoJson.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <ArduinoMqttClient.h> // MQTT library
#include <WiFiNINA.h> // Wi-Fi library
#include "wifi_secrets.h"

const int RxPin = 0, TxPin = 1;
const uint32_t GPSBaud = 4800;
char *wifi_ssid = WIFI_SSID;
char *wifi_password = WIFI_PASSWORD;
const char *mqtt_broker = "test.mosquitto.org"; // mqtt broker
int port = 1883; // tcp port
const char *topic = "gps_location";
const int interval =  8000; // interval for sending messages (after 8 seconds)
unsigned long previousMillis = 0;
int count = 0;

TinyGPSPlus gps; // gps object
SoftwareSerial ss(RxPin, TxPin); // comm btn arduino and gps
WiFiClient wifiClient; // creates a wifi client
MqttClient mqttClient(wifiClient); // connects the wifi client to the mqtt client

void setup() {
  Serial.begin(9600);
  ss.begin(GPSBaud);
  
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
  // getting gps data
  DynamicJsonDocument doc(1024); // arduino json
  String locationData; // location data in JSON format
  
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
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

// References
// https://docs.arduino.cc/tutorials/uno-wifi-rev2/uno-wifi-r2-mqtt-device-to-device
// https://create.arduino.cc/projecthub/ruchir1674/how-to-interface-gps-module-neo-6m-with-arduino-8f90ad
// https://github.com/mikalhart/TinyGPSPlus/blob/master/examples/DeviceExample/DeviceExample.ino
// https://arduinojson.org/?utm_source=meta&utm_medium=library.properties
