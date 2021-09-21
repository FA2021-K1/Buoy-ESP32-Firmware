/***
 * Interface for the GPS Module
 * Provides funcitons and structs to initialize the GPS Module
 * and retrieve data
 */
#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <utility>
#include <global_enums.h>


typedef std::pair<double,double> location_t;

class GPSSensor
{
    public:
        GPSSensor(){}
        ~GPSSensor(){}

        location_t getLocation();
        SensorStatus get_status();
    private:
        SensorStatus _status;
};

#endif