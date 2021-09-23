#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>
#include <vector>

#include "value.h"
#include "global_enums.h"

/**
 * Pure abstract class for all sensors except the GPS sensor.
 */
class Sensor {
public:
  Sensor(uint32_t sensor_id, uint32_t type_id) : _sensor_id(sensor_id), _type_id(type_id) {}
  virtual ~Sensor() = default;

  // METHODS
  virtual std::vector<Value> sampleValues() = 0;
  void enable();
  void disable();

  // GETTERS
  uint32_t get_sensor_id();
  uint32_t get_type_id();
  SensorStatus get_status();

protected:
  uint32_t _sensor_id;
  uint32_t _type_id;
  SensorStatus _status;
};

#endif
