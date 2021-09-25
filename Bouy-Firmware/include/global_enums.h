#ifndef GLOBAL_ENUMS
#define GLOBAL_ENUMS

typedef std::vector<std::tuple<uint16_t, uint32_t, uint32_t>> buoyStatus_t;
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
