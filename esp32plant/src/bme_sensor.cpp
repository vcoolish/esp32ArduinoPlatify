#include <Arduino.h>
#include <Wire.h>
#include "bme_sensor.h"
#include "./lib/bme280.h"

struct bme280_data comp_data;
struct bme280_dev dev;

void user_delay_us(uint32_t period, void *intf_ptr)
{
  /*
     * Return control or wait,
     * for a period amount of milliseconds
     */

  if (period < 1000)
  {
    delay(1);
  }
  else
  {
    delay(period / 1000);
  }
}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

  /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

  /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

  Wire.beginTransmission(BME280_I2C_ADDR_PRIM); // transmit to device #44 (0x2c)
                                                // device address is specified in datasheet
  Wire.write(reg_addr);                         // sends instruction byte
  Wire.endTransmission();                       // stop transmitting

  Wire.requestFrom(BME280_I2C_ADDR_PRIM, len); // request 6 bytes from slave device #8
  uint8_t i = 0;
  while (Wire.available())
  {                            // slave may send less than requested
    reg_data[i] = Wire.read(); // receive a byte as character
    i++;
  }

  return rslt;
}

int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
  int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

  /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

  /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

  Wire.beginTransmission(BME280_I2C_ADDR_PRIM); // transmit to device #44 (0x2c)
                                                // device address is specified in datasheet

  Wire.write(reg_addr); // sends instruction byte

  for (uint8_t i = 0; i < len; i++)
  {
    Wire.write(reg_data[i]); // sends potentiometer value byte
  }
  Wire.endTransmission(); // stop transmitting

  return rslt;
}

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
  int8_t rslt;
  uint8_t settings_sel;
  /* Recommended mode of operation: Indoor navigation */
  dev->settings.osr_h = BME280_OVERSAMPLING_1X;
  dev->settings.osr_p = BME280_OVERSAMPLING_16X;
  dev->settings.osr_t = BME280_OVERSAMPLING_2X;
  dev->settings.filter = BME280_FILTER_COEFF_16;
  dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

  settings_sel = BME280_OSR_PRESS_SEL;
  settings_sel |= BME280_OSR_TEMP_SEL;
  settings_sel |= BME280_OSR_HUM_SEL;
  settings_sel |= BME280_STANDBY_SEL;
  settings_sel |= BME280_FILTER_SEL;
  rslt = bme280_set_sensor_settings(settings_sel, dev);
  rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

  // printf("Temperature, Pressure, Humidity\r\n");
  // while (1) {
  /* Delay while the sensor completes a measurement */
  // dev->delay_ms(70, dev->intf_ptr);
  // rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
  // print_sensor_data(&comp_data);
  // }

  return rslt;
}

int8_t sensor_init()
{
  int8_t rslt = BME280_OK;
  uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

  dev.intf_ptr = &dev_addr;
  dev.intf = BME280_I2C_INTF;
  dev.read = user_i2c_read;
  dev.write = user_i2c_write;
  dev.delay_us = user_delay_us;

  rslt = bme280_init(&dev);
  if (rslt != BME280_OK)
  {
    fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
  }

  rslt = stream_sensor_data_normal_mode(&dev);
  bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
  return rslt;
}

void print_sensor_data()
{
  bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
  bme280_data *data = &comp_data;
  char output_string[40];
#ifdef BME280_FLOAT_ENABLE
  // printf("%0.2f, %0.2f, %0.2f\r\n", comp_data->temperature, comp_data->pressure, comp_data->humidity);

  sprintf(output_string, "%0.2f, %0.2f, %0.2f\r\n", comp_data->temperature, comp_data->pressure, comp_data->humidity);
  Serial.println(output_string);
#else
  // printf("%ld, %ld, %ld\r\n", comp_data->temperature, comp_data->pressure, comp_data->humidity);

  sprintf(output_string, "%ld, %ld, %ld\r\n", data->temperature, data->pressure, data->humidity);
  Serial.println(output_string);
#endif
}

String get_json_sensor_data()
{
  bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
  bme280_data *data = &comp_data;
  char output_string[60];
  sprintf(output_string, data_format, data->temperature, data->pressure, data->humidity);
  return String(output_string);
}

void i2c_scan()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}
