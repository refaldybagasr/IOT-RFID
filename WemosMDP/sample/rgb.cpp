#include <Arduino.h>

const int pinPotensio = A0;
const int pinB = 0, pinR = 2, pinG = 4;
int valPotensio = 0;

void setup()
{

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);

    Serial.begin(115200);
}

void loop()
{
    valPotensio = analogRead(pinPotensio);
    Serial.print("Nilai Potensio : ");
    Serial.print(valPotensio);
    digitalWrite(pinB, valPotensio >= 801 ? HIGH : LOW);
    digitalWrite(pinG, valPotensio >= 513 && valPotensio <= 800 ? HIGH : LOW);
    digitalWrite(pinR, valPotensio >= 256 && valPotensio <= 512 ? HIGH : LOW);
    delay(1000);
}