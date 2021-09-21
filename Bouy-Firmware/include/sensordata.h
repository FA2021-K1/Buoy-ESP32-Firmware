/***
 * Proivdes data structures to hold the measurements of all sensors
 * at one timepoint and create the requested ouput formats (e.g. json)
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <memory>
#include <vector>
#include <utility>

#include "value.h"

typedef int JsonObject; // for the moment until we include some json lib
typedef std::pair<double, double> Location;

class SensorData {
public:
  SensorData();
  JsonObject toJson();
private:
  Location location;
  std::string timestamp;
  std::vector<Value> values;
};

#endif
