/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "stdbool.h"

struct RaspPi{
    bool online;
    bool requestedTurnOff;
};

void initRaspPi(struct RaspPi *pi);

#endif