#include <memory>

#include "buoy.h"

Buoy::Buoy(uint16_t buoy_id) : _buoy_id(buoy_id) {}

void Buoy::attachSensor(std::shared_ptr<Sensor> sensor) {
  _sensors.push_back(sensor);
}

std::vector<Value> Buoy::sampleAllSensors() {
  std::vector<Value> all_values;
  for (auto sensor : _sensors) {
    auto sensor_values = sensor->sampleValues();
    all_values.insert(all_values.end(), sensor_values.begin(), sensor_values.end());
  }
  return all_values;
}