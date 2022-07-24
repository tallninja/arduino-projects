//#include "ghs.h"
//
//DHT dht(DHTPIN, DHTTYPE);
//
//float temperature = 0.0;
//float humidity = 0.0;
//
//unsigned long dht_previous_millis = 0, dht_interval = DHT_INTERVAL;
//
//String dhtOutputProcessor(const String& var);
//
//void setup() {
//  Serial.begin(115200);
//  dht.begin();
//}
//
//void loop() {
//  unsigned long dht_current_millis = millis();
//  if (dht_current_millis - dht_previous_millis >= dht_interval) {
//    dht_previous_millis = dht_current_millis;
//    float new_temp = dht.readTemperature();
//    if (isnan(new_temp)) {
//      Serial.println("Failed to read temperature from the DHT sensor...");
//    }
//    else {
//      temperature = new_temp;
//      Serial.print("Temperature: ");
//      Serial.println(temperature);
//    }
//    float new_hum = dht.readHumidity();
//    if (isnan(new_hum)) {
//      Serial.println("Failed to read humidity from the DHT sensor...");
//    }
//    else {
//      humidity = new_hum;
//      Serial.print("Humidity: ");
//      Serial.println(humidity);
//    }
//  }
//}
//
//String dhtOutputProcessor(const String& var) {
//  if (var == "TEMPERATURE") {
//    return String(temperature);
//  }
//  else if (var == "HUMIDITY") {
//    return String(humidity);
//  }
//  else {
//    return String();
//  }
//}
//
