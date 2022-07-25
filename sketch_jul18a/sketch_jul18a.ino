#include <ESP8266WiFi.h>
#include "secrets.h"

unsigned long previousMillis = 0;
unsigned long interval = 30000;

void initWiFi();

void setup() {
  Serial.begin(115200);
  initWiFi();
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >=interval){
      switch (WiFi.status()){
        case WL_NO_SSID_AVAIL:
          Serial.println("Configured SSID cannot be reached");
          break;
        case WL_CONNECTED:
          break;
        case WL_CONNECT_FAILED:
          Serial.println("WiFi Connection failed");
          break;
      }
      previousMillis = currentMillis;
    }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  //The ESP8266 tries to reconnect automatically when the connection is lost
  WiFi.setAutoReconnect(true);
  WiFi.persistent(true);
}
