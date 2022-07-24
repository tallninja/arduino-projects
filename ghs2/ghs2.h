#ifndef GHS_H
#define GHS_H

#include <DHT.h>

#define DHT_INTERVAL 3000
#define DHTPIN 2 // digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

#endif /* GHS_H */
