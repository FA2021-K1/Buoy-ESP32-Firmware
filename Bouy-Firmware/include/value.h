#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

class Value {
  uint32_t type_id;
  uint32_t sensor_id;
  double data;
};

#endif
