#ifndef GLOBAL_ENUMS
#define GLOBAL_ENUMS

#include <cstdint>
#include <utility>
#include <map>

typedef std::map<uint16_t, std::pair<uint32_t, uint32_t>> buoyStates_t;
typedef std::pair<float, float> Location_t;

enum SensorStatus {
  UP,
  DOWN,
};

enum GPSStatus {
  VALID,
  NO_FIX,
};

enum SensorType {
  TEMP,
  PH,
  REDOX,
  COND,
};

enum RaspPiStatus {
  ON,
  OFF,
  TURNING_ON,
  TURNING_OFF,
};

enum RaspPiCommandType {
  SYNC,
  SEND_DUMP,
  ACK,
  REQUEST_SHUTDOWN,
};

#endif
