#include <memory>

#include "buoy.h"

Buoy::Buoy(unsigned int buoyID) : _buoyID(buoyID) {}

void Buoy::attachSensor(std::shared_ptr<Sensor> sensor) {
  _sensors.push_back(sensor);
}