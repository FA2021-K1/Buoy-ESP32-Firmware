#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <vector>
#include <memory>
#include <cstdint>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"
#include "datetime.h"

typedef std::pair<float, float> Location;

/**
 * Dataclass for all variables that correspond to one measurement sample.
 */
class SensorData {
public:
  /**
   * Constructor for dataclass.
   * 
   * @param buoy_id    Buoy ID of owning buoy
   * @param location   Location of mearurement. Pair (lon, lat) from GPS sensor.
   * @param timestamp  Time of measurement.
   * @param values     Vector containing all values that are acquired by sensor.
   */
  SensorData(uint16_t buoy_id, Location location,
             DateTime timestamp, std::vector<Value> values);
             
  /**
   * Format SensorData object to JSON.
   * 
   * @returns JSON-formatted string.
   */
  std::string toJsonString();
private:
  uint16_t _buoy_id;
  Location _location;
  DateTime _timestamp;
  std::vector<Value> _values;
};

#endif
