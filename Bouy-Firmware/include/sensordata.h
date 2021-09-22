/***
 * Proivdes data structures to hold the measurements of all sensors
 * at one timepoint and create the requested ouput formats (e.g. json)
 */
#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <vector>
#include <memory>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"

typedef std::pair<double, double> Location;

class SensorData {
public:
  SensorData(std::shared_ptr<Buoy> buoy, Location location,
             std::string timestamp, std::vector<Value> values);
  std::string toJsonString();
private:
  std::shared_ptr<Buoy> _buoy;
  Location _location;
  std::string _timestamp;
  std::vector<Value> _values;
};

#endif
