/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "libraries/ArduinoJson.h"

#include "global_enums.h"
#include "driver/uart.h"

class RaspPi {
    public:
        RaspPi();
        
        void turnOn();
        void turnOff();
        void writeData(std::string json_string);
        void waitForReady();
        
};

#endif