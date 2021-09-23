#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <vector>
#include <memory>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"
#include "datetime.h"

typedef std::pair<double, double> Location;

/**
 * Dataclass for all variables that correspond to one measrument sample.
 */
class SensorData {
public:
  /**
   * Constructor for dataclass.
   * 
   * @param buoy       Shared pointer to buoy owning the sensors.
   * @param location   Location of mearurement. Pair (lon, lat) from GPS sensor.
   * @param timestamp  Time of measurement.
   * @param values     Vector containing all values that are acquired by sensor.
   */
  SensorData(std::shared_ptr<Buoy> buoy, Location location,
             DateTime timestamp, std::vector<Value> values);
             
  /**
   * Format SensorData object to JSON.
   * 
   * @returns JSON-formatted string.
   */
  std::string toJsonString();
private:
  std::shared_ptr<Buoy> _buoy;
  Location _location;
  DateTime _timestamp;
  std::vector<Value> _values;
};

#endif
