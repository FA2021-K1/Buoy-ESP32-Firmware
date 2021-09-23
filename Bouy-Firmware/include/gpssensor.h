#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <utility>
#include <global_enums.h>
#include <TinyGps++.h>
#include "datetime.h"

typedef std::pair<double,double> Location;

/**
 * Interface for the GPS Module.
 * 
 * Provides functions to initialize the GPS Module and retrieve data.
 */
class GPSSensor
{
    public:
        GPSSensor(){}
        ~GPSSensor(){}

        void init();

        Location get_location();
        GPSStatus get_status();
        int32_t get_hdop();
        DateTime get_datetime();

    private:
        int32_t _hdop;
        GPSStatus _status;
        TinyGPSPlus _tgps;
};

#endif