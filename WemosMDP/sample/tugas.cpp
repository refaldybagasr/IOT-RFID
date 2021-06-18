#include <Arduino.h>

const int pinBlue = 2;
const int pinRed = 0;
const int pinBuzzer = 5;
const int pinBtnBlue = 4;
const int pinBtnRed = 16;

void setup()
{
    pinMode(pinBlue, OUTPUT);
    pinMode(pinRed, OUTPUT);
    pinMode(pinBuzzer, OUTPUT);
    pinMode(pinBtnBlue, INPUT);
    pinMode(pinBtnRed, INPUT);
    Serial.begin(9600);
}

void loop()
{

    if (digitalRead(pinBtnBlue) == LOW)
    {
        digitalWrite(pinBlue, HIGH);
        digitalWrite(pinBuzzer, HIGH);
        Serial.println("LED Blue Menyala!");
        delay(1000);
    }
    else if (digitalRead(pinBtnRed) == LOW)
    {
        digitalWrite(pinRed, HIGH);
        digitalWrite(pinBuzzer, HIGH);
        Serial.println("LED Red Menyala!");
        delay(500);
    }
    else
    {
        digitalWrite(pinRed, LOW);
        digitalWrite(pinBlue, LOW);
        digitalWrite(pinBuzzer, LOW);
    }
}