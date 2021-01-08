#include "ws_client.h"
#include <ArduinoWebsockets.h>
#include <Arduino.h>

const char *websockets_server = "ws://192.168.0.107:8080"; //server adress and port

using namespace websockets;

uint16_t getDeviceId()
{
#if defined(ARDUINO_ARCH_ESP32)
  return ESP.getEfuseMac();
#else
  return ESP.getChipId();
#endif
}

void onMessageCallback(WebsocketsMessage message)
{
  Serial.print("Got Message: ");
  Serial.println(message.data());
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
  client.send("{ uid: " + String(getDeviceId()) + ", type: \"CONNECTION_DATA\" }");
  // Send a message
  client.send("Hi Server!");
  // Send a ping
  client.ping();
}

void ws_poll()
{
  client.poll();
}
