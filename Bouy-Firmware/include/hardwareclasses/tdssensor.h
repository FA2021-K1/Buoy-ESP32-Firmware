/*
 * Interface for the TDS Sensor (Conductivity)
 * Provides funcitons and structs to initialize the TDS Sensor
 * and retrieve data
 */
#ifndef TDSSENSOR_H
#define TDSSENSOR_H

#include <cstdint>
#include <vector>

#include "hardwareclasses/sensor.h"

class TDSSensor : public Sensor {
public:
    TDSSensor(uint8_t sensor_id);
    virtual ~TDSSensor() = default;
    virtual std::vector<Value> sampleValues() override;
};
#endif