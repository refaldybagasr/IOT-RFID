#include <Arduino.h>

const int pinBlue = 2;
const int pinRed = 0;
const int pinGreen = 12;
const int pinBuzzer = 5;
const int pinBtn1 = 4;
const int pinBtn2 = 16;
const int pinPotensio = A0;
int valPotensio = 0;

void setup()
{
  pinMode(pinBlue, OUTPUT);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinBtn1, INPUT);
  pinMode(pinBtn2, INPUT);
  Serial.begin(115200);
}

void loop()
{

  if (digitalRead(pinBtn1) == LOW)
  {
    digitalWrite(pinRed, HIGH);
    delay(2000);
    digitalWrite(pinGreen, HIGH);
    delay(2000);
    digitalWrite(pinBlue, HIGH);
    delay(2000);
    digitalWrite(pinBuzzer, HIGH);
    delay(1000);
  }
  else if (digitalRead(pinBtn2) == LOW)
  {
    valPotensio = analogRead(pinPotensio);
    Serial.println("Nilai Potensio : ");
    Serial.print(valPotensio);
    if (valPotensio < 512)
    {
      digitalWrite(pinGreen, HIGH);
      digitalWrite(pinRed, HIGH);
      delay(1000);
    }
    else
    {
      digitalWrite(pinRed, HIGH);
      delay(500);
      digitalWrite(pinGreen, HIGH);
      delay(500);
      digitalWrite(pinBlue, HIGH);
      delay(500);
      digitalWrite(pinBuzzer, HIGH);
      delay(500);
    }
  }
  else
  {
    digitalWrite(pinGreen, LOW);
    digitalWrite(pinRed, LOW);
    digitalWrite(pinBlue, LOW);
    digitalWrite(pinBuzzer, LOW);
  }
}