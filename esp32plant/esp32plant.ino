//#include <HTTPClientESP32Ex.h>
//#include "FirebaseESP32.h"
//#include <Wire.h>
//#include <SPI.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
//#include "RTClib.h"
//
//#define BME_CS 5
//#define BME_MOSI 23
//#define BME_MISO 19
//#define BME_SCK 18
//
//#define TEMPERATURE_PIN 4
//#define MOISTURE_PIN 36
//#define PUMP_PIN 26
//#define LED_PIN 32
//#define COOLER2_PIN 33
//#define COOLER_PIN 25
//
//#define SEALEVELPRESSURE_HPA (1013.25)
//
//#define FIREBASE_HOST "esp32plantifytest.firebaseio.com" //Do not include https:// in FIREBASE_HOST
//#define FIREBASE_AUTH "HbdM9xdt9v0va4xuB7RNrbMguDw8tqXpHlK4p8Hf"
//#define WIFI_SSID "TL-2.4G"
//#define WIFI_PASSWORD "yodamaster"
//
//RTC_DS3231 rtc;
// 
//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// 
////Adafruit_BME280 bme; // I2C
////Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI
//FirebaseData firebaseData;
//unsigned long delayTime;
//String path = "/ESP32_Test";
//uint16_t Get_moisture_percentage(void);
//
//OneWire oneWire(TEMPERATURE_PIN);
//DallasTemperature sensors(&oneWire);
//DeviceAddress Thermometer;
//
//uint8_t sensor1[8] = { 0x28, 0xAA, 0x8C, 0xDF, 0x4E, 0x14, 0x01, 0xB0 };
//
//void printAddress(DeviceAddress deviceAddress)
//{ 
//  for (uint8_t i = 0; i < 8; i++)
//  {
//    Serial.print("0x");
//    if (deviceAddress[i] < 0x10) Serial.print("0");
//    Serial.print(deviceAddress[i], HEX);
//    if (i < 7) Serial.print(", ");
//  }
//  Serial.println("");
//}
//
//void setup() {
//    Serial.begin(115200);
//    Serial.println(F("BME280 test"));
//    sensors.begin();
//    Serial.println("Locating devices...");
//    Serial.print("Found ");
//    int deviceCount = sensors.getDeviceCount();
//    Serial.print(deviceCount, DEC);
//    Serial.println(" devices.");
//    Serial.println("");
//    Serial.println("Printing addresses...");
//    for (int i = 0;  i < deviceCount;  i++)
//    {
//      Serial.print("Sensor ");
//      Serial.print(i+1);
//      Serial.print(" : ");
//      sensors.getAddress(Thermometer, i);
//      printAddress(Thermometer);
//    }
////    Wire.begin(BME_SDA, BME_SCK);
//    Serial.print("Connecting to WiFi");
//    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//    while (WiFi.status() != WL_CONNECTED) {
//      Serial.print(".");
//      delay(300);
//    }
//    pinMode(COOLER2_PIN, OUTPUT);
//    pinMode(COOLER_PIN, OUTPUT);
//    pinMode(PUMP_PIN, OUTPUT);
//    pinMode(LED_PIN, OUTPUT);
//    Serial.println();
//    Serial.print("Connected with IP: ");
//    Serial.println(WiFi.localIP());
//    Serial.println();
//    if (! bme.begin(&Wire)) {
//        Serial.println("Could not find a valid BME280 sensor, check wiring!");
//        while(1);
//    }
//    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
//    Firebase.reconnectWiFi(true);
//    Serial.println("-- Default Test --");
//    Serial.println("normal mode, 16x oversampling for all, filter off,");
//    Serial.println("0.5ms standby period");
//    if (! rtc.begin()) {
//      Serial.println("Couldn't find RTC");
//      while (1);
//    }
// 
//   if (rtc.lostPower()) {
//     Serial.println("RTC lost power, lets set the time!");
//      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//    }
//    delayTime = 20000;
//    
//    Serial.println();
//}
//
//
//void loop() {
//    // Only needed in forced mode! In normal mode, you can remove the next line.
//    bme.takeForcedMeasurement(); // has no effect in normal mode
//    
//    printValues();
//    delay(delayTime);
//}
//
//
//void printValues() {
//    Serial.print("Temperature = ");
//    Serial.print(bme.readTemperature());
//    Serial.println(" *C");
//
//    Serial.print("Pressure = ");
//
//    Serial.print(bme.readPressure() / 100.0F);
//    Serial.println(" hPa");
//
//    Serial.print("Approx. Altitude = ");
//    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
//    Serial.println(" m");
//
//    Serial.print("Humidity = ");
//    Serial.print(bme.readHumidity());
//    Serial.println(" %");
//
//    uint16_t moi = Get_moisture_percentage();
//    
//    Serial.print("analog read = ");
//    Serial.print(moi);
//    Serial.println(" ");
//    
//    sensors.requestTemperatures();           
//    delay(400);
//    Serial.println();
//    Serial.print("gTemperature = ");
//    Serial.print(String(sensors.getTempC(sensor1)));
//    Serial.println(" ºC");
//    Serial.println();
//
//    DateTime now = rtc.now();
//
//    String timestamp = 
//        String(now.year()) + "-" +
//        String(now.month()) +  "-" +
//        String(now.day()) + "T" +
//        String(now.hour()) + ":" +
//        String(now.minute()) + ":" +
//        String(now.second());
//        
//    String jsonStr = "{\"temperature\":\"" + String(bme.readTemperature()) + " ºC\", " + 
//                       "\"pressure\":\"" + String(bme.readPressure() / 100.0F) + " hPa\", " + 
//                       "\"altitude\":\"" + String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + " m\", " +
//                       "\"humidity\":\"" + String(bme.readHumidity()) + " %\", " +
//                       "\"moisture\":\"" + String(Get_moisture_percentage()) + " %\", " +
//                       "\"gTemperature\":\"" + String(sensors.getTempC(sensor1)) + " ºC\", " +
//                       "\"clockTemperature\":\"" + String(rtc.getTemperature()) + " ºC\", " +
//                       "\"timestamp\":\"" + timestamp + "\""
//                       "}";
//
//    if (Firebase.pushJSON(firebaseData, path + "/data", jsonStr))
//    {
//      Serial.println("PASSED");
//      Serial.println("PATH: " + firebaseData.dataPath());
//      Serial.print("PUSH NAME: ");
//      Serial.println(firebaseData.pushName());
//      Serial.println("ETag: " + firebaseData.ETag());
//      Serial.println("------------------------------------");
//      Serial.println();
//    }
//    else
//    {
//      Serial.println("FAILED");
//      Serial.println("REASON: " + firebaseData.errorReason());
//      Serial.println("------------------------------------");
//      Serial.println();
//    }
//    Serial.println(timestamp);
//    Serial.println();
//    Serial.print("clockTemperature: ");
//    Serial.print(rtc.getTemperature());
//    Serial.println(" C");
//
//    Toggle_pump_light(0);
//    Serial.print("Pump is On");
//    Serial.println();
//    delay(10000);
//    Toggle_pump_light(1);
//    Serial.print("Pump is Off");
//    Serial.println();
//}
//
//void Toggle_pump_light(int value) {
//    digitalWrite(COOLER_PIN, value);
//    Serial.print("Cooler");
//    delay(2000);
//    digitalWrite(COOLER2_PIN, value);
//    Serial.print("cooler2");
//    delay(2000);
//    digitalWrite(PUMP_PIN, value);
//    Serial.print("Pump");
//    delay(2000);
//}
//
//uint16_t Get_moisture_percentage(void) {
//    uint16_t moi = 0;
//    moi = analogRead(MOISTURE_PIN);
//
//    moi = (3500 - 1520) - (moi - 1520);
//    moi = (moi * 100) / (3500 - 1520);
//    // 1520 in water
//    // 3450 in air
//    
//    return moi;
//}

// ===================================================================================================

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-websocket-server-arduino/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your network credentials
const char* ssid = "PreciousLab";
const char* password = "dirtyhands";

bool ledState = 0;
const int ledPin = 2;

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #143642;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>ESP Web Server</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>ESP WebSocket Server</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Output - GPIO 2</h2>
      <p class="state">state: <span id="state">%STATE%</span></p>
      <p><button id="button" class="button">Toggle</button></p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    var state;
    if (event.data == "1"){
      state = "ON";
    }
    else{
      state = "OFF";
    }
    document.getElementById('state').innerHTML = state;
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
  }
  function toggle(){
    websocket.send('toggle');
  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(String(ledState));
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      ledState = !ledState;
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if (ledState){
      return "ON";
    }
    else{
      return "OFF";
    }
  }
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  setMDNSName("esp32-growbox");

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  initWebSocket();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Start server
  server.begin();
}

void loop() {
  ws.cleanupClients();
  digitalWrite(ledPin, ledState);
}
