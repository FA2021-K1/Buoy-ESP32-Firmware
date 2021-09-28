#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <utility>

#include <TinyGPS++.h>

#include "datetime.h"
#include "global_enums.h"

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

        Location_t get_location();
        GPSStatus get_status();
        int32_t get_hdop();
        DateTime get_datetime();

    private:
        int32_t _hdop;
        GPSStatus _status;
        TinyGPSPlus _tgps;
};

#endif