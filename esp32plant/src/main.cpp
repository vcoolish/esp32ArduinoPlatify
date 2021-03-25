#include "main.h"
#include "advertise_services.h"
#include "ws_client.h"
#include "bme_sensor.h"
#include "./lib/bme280.h"
#include <Wire.h>

// Replace with your network credentials
const char *ssid = "PreciousLab";
const char *password = "dirtyhands";

bool ledState = 0;
const int ledPin = 2;

void main_init()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // setMDNSName("esp32-growbox");

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  ws_init();

  Wire.begin(); // join i2c bus (address optional for master)

  // i2c_scan();

  // init sensor
  // struct bme280_dev dev;
  // sensor_init();
}

void main_loop()
{
  ws_poll();

  // print_sensor_data();
  // send_sensor_data(get_json_sensor_data());

  // delay(1000);
}
