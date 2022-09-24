// Server:
// This code designed to enable server and client board to communicate with each other
// by calling their name and exchanging messages over wifi

#include <Arduino.h>
#include "WiFi.h"

#define NUM_CLIENTS 2
String data;
String CLIENT;
String ACTION;

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);
// This matrix is defined for further development, it has not been used in the code
WiFiClient *clients[NUM_CLIENTS] = {NULL};

void clientCommand(String input)
{
  for (int i = 0; i < NUM_CLIENTS; i++)
  {
    WiFiClient client = server.available();
    if (client)
    {
      if (client.connected())
      {
        client.println(input);
        delay(10);
      }
    }
    client.stop();
  }
}

String clientRequest(String input)
{
  String response = "\0";
  for (int i = 0; i < NUM_CLIENTS; i++)
  {
    WiFiClient client = server.available();
    if (client)
    {
      client.setTimeout(50);
      if (client.connected())
      {
        client.println(input);

        data = client.readStringUntil('\r'); // received the server's answer
        if (data != "\0")
        {
          int Index = data.indexOf(':');

          CLIENT = data.substring(0, Index);
          ACTION = data.substring(Index + 1);

          if (CLIENT == "ACK")
          {
            response = ACTION;
          }
          data = "\0";
        }
      }
    }
  }
  return response;
}

// This void is for further developmets and has not ben used
void connect_wifi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    //delay(100);
  }
}

void setup()
{
  Serial.begin(9600);

  //Start Server
  Serial.println();
  Serial.print("Setting soft AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  WiFi.begin();
  server.begin();
  //End: Server
}

void loop()
{
  if ((clientRequest("SENSOR1:TEMPERATURE?").toInt()) > 30) //Request the temperature from SENSOR1
  {
    clientCommand("OUTPUT1:ON"); //Sets the output on OUTPUT1
    Serial.println("This is Server: Output1:On was sent to client");
  }
  else
  {
    clientCommand("OUTPUT1:OFF"); //Sets the output on OUTPUT1
    Serial.println("This is Server: Output1:Off was sent to client");
  }
}