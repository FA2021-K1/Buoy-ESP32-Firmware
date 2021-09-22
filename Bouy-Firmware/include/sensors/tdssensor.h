/*
 * Interface for the TDS Sensor (Conductivity)
 * Provides funcitons and structs to initialize the TDS Sensor
 * and retrieve data
 */
#ifndef TDSSENSOR_H
#define TDSSENSOR_H
#include "analogsensor.h"

class TDSSensor : public AnalogSensor
{
    public:
        TDSSensor();
        ~TDSSensor();
        void set_pin(uint8_t sensor_input_pin);
        uint32_t get_ppm_value();  
    private:
        uint8_t _sensor_input_pin;
        float _ppm_value;
};
#endif