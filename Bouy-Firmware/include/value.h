#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

/**
 * Value is a dataclass that holds measurement values from analog sensors.
 */
class Value {
public:
  /**
   * Constructor for all class members of Value.
   * 
   * @param type_id_    Sensor type id (see global_enums.h).
   * @param sensor_id_  Sensor id (unique on buoy).
   * @param data        Measurement value.
   */
  Value(uint32_t type_id_, uint32_t sensor_id_, double data_) : 
    type_id(type_id_), sensor_id(sensor_id_), data(data_) {};
  uint32_t type_id;
  uint32_t sensor_id;
  double data;
};

#endif
