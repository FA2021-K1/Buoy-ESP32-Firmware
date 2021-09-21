/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "transferdata.h"
#include "driver/uart.h"

enum RaspPiStatus{
    ON,
    OFF,
    TURNING_ON,
    TURNING_OFF
};

class RaspPi : public TransferData{
    protected:
        RaspPi();
        ~RaspPi();

        static RaspPi* _pi;
    public:
        RaspPi(RaspPi &other) = delete;
        void operator=(const RaspPi &other) = delete;

        static RaspPi* getInstance();
        
        void turnOn();
        void turnOff();
        RaspPiStatus get_status();

        void writeData(void);
    private:
        RaspPiStatus _rasppi_status;
};

#endif