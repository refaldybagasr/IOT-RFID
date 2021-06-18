#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

#define SERIAL_DEBUG Serial
#define SERVER_TCP_PORT 50000

const char *ssid_name = "Triar",
           *ssid_password = "triar333",
           *soft_ap_name = "Belajar TCP/UDP", *soft_ap_pass = "123456";

const int pinRed = 2;
const int pinGreen = 4;
const int pinBlue = 0;
const int dhtPin = 5;

DHT DHTSensor(dhtPin, DHT11);

void serial_init()
{
  SERIAL_DEBUG.begin(115200);
  SERIAL_DEBUG.setDebugOutput(true);
}

void led_flip_flop_with_delay(uint8_t pin, unsigned long delayTime)
{
  digitalWrite(pin, !digitalRead(pin));
  delay(delayTime);
  digitalWrite(pin, !digitalRead(pin));
}

WiFiServer tcp_server_obj(SERVER_TCP_PORT);

void led_init()
{
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void wifi_hw_setup()
{
  SERIAL_DEBUG.println(F("Connecting to AP WiFi..."));
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(soft_ap_name, soft_ap_pass);
  WiFi.begin(ssid_name, ssid_password);
  while (!WiFi.isConnected())
  {
    SERIAL_DEBUG.print(F("#"));
    yield();
    delay(500);
  }

  SERIAL_DEBUG.print(F("Connected with IP = "));
  SERIAL_DEBUG.println(WiFi.localIP().toString());
  SERIAL_DEBUG.print(F("AP IP = "));
  SERIAL_DEBUG.println(WiFi.softAPIP().toString());
}

void resetPinLedState()
{
  digitalWrite(pinRed, LOW);
  digitalWrite(pinGreen, LOW);
  digitalWrite(pinBlue, LOW);
}

void setup()
{
  serial_init();
  led_init();
  resetPinLedState();

  DHTSensor.begin();

  SERIAL_DEBUG.println(F("\nDEMO TCP SERVER WEMOS ESP8266"));

  wifi_hw_setup();

  tcp_server_obj.begin(SERVER_TCP_PORT);
  tcp_server_obj.setNoDelay(true);
}

void loop()
{
  float tempRead = DHTSensor.readTemperature();

  if (isnan(tempRead))
  {
    Serial.println("Temperature data is empty");
  }

  if (tcp_server_obj.hasClient())
  {
    SERIAL_DEBUG.println("Has Connection From Client");
    WiFiClient tcp_client_obj = tcp_server_obj.available();

    if (tcp_client_obj)
    {
      SERIAL_DEBUG.println(F("Ready to recieved Data From CLient........"));

      while (tcp_client_obj.connected())
      {
        /* code */
        String payload = "";

        while (tcp_client_obj.available())
        {
          /* code */
          char rx1 = tcp_client_obj.read();
          payload += String(rx1);
        }

        if (payload.equals("baca sensor"))
        {
          if (tempRead >= 31)
          {
            Serial.println("Temperature :");
            Serial.print(tempRead);
            Serial.println("Suhu Panas");

            led_flip_flop_with_delay(pinRed, 500);
            led_flip_flop_with_delay(pinGreen, 500);
            led_flip_flop_with_delay(pinBlue, 500);
          }
          else if (tempRead >= 23 && tempRead < 31)
          {
            Serial.println("Temperature :");
            Serial.print(tempRead);
            Serial.println("Suhu Normal");

            digitalWrite(pinGreen, HIGH);
          }
          else
          {
            resetPinLedState();
          }
        }
        yield();
      }

      tcp_client_obj.stop();

      SERIAL_DEBUG.println(F("Client Disconnected !!!"));
    }
    else
    {
      SERIAL_DEBUG.println(F("Cannot Allocate Client Object !!!"));
    }
  }

  delay(500);
}
