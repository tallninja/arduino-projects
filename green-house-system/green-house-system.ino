#include "ghs.h"        // Include the Wi-Fi library

const char* ssid     = WIFI_SSID;         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = WIFI_PASSWORD;     // The password of the Wi-Fi network

unsigned long dht_previous_millis = 0, dht_interval = DHT_INTERVAL;

float temperature = 0.0;
float humidity = 0.0;

void setup() {
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
//  WiFi.begin(ssid, password);             // Connect to the network
//  Serial.print("Connecting to: ");
//  Serial.print(ssid);
//
//  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
//    delay(500);
//    Serial.print('.');
//  }
//
//  Serial.println('\n');
//  Serial.println("Connection established!");  
//  Serial.print("IP address:\t");
//  Serial.println(WiFi.localIP());        // Send the IP address of the ESP8266 to the computer
////  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
}

void loop() { 
  unsigned long dht_current_millis = millis();
  if (dht_current_millis - dht_previous_millis >= dht_interval) {
    dht_previous_millis = dht_current_millis;
    float new_temp = dht.readTemperature();
    if (isnan(new_temp)) {
      Serial.println("Failed to read temperature from the DHT sensor...");
    }
    else {
      temperature = new_temp;
      Serial.print("Temperature: ");
      Serial.println(temperature);
    }
    float new_hum = dht.readHumidity();
    if (isnan(new_hum)) {
      Serial.println("Failed to read humidity from the DHT sensor...");
    }
    else {
      humidity = new_hum;
      Serial.print("Humidity: ");
      Serial.println(humidity);
    }
  }
}
