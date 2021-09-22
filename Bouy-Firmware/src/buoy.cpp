#include "buoy.h"

Buoy::Buoy(unsigned int buoyID) : _buoyID(buoyID) {}

void Buoy::attachSensor(Sensor *sensor) {
  _sensors.push_back(sensor);
}