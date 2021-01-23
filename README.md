# esp32ArduinoPlatify
Esp32 Arduino project for plant growing automation
![alt text](https://i.ibb.co/CMjTFWB/scheme.jpg)

## Libs
To install ESP32 Arduino to Arduino IDE follow some instructions:
1. [RU](https://voltiq.ru/instruction-installing-esp32-board-in-arduino-ide-for-windows/)
2. [EN](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

[Websocket server libs](https://randomnerdtutorials.com/esp32-websocket-server-arduino/)

### Arduino libs
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) 6.17.2
* [ArduinoWebsockets](https://github.com/gilmaimon/ArduinoWebsockets) 0.5.0

### Other libs
* [BME280](https://github.com/BoschSensortec/BME280_driver) *(used as source code)*

## Troubleshooting
When you have problems with communication between board and Arduino IDE use esptool to erase flash.
```python
python esptool --port <your COM No.> erase_flash
```
