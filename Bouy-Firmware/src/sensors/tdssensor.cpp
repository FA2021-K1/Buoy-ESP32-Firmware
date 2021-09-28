#include <cstdint>
#include <vector>

#include "Arduino.h"

#include "sensors/tdssensor.h"
#include "hardwarelayout.h"
#include "sensor.h"

TDSSensor::TDSSensor(uint8_t sensor_id, uint8_t type_id) : Sensor(sensor_id, type_id) {}

std::vector<Value> TDSSensor::sampleValues() {
  double adcValue = analogRead(TDS_PIN);
  double voltageValue = (adcValue / 4096) * 2.3;
  double ppmValue = (voltageValue / 2.3) * 1000;
  std::vector<Value> values;
  values.emplace_back(_sensor_id, _type_id, ppmValue);
  return values;
}