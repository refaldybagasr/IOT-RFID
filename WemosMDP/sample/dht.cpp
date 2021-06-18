#include <Arduino.h>

#include "../lib/DHT/DHT.h"

const int pinLedMerah = 5;
const int pinLedBiru = 4;
const int pinBtn1 = 0;
const int pinBtn2 = 2;

void setup()
{
  pinMode(pinLedMerah, OUTPUT);
  pinMode(pinLedBiru, OUTPUT);
  pinMode(pinBtn1, INPUT);
  pinMode(pinBtn2, INPUT);

  Serial.begin(115200);
}

void loop()
{
  if (digitalRead(pinBtn1) == LOW)
  {
    //Jika BTN 1 ditekan
    Serial.print("BTN 1 ditekan");
    digitalWrite(pinLedMerah, HIGH);
    delay(500);
    digitalWrite(pinLedMerah, LOW);
    delay(500);
    digitalWrite(pinLedBiru, HIGH);
    delay(750);
    digitalWrite(pinLedBiru, LOW);
    delay(250);
    digitalWrite(pinLedMerah, HIGH);
    digitalWrite(pinLedBiru, HIGH);
    delay(750);
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedBiru, LOW);
    delay(250);
  }
  else
  {
    //Reset state
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedBiru, LOW);
  }
}