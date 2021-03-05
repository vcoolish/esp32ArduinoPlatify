#include "ws_client.h"
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>

const char *websockets_server = "ws://192.168.0.109:8080"; //server adress and port

using namespace websockets;

String mac2String(byte ar[])
{
  String s;
  for (byte i = 0; i < 6; ++i)
  {
    char buf[3];
    sprintf(buf, "%02X", ar[i]); // J-M-L: slight modification, added the 0 in the format for padding
    s += buf;
    if (i < 5)
      s += ':';
  }
  return s;
}

String getDeviceId()
{
  return mac2String((byte *)ESP.getEfuseMac());
}

void handleMessageData(String json)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);

  const String type = doc["type"];
  const String payload = doc["payload"];
  Serial.println("Parsed type " + type + "; payload: " + payload + ".");

  if (type == "COMMAND")
  {
    if (payload == "LED_ON")
    {
      digitalWrite(2, true);
    }
    else if (payload == "LED_OFF")
    {
      digitalWrite(2, false);
    }
  }
}

void onMessageCallback(WebsocketsMessage message)
{
  Serial.print("Got Message: ");
  Serial.println(message.data());

  if (message.isText())
  {
    handleMessageData(message.data());
  }
}

void onEventsCallback(WebsocketsEvent event, String data)
{
  if (event == WebsocketsEvent::ConnectionOpened)
  {
    Serial.println("Connnection Opened");
  }
  else if (event == WebsocketsEvent::ConnectionClosed)
  {
    Serial.println("Connnection Closed");
  }
  else if (event == WebsocketsEvent::GotPing)
  {
    Serial.println("Got a Ping!");
  }
  else if (event == WebsocketsEvent::GotPong)
  {
    Serial.println("Got a Pong!");
  }
}

WebsocketsClient client;
void ws_init()
{
  // Setup Callbacks
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);

  // Connect to server
  client.connect(websockets_server);

  Serial.println(String(getDeviceId()));
  client.send("{ \"uid\": \"" + String(getDeviceId()) + "\", \"type\": \"CONNECTION_DATA\" }");
  // Send a message
  client.send("Hi Server!");
  // Send a ping
  client.ping();
}

void ws_poll()
{
  client.poll();
}

void send_sensor_data(String data)
{
  client.send("{ \"uid\": \"" + String(getDeviceId()) + "\", \"type\": \"SENSORS_DATA\", \"payload\": " + data + " }");
}
