/***
 * Class to hold all information of the buoy
 */
#ifndef BUOY_H
#define BUOY_H

#include <vector>

#include "sensor.h"

class Buoy {
public:
  Buoy(unsigned int buoy_id);
  ~Buoy() = default;

  void attachSensor(Sensor *sensor);

  unsigned int get_buoy_id() {return _buoyID;};

  //  sampleAllSensors();

private:
  unsigned int _buoyID;
  std::vector<Sensor *> _sensors;
};

#endif