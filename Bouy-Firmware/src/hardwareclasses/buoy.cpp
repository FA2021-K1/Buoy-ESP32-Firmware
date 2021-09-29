#include <memory>

#include <Arduino.h>

#include "hardwareclasses/buoy.h"

Buoy::Buoy(uint16_t buoy_id) : _buoy_id(buoy_id) {
  Serial.printf("Buoy created with id %d\n", _buoy_id);
}

void Buoy::attachSensor(std::shared_ptr<Sensor> sensor) {
  _sensors.push_back(sensor);
}

std::vector<Value> Buoy::sampleAllSensors() {
  std::vector<Value> all_values;
  Serial.println("Now sampling all sensors");
  for (auto sensor : _sensors) {
    auto sensor_values = sensor->sampleValues();
    all_values.insert(all_values.end(), sensor_values.begin(), sensor_values.end());
  }
  Serial.println("Sampling finished");
  for (auto value : all_values) {
    Serial.printf("Buoy %d, Measurement %d, Value %d \n", 
          (int) value.type_id, (int) value.sensor_id, (int) value.data);
  }
  return all_values;
}