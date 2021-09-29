#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>
#include <vector>

#include "dataclasses/value.h"
#include "global_enums.h"

/**
 * Pure abstract class for all sensors except the GPS sensor.
 */
class Sensor {
public:
  Sensor(uint8_t sensor_id, uint8_t type_id) : _sensor_id(sensor_id), _type_id(type_id) {}
  virtual ~Sensor() = default;

  // METHODS
  virtual std::vector<Value> sampleValues() = 0;
  void enable();
  void disable();

  // GETTERS
  uint8_t get_sensor_id() {return _sensor_id;}
  uint8_t get_type_id() {return _type_id;}
  SensorStatus get_status() {return _status;}

protected:
  uint8_t _sensor_id;
  uint8_t _type_id;
  SensorStatus _status;
};

#endif
