#include <Arduino.h>

const int pinRed = 0;
const int pinPotensio = A0;
int valPotensio = 0;

void setup()
{
    pinMode(pinRed, OUTPUT);
    pinMode(pinPotensio, INPUT);
    Serial.begin(115200);
}

void loop()
{
    valPotensio = analogRead(pinPotensio);
    Serial.print("Nilai Potensio : ");
    Serial.println(valPotensio);
    analogWrite(pinRed, valPotensio);
    delay(500);
}