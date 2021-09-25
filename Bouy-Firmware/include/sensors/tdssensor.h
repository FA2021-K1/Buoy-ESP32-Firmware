/*
 * Interface for the TDS Sensor (Conductivity)
 * Provides funcitons and structs to initialize the TDS Sensor
 * and retrieve data
 */
#ifndef TDSSENSOR_H
#define TDSSENSOR_H

#include <cstdint>
#include <vector>

#include "sensor.h"

class TDSSensor : public Sensor {
public:
    TDSSensor(uint16_t sensor_id, uint16_t type_id);
    virtual ~TDSSensor() = default;
    virtual std::vector<Value> sampleValues() override;
};
#endif