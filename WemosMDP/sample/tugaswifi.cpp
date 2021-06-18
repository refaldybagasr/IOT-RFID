#include <Arduino.h>
#include <ESP8266WiFi.h>

// Replace with your network details
const char *ssid = "Punuk Unta";
const char *password = "UntaChina";

WiFiServer server(8888);

String header;

//Replace this with used pin
const int pinRed = 2;
const int pinGreen = 4;
const int pinBlue = 0;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Web server running. Waiting for the ESP IP...");
  delay(5000);

  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println(":8888");
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New client");

    //Wait boolean to locate when the http request ends
    boolean blank_line = true;
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    {
      currentTime = millis();
      if (client.available())
      {
        char c = client.read();
        header += c;
        if (c == '\n' && blank_line)
        {
          // checking if header is valid
          Serial.print(header);
          if (header.indexOf("VW50YUNoaW5h") >= 0)
          {
            // successful login Create HTTP and Web Page
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET / HTTP/1.1") >= 0)
            {
              Serial.println("Main Web Page");
            }
            if (header.indexOf("GET /red-on HTTP/1.1") >= 0)
            {
              Serial.println("RED Led On");
              digitalWrite(pinRed, HIGH);
            }
            if (header.indexOf("GET /red-off HTTP/1.1") >= 0)
            {
              Serial.println("Led Off");
              digitalWrite(pinRed, LOW);
            }
            if (header.indexOf("GET /green-on HTTP/1.1") >= 0)
            {
              Serial.println("GREEN Led On");
              digitalWrite(pinGreen, HIGH);
            }
            if (header.indexOf("GET /green-off HTTP/1.1") >= 0)
            {
              Serial.println("GREEN Led Off");
              digitalWrite(pinGreen, LOW);
            }
            if (header.indexOf("GET /blue-on HTTP/1.1") >= 0)
            {
              Serial.println("BLUE Led On");
              digitalWrite(pinBlue, HIGH);
            }
            if (header.indexOf("GET /blue-off HTTP/1.1") >= 0)
            {
              Serial.println("BLUE Led Off");
              digitalWrite(pinBlue, LOW);
            }
            // your web page
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println(R"(<meta name="viewport"content ="width=device-width, initial-scale=1">)");
            client.println(
                R"(<link rel="stylesheet"href ="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css">)");
            client.println("</head>");
            client.println("<div class=\"container\">");
            client.println("<h1>Web Server</h1>");
            client.println("<div class=\"row\">");
            client.println(
                R"(<div class="col-md-2"><h2>Red LED</h2></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/red-on" class="btn btn-block btn-lg btn-success" role="button">ON</a></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/red-off" class="btn btn-block btn-lg btn-danger" role="button">OFF</a></div>)");
            client.println("</div>");
            client.println("<div class=\"row\">");
            client.println(
                R"(<div class="col-md-2"><h2>Green LED</h2></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/green-on" class="btn btn-block btn-lg btn-success" role="button">ON</a></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/green-off" class="btn btn-block btn-lg btn-danger" role="button">OFF</a></div>)");
            client.println("</div>");
            client.println("<div class=\"row\">");
            client.println(
                R"(<div class="col-md-2"><h2>Blue LED</h2></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/blue-on" class="btn btn-block btn-lg btn-success" role="button">ON</a></div>)");
            client.println(
                R"(<div class="col-md-2"><a href="/blue-off" class="btn btn-block btn-lg btn-danger" role="button">OFF</a></div>)");
            client.println("</div>");
            client.println("</div>");
            client.println("</html>");
          }
          // wrong user or pass, so http request fails...
          else
          {
            client.println("HTTP/1.1 401 Unauthorized");
            client.println("WWW-Authenticate: Basic realm =\"Secure\"");
            client.println("Content-Type: text/html");
            client.println();
            client.println("<html>Authentication failed</html>");
          }
          header = "";
          break;
        }
        if (c == '\n')
        {
          // when starts reading a new line
          blank_line = true;
        }
        else if (c != '\r')
        {
          // when finds a character on the current line
          blank_line = false;
        }
      }
    }
    // closing the client connection
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");
  }
}