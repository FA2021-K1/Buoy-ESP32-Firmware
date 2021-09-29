#include <memory>

#include <Arduino.h>

#include "buoy.h"

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
  return all_values;
}