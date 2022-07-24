//#include <ESP8266WiFi.h>
//#include "ghs.h"
//
//unsigned long wifi_previous_millis = 0, wifi_interval = WIFI_CONNECTION_CHECK_INTERVAL;
//
//void initWiFi();
//
//void setup() {
//  Serial.begin(115200);
//  initWiFi();
//  Serial.print("RSSI: ");
//  Serial.println(WiFi.RSSI());
//}
//
//void loop() {
//    unsigned long currentMillis = millis();
//    if (currentMillis - wifi_previous_millis >= wifi_interval){ // check for WiFi connection every 3 seconds
//      switch (WiFi.status()){
//        case WL_NO_SSID_AVAIL:
//          Serial.println("WiFi Network cannot be reached");
//          break;
//        case WL_CONNECTED:
//          break;
//        case WL_CONNECT_FAILED:
//          Serial.println("WiFi Connection failed");
//          break;
//      }
//      wifi_previous_millis = currentMillis;
//    }
//}
//
//void initWiFi() {
//  WiFi.mode(WIFI_STA);
//  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//  Serial.print("Connecting to WiFi Network: ");
//  Serial.println(WIFI_SSID);
//  while (WiFi.status() != WL_CONNECTED) {
//    Serial.print('.');
//    delay(500);
//  }
//  Serial.println();
//  Serial.print("Local IP address: ");
//  Serial.println(WiFi.localIP());
//  WiFi.setAutoReconnect(true); // reconnect automatically when connection is lost
//  WiFi.persistent(true);
//}
