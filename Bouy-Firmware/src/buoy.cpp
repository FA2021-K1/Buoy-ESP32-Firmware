#include <memory>
#include "buoy.h"

Buoy* Buoy::_buoy = nullptr;

Buoy* Buoy::getInstance() {
  if (Buoy::_buoy == nullptr) {
      Buoy::_buoy = new Buoy(1234);
  }
  return Buoy::_buoy;
}

Buoy::Buoy(unsigned int buoyID) : _buoyID(buoyID) {}

void Buoy::attachSensor(Sensor *sensor) {
  _sensors.push_back(sensor);
}