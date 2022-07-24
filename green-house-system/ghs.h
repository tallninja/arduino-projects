#ifndef GHS_H
#define GHS_H

#include <ThingSpeak.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

#define WIFI_SSID "Okay "
#define WIFI_PASSWORD "d1rtythieve5"
#define WIFI_INTERVAL 30000 // time interval to check for WiFi connection

#define BOT_TOKEN "5457792707:AAGYTrXTsPrQKJaKAURFKlgQmeULnsYxNHQ"
#define BOT_INTERVAL 10000
#define CHAT_ID "775672614"

#define WRITE_API_KEY "DKYNTBDAY8P1CEPM"
#define CHANNEL_NUMBER 1806044
#define THINGSPEAK_INTERVAL 15000

#define DHT_INTERVAL 3000
#define DHTPIN 23 // digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

#define SOIL_MOISTURE_PIN A0

#define PHONE_NUMBER "+254773303396"

DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

#endif /* GHS_H */
