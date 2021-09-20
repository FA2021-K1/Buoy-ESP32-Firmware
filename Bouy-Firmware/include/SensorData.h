/***
 * Proivdes data structures to hold the measurements of all sensors
 * at one timepoint and create the requested ouput formats (e.g. json)
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <memory>
#include <vector>
#include <utility>
#include "buoy.h"

typedef std::pair<unsigned int, unsigned int> Location;

class SensorData {
public:
  SensorData();
private:
  std::shared_ptr<Buoy> _buoy;
  Location _location;
  std::string _timestamp;
  std::vector<unsigned int> _values;
};

#endif