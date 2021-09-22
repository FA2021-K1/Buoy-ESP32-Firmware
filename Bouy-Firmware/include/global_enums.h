#ifndef GLOBAL_ENUMS
#define GLOBAL_ENUMS

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

#endif