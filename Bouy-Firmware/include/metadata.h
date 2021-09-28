#ifndef METADATA_H
#define METADATA

#include "global_enums.h"

class MetaData {
public:
  MetaData(buoyStates_t buoy_states) : _buoy_states(buoy_states) {}
  std::string toJsonString() const;
  uint32_t getLastMeasurementId(uint16_t buoy_id) const;

  void print() const;
  const buoyStates_t _buoy_states;
};

#endif
