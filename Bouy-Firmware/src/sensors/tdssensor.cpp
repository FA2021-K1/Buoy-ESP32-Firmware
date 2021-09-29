#include <cstdint>
#include <vector>

#include "Arduino.h"

#include "sensors/tdssensor.h"
#include "hardwarelayout.h"
#include "sensor.h"
#include "global_enums.h"

TDSSensor::TDSSensor(uint8_t sensor_id) : Sensor(sensor_id, SensorType::COND) {
  Serial.printf("Created TDS Sensor with id %d\n", _sensor_id);
}

std::vector<Value> TDSSensor::sampleValues() {
  Serial.printf("Sampling sensor %d ", _sensor_id);
  double adcValue = analogRead(TDS_PIN);
  double voltageValue = (adcValue / 4096) * 2.3;
  double ppmValue = (voltageValue / 2.3) * 1000;
  std::vector<Value> values;
  values.emplace_back(_type_id, _sensor_id, ppmValue);
  Serial.printf("Sensor returned values %f\n", values[0].data);
  return values;
}