#include <cstdint>
#include <vector>

#include "Arduino.h"

#include "sensors/phsensor.h"
#include "hardwarelayout.h"
#include "sensor.h"
#include "global_enums.h"

PHSensor::PHSensor(uint8_t sensor_id) : Sensor(sensor_id, SensorType::COND) {
  Serial.printf("Created PH Sensor with id %d\n", _sensor_id);
  // TODO
  ph.begin();
}

std::vector<Value> PHSensor::sampleValues() {
  Serial.printf("Sampling sensor %d ", _sensor_id);
  double temperatureValue = 25;
  double voltageValue = analogRead(PH_PIN) / 4096 * 3300;
  double pHValue = ph.readPH(voltageValue, temperatureValue);
  std::vector<Value> values;
  values.emplace_back(_type_id, _sensor_id, pHValue);
  Serial.printf("Sensor returned values %f\n", values[0].data);
  return values;
}