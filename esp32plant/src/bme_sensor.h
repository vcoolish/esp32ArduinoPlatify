#include <Arduino.h>
#include "./lib/bme280.h"

const char data_format[] = "{\"temp\": %ld, \"pres\":%ld, \"hum\": %ld}";

int8_t sensor_init();
void print_sensor_data();
String get_json_sensor_data();
void i2c_scan();
