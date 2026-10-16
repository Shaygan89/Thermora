#include "DHT.h"
#include <DHT.h>

#define DHTPIN 26
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastDHTCheck = 0;

float temperature;
float humidity;

bool initDHT()
{
    dht.begin();

    delay(2000);

    float test = dht.readTemperature();

    if(isnan(test))
    {
        return false;
    }

    return true;
}

void updateDHT() {
    if (millis() - lastDHTCheck >= 2000) {
        lastDHTCheck = millis();

        temperature = dht.readTemperature();
        humidity = dht.readHumidity();
    }
}