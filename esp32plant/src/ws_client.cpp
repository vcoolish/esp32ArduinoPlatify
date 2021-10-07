#include "ws_client.h"
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>

#define RELAY_ONE_PIN 13
#define RELAY_TWO_PIN 32
#define RELAY_THREE_PIN 33

const char *websockets_server = "ws://192.168.0.104:8080"; //server adress and port
extern volatile uint32_t sharedCounter;

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

void relay_on(int pin)
{
  Serial.println("ON " + String(pin));
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void relay_off(int pin)
{
  Serial.println("OFF " + String(pin));
  pinMode(pin, INPUT);
}

void handleCommand(String command)
{
  if (command == "LED_ON")
  {
    digitalWrite(2, true);
  }
  else if (command == "LED_OFF")
  {
    digitalWrite(2, false);
  }
  else if (command == "TIME")
  {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    send_data(String(tv.tv_sec));
  }
  else if (command == "WATER_ON")
  {
    relay_on(RELAY_ONE_PIN);
  }
  else if (command == "WATER_OFF")
  {
    relay_off(RELAY_ONE_PIN);
  }
}

void handleTask(String task)
{
}

void handlePinTimeout(uint32_t timeout)
{
  sharedCounter = timeout;
}

void handleMessageData(String json)
{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, json);

  String type = doc["type"];
  Serial.println("Parsed type " + type + ".");

  if (type == "COMMAND")
  {
    String payload = doc["payload"];
    handleCommand(payload);
  }
  else if (type == "TASK")
  {
    String payload = doc["payload"];
    handleTask(payload);
  }
  else if (type == "PIN_TIMEOUT")
  {
    uint32_t payload = doc["payload"];
    Serial.print(payload);
    Serial.println(" timeout");
    handlePinTimeout(payload);
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

WebsocketsClient client;
void tryConnect()
{
  bool connected;
  do
  {
    connected = client.connect(websockets_server);
    if (!connected)
    {
      Serial.println("Trying to connect...");
      delay(1000);
    }
  } while (!connected);
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
    tryConnect();
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

void ws_init()
{
  // Setup Callbacks
  client.onMessage(onMessageCallback);
  client.onEvent(onEventsCallback);

  // Connect to server
  tryConnect();

  Serial.println(String(getDeviceId()));
  // Send a message
  client.send("{ \"uid\": \"" + String(getDeviceId()) + "\", \"type\": \"CONNECTION_DATA\" }");

  // Send a ping
  client.ping();
}

void ws_poll()
{
  client.poll();
}

void send_data(String data)
{
  client.send("{ \"uid\": \"" + String(getDeviceId()) + "\", \"type\": \"DATA\", \"payload\": " + data + " }");
}

void send_sensor_data(String data)
{
  client.send("{ \"uid\": \"" + String(getDeviceId()) + "\", \"type\": \"SENSORS_DATA\", \"payload\": " + data + " }");
}
