/***
 * Class to hold all information of the buoy
 */
#ifndef BUOY_H
#define BUOY_H

#include <vector>
#include <memory>

#include "sensor.h"

/**
 * Interface for the buoy.
 * 
 * Each buoy has a unique ID in the fleet.
 * Buoy owns the sensors and can sample data from them.
 */
class Buoy {
public:
  Buoy(unsigned int buoy_id);
  ~Buoy() = default;

  void attachSensor(std::shared_ptr<Sensor> sensor);

  unsigned int get_buoy_id() {return _buoyID;};

  //  sampleAllSensors();

private:
  unsigned int _buoyID;
  std::vector<std::shared_ptr<Sensor>> _sensors;
};

#endif