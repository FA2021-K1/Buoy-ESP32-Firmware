/***
 * Class to hold all information of the buoy
 */
#ifndef BUOY_H
#define BUOY_H

#include <vector>
#include <memory>
#include <cstdint>

#include "sensor.h"

/**
 * Interface for the buoy.
 * 
 * Each buoy has a unique ID in the fleet.
 * Buoy owns the sensors and can sample data from them.
 */
class Buoy {
public:
  Buoy(uint16_t buoy_id);
  ~Buoy() = default;

  void attachSensor(std::shared_ptr<Sensor> sensor);

  uint16_t get_buoy_id() {return _buoy_id;};

  std::vector<Value> sampleAllSensors();

private:
  uint16_t _buoy_id;
  std::vector<std::shared_ptr<Sensor>> _sensors;
};

#endif