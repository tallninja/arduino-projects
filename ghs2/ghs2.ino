#include "ghs2.h"

int dehumidPin = 3;
int soilMoisturePin = A0;
int motorPin = 4;

float temperature = 0.0;
float humidity = 0.0;
float soilMoisture = 0.0;

unsigned long dht_previous_millis = 0, dht_interval = DHT_INTERVAL;
unsigned long sm_previous_millis = 0, sm_interval = 3000;

String dhtOutputProcessor(const String& var);

void setup() {
  pinMode(dehumidPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(soilMoisturePin, INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  readDhtData();
  readSoilMoisture();
  if (humidity > 65.0) {
    digitalWrite(dehumidPin, HIGH);
  }
  else
    digitalWrite(dehumidPin, LOW);

  if (temperature >= 28) {
    digitalWrite(motorPin, HIGH);
  }
  else
    digitalWrite(motorPin, LOW);

  if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.println(data);
    delay(10);
    if (data == 'A') {
      digitalWrite(dehumidPin, HIGH);
    }
    else if (data == 'a') {
      digitalWrite(dehumidPin, LOW);
    }
    else if (data == 'B') {
      digitalWrite(motorPin, HIGH);
    }
    else if (data == 'b') {
      digitalWrite(motorPin, LOW);
    }
  }
}

void readDhtData() {
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

void readSoilMoisture() {
  unsigned long sm_current_millis = millis();
  if (sm_current_millis - sm_previous_millis >= sm_interval) {
    soilMoisture = analogRead(soilMoisturePin);
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoisture);
    sm_previous_millis = sm_current_millis;
  }
}
