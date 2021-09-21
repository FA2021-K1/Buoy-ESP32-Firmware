#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "sensor.h"

class AnalogSensor : public Sensor {
public:
  virtual std::vector<Value> sampleValues() override;
};

#endif
