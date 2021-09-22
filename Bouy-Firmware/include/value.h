#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

class Value {
public:
  Value(uint32_t type_id_, uint32_t sensor_id_, double data_) : 
    type_id(type_id_), sensor_id(sensor_id_), data(data_) {};
  uint32_t type_id;
  uint32_t sensor_id;
  double data;
};

#endif
