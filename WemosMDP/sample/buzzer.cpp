#include <Arduino.h>

const int pinBlue = 2;
const int pinBuzzer = 5;
const int pinTOMBOL = 4;

void setup()
{
    pinMode(pinBlue, OUTPUT);
    pinMode(pinBuzzer, OUTPUT);
    pinMode(pinTOMBOL, INPUT);
    Serial.begin(9600);
}

void loop()
{
    if (digitalRead(pinTOMBOL) == HIGH)
    {
        digitalWrite(pinBlue, LOW);
        digitalWrite(pinBuzzer, LOW);
        Serial.println("buzzer nyala");
        delay(1000);
    }
    else
    {
        digitalWrite(pinBlue, HIGH);
        digitalWrite(pinBuzzer, HIGH);
        delay(1000);
    }
}