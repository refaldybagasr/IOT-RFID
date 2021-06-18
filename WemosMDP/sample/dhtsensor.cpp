#include <Arduino.h>
#include "../lib/DHT/DHT.h"

const int dhtPin = 5;

DHT DHTSensor(dhtPin, DHT11);

void setup()
{
  Serial.begin(9600);
  Serial.println("Test DHT11 !!");
  delay(1000);

  DHTSensor.begin();
}

void loop()
{
  float humidityRead = DHTSensor.readHumidity();
  float tempRead = DHTSensor.readTemperature();

  if (isnan(humidityRead) || isnan(tempRead))
  {
    Serial.print("Humidity data is empty!!");
  }
  Serial.print("Humidity: ");
  Serial.println(humidityRead);
  Serial.print("Temperature: ");
  Serial.println(tempRead);
  delay(2000);
}