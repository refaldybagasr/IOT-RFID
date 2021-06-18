#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include "MFRC522.h"

#define RST_PIN 5
#define SS_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(115200);

  SPI.begin();
  mfrc522.PCD_Init();

  WiFi.begin("Ryzen Master Race", "nvidiasucks");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Waiting for connection");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println(F("WiFi connected"));
  }
}

void loop()
{
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  String rfid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    rfid += mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ";
    rfid += mfrc522.uid.uidByte[i];
  }

  if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
  {
    HTTPClient http; //Declare object of class HTTPClient

    http.begin("http://9d1bd53a4691.ap.ngrok.io"); //Specify request destination

    http.addHeader("Content-Type", "application/json");
    String httpRequestData = "{\"rfid\" : \"" + rfid + "\"}";
    Serial.println(httpRequestData);
    int httpCode = http.POST(httpRequestData); //Send the request
    String payload = http.getString();         //Get the response payload

    Serial.println(httpCode); //Print HTTP return code
    Serial.println(payload);  //Print request response payload

    http.end(); //Close connection
  }
  else
  {
    Serial.println("Error in WiFi connection");
  }
  delay(2000);
}