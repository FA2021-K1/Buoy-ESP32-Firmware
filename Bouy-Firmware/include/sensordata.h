#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <vector>
#include <memory>
#include <cstdint>

#include "ArduinoJson.h"

#include "value.h"
#include "buoy.h"
#include "datetime.h"
#include "global_enums.h"

/**
 * Dataclass for all variables that correspond to one measurement sample.
 */
class SensorData {
public:
  /**
   * Constructor for dataclass.
   * 
   * @param buoy_id          Buoy ID of owning buoy.
   * @param measurement_id   Unique id within buoy, incrementing with every measurement.
   * @param location         Location of mearurement. Pair (lon, lat) from GPS sensor.
   * @param timestamp        Time of measurement.
   * @param values           Vector containing all values that are acquired by sensor.
   */
  SensorData(uint16_t buoy_id, uint32_t measurement_id, Location_t location,
             DateTime timestamp, std::vector<Value> values);
  SensorData();
             
  /**
   * Format SensorData object to JSON.
   * 
   * @returns JSON-formatted string.
   */
  std::string toJsonString();
  std::string toPiJsonString();
  uint16_t get_buoy_id() {return _buoy_id;}
  uint32_t get_measurement_id() {return _measurement_id;}
  void append_value(Value value) {_values.push_back(value);}

  explicit operator bool() const {return _found;}

private:
  uint16_t _buoy_id;
  uint32_t _measurement_id;
  Location_t _location;
  DateTime _timestamp;
  std::vector<Value> _values;
  bool _found;
};

#endif
