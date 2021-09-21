#ifndef SENSOR_H
#define SENSOR_H

#include <cstdint>
#include <vector>

#include "value.h"
#include "global_enums.h"

class Sensor {
public:
  Sensor(uint32_t sensor_id, uint32_t type_id);
  virtual ~Sensor();

  // METHODS
  virtual std::vector<Value> sampleValues() = 0;

  // GETTERS
  uint32_t get_sensor_id();
  uint32_t get_type_id();
  SensorStatus get_status();

private:
  uint32_t _sensor_id;
  uint32_t _type_id;
  SensorStatus _status;
};

#endif
