/***
 * Proivdes data structures to hold the measurements of all sensors
 * at one timepoint and create the requested ouput formats (e.g. json)
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <memory>
#include <vector>
#include <utility>

#include "ArduinoJson.h"

#include "value.h"

typedef std::pair<double, double> Location;

class SensorData {
public:
  SensorData();
  DynamicJsonDocument toJson();
private:
  Location location;
  std::string timestamp;
  std::vector<Value> values;
};

#endif
