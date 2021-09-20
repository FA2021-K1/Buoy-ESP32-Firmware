#include <memory>
#include "buoy.h"

std::shared_ptr<Buoy> Buoy::_buoy = nullptr;

std::shared_ptr<Buoy> Buoy::getInstance() {
  if (Buoy::_buoy == nullptr) {
      Buoy::_buoy = std::make_shared<Buoy>();
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