#include <cstdint>
#include <vector>

#include "Arduino.h"

#include "hardwareclasses/phsensor.h"
#include "hardwareclasses/sensor.h"
#include "global_enums.h"
#include "hardwarelayout.h"

PHSensor::PHSensor(uint8_t sensor_id) : Sensor(sensor_id, SensorType::COND) {
  Serial.printf("Created pH Sensor with id %d\n", _sensor_id);
}

std::vector<Value> PHSensor::sampleValues() {
  Serial.printf("Sampling pH sensor %d ", _sensor_id);
  double value = analogRead(PH_PIN);
  // double voltageValue = (adcValue / 4096) * 2.3;
  // double ppmValue = (voltageValue / 2.3) * 1000;
  std::vector<Value> values;
  values.emplace_back(_type_id, _sensor_id, value);
  Serial.printf("Sensor returned values %f\n", values[0].data);
  return values;
}