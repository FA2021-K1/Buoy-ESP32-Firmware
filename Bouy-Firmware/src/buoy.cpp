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

void Buoy::attachSensor(unsigned int sensor_id) {
  _sensorIDs.push_back(sensor_id);
}

std::vector<unsigned int> Buoy::getSensorIDs() {
  return _sensorIDs;
}