#include <Arduino.h>
#include "../lib/DHT/DHT.h"

const int dhtPin = 5;

const char *ssid_name = "tes", *ssid_password = "12345678";

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  Serial.println(F("\nDEMO WIFI ESP8266"));

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println(F("Connecting to AP WiFi..."));
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid_name, ssid_password);
  while (!WiFi.isConnected())
  {
    Serial.print(F("#"));
    yield();
    delay(500);
  }

  Serial.print(F("Connected with IP = "));
  Serial.println(WiFi.localIP().toString());
}

void loop()
{
  Serial.println(F())
}