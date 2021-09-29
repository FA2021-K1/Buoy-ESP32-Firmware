/*
 * Interface for the TDS Sensor (Conductivity)
 * Provides funcitons and structs to initialize the TDS Sensor
 * and retrieve data
 */
#ifndef PHSENSOR_H
#define PHSENSOR_H

#include <cstdint>
#include <vector>

#include "hardwareclasses/sensor.h"

class PHSensor : public Sensor {
public:
    PHSensor(uint8_t sensor_id);
    virtual ~PHSensor() = default;
    virtual std::vector<Value> sampleValues() override;
};

#endif