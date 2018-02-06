/**
 * Server to manage GPIO pins as output.
 * examples:
 *  - http://<IP>/gpio?2=0 -> set pin 2 to LOW
 *  - http://<IP>/gpio?5=1 -> set pin 5 to HIGH
 * @author: Aaron Rosas
 */

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>

//WIFI Credentials
const char *ssid = "***";
const char *password = "***";

MDNSResponder mdns;

ESP8266WebServer server(80);

// GPIO ////////////////////////////////////////////////////////////////////////////////////

/**
 * Declare here the pins you want to use, warning: all of them are not valid,
 * there are some protected according to the board
 * 
 * Naming matchs with GPIO schema, it could be different from board indexes.
 * */
int gpio[] = {2, 4, 5, 12, 13, 14, 15};
int gpioLength = 0;

void setupGpio()
{
  gpioLength = sizeof(gpio) / sizeof(gpio[0]);
  for (int i = 0; i < gpioLength; i++)
  {
    pinMode(gpio[i], OUTPUT);
    digitalWrite(gpio[i], LOW);
  }
}

// Server Handlers /////////////////////////////////////////////////////////////////////////

void handleIndex()
{
  server.send(200, "text/html",
              "<html>"
              "<head><title>POWER STRIP</title></head>"
              "<body>"
              "<h1>POWER STRIP</h1>"
              "<p>GPIO 2 <a href=\"gpio?2=0\">0</a> || <a href=\"gpio?2=1\">1</a></p>"
              "<p>GPIO 4 <a href=\"gpio?4=0\">0</a> || <a href=\"gpio?4=1\">1</a></p>"
              "<p>GPIO 5 <a href=\"gpio?5=0\">0</a> || <a href=\"gpio?5=1\">1</a></p>"
              "<p>GPIO 12 <a href=\"gpio?12=0\">0</a> || <a href=\"gpio?12=1\">1</a></p>"
              "<p>GPIO 13 <a href=\"gpio?13=0\">0</a> || <a href=\"gpio?13=1\">1</a></p>"
              "<p>GPIO 14 <a href=\"gpio?14=0\">0</a> || <a href=\"gpio?14=1\">1</a></p>"
              "<p>GPIO 15 <a href=\"gpio?15=0\">0</a> || <a href=\"gpio?15=1\">1</a></p>"
              "</body>"
              "</html>");
}

void handleGpio()
{
  for (uint8_t i = 0; i < server.args(); i++)
  {
    for (int j = 0; j < gpioLength; j++)
    {
      int pin = gpio[j];
      if (server.argName(i).toInt() == pin)
      {
        int value = strtoul(server.arg(i).c_str(), NULL, 10);
        digitalWrite(pin, value == 0 ? LOW : HIGH);
      }
    }
  }
  handleIndex();
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}

// SETUP & LOOP ////////////////////////////////////////////////////////////////////////////

void setup(void)
{

  setupGpio();

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP()))
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleIndex);
  server.on("/gpio", handleGpio);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}
