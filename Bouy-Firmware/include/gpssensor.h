#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <utility>
#include <global_enums.h>
#include <TinyGps++.h>
#include "datetime.h"

typedef std::pair<float, float> Location;

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

        /**
         * Change the baud-rate from default 9600 to 115200 to enable faster communication.
         */
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