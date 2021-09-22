/***
 * Interface for the GPS Module
 * Provides funcitons and structs to initialize the GPS Module
 * and retrieve data
 */
#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <utility>
#include <global_enums.h>
#include <TinyGps++.h>
#include "datetime.h"

typedef std::pair<double,double> location_t;

class GPSSensor
{
    public:
        GPSSensor(){}
        ~GPSSensor(){}

        location_t getLocation();
        GPSStatus get_status();
        int32_t gethdop();
        void init();
        DateTime getDateTime();
    private:
        int32_t hdop;
        GPSStatus _status;
        TinyGPSPlus tgps;
};

#endif