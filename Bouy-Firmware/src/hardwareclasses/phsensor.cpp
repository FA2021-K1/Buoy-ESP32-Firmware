#include <cstdint>
#include <vector>

#include "Arduino.h"

#include "hardwareclasses/phsensor.h"
#include "hardwarelayout.h"
#include "sensor.h"
#include "global_enums.h"

PHSensor::PHSensor(uint8_t sensor_id) : Sensor(sensor_id, SensorType::PH) {
  Serial.printf("Created PH Sensor with id %d\n", _sensor_id);
}

std::vector<Value> PHSensor::sampleValues() {
  Serial.printf("Sampling pH sensor %d ", _sensor_id);
  double voltageValue = analogRead(PH_PIN) / 4096 * 3300;
  // double pHValue = 
  std::vector<Value> values;
  values.emplace_back(_type_id, _sensor_id, voltageValue);
  Serial.printf("Sensor returned values %f\n", values[0].data);
  return values;
}