// Client:
// This code designed to enable server and client board to communicate with each other
// by calling their name and exchanging messages over wifi
#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

unsigned long previousMillis = 0;
int interval = 500;

String CLIENT_NAME = "SENSOR1";
WiFiClient client;

// IP Address of the server
IPAddress server(192, 168, 4, 1);

String ServerMessage;

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(50);
    Serial.print(".");
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    Serial.println("Attemting to connect");
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("wifi status connected");
      client.connect(server, 80);
      while (client.connected())
      {
        Serial.println("client connected");
        String data = client.readStringUntil('\r');
        Serial.println(data);
        if (data != "\0")
        {
          Serial.print("Received data from Server:");
          Serial.println(data);
          int Index = data.indexOf(':');
          String CLIENT = data.substring(0, Index);
          String ACTION = data.substring(Index + 1);
          if (CLIENT == CLIENT_NAME)
          {
            if (ACTION == "TEMPERATURE?")
            {
              client.println("ACK:10");
              Serial.println("This is Client: ACK10 was sent to server");
            }
          }
          else if (CLIENT == "OUTPUT1")
          {
            if (ACTION == "ON" || ACTION == "OFF")
            {
              Serial.println("This is Client: server is sending output1 On or Off command");
            }
          }

          client.stop();
          data = "\0";
        }
      }
    }
    previousMillis = millis();
  }
}