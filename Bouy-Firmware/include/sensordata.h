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
#include "datetime.h"

typedef std::pair<double, double> Location;

class SensorData {
public:
  SensorData(std::shared_ptr<Buoy> buoy, Location location,
             DateTime timestamp, std::vector<Value> values);
  std::string toJsonString();
private:
  std::shared_ptr<Buoy> _buoy;
  Location _location;
  DateTime _timestamp;
  std::vector<Value> _values;
};

#endif
