#include <cstdint>

#include "Arduino.h"

#include "sensors/tdssensor.h"

TDSSensor::TDSSensor(uint8_t sensor_input_pin) : _sensor_input_pin(sensor_input_pin) {}

double TDSSensor::get_ppm_value() {
  double adcValue = analogRead(_sensor_input_pin);
  double voltageValue = (adcValue/4096)*2.3;
  double ppmValue = (voltageValue/2.3)*1000;
  return ppmValue;
}