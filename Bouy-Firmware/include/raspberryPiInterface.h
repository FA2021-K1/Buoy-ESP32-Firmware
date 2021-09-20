/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "driver/uart.h"

enum RASPPI_STATE{
    ON,
    OFF,
    STARTING_UP,
    SHUTTING_DOWN
};

class RaspPi{
    protected:
        RaspPi();
        ~RaspPi();

        static RaspPi* pi_;
    public:
        RaspPi(RaspPi &other) = delete;
        void operator=(const RaspPi &other) = delete;

        static RaspPi* getInstance();
        
        void turnOn();
        void turnOff();
    private:
        RASPPI_STATE rasppi_state;
};

#endif