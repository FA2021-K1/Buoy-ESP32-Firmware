/*
 * Interface for the TDS Sensor (Conductivity)
 * Provides funcitons and structs to initialize the TDS Sensor
 * and retrieve data
 */
#ifndef TDSSENSOR_H
#define TDSSENSOR_H

#include <cstdint>

class TDSSensor {
public:
    TDSSensor(uint8_t sensor_input_pin);
    double get_ppm_value();  
private:
    uint8_t _sensor_input_pin;
};
#endif