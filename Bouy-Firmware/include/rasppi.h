/***
 * Interface for the raspberrypi
 * Provides functions and structs to wakeup the Raspberry Pi
 * and communicate sensor data
 */
#ifndef RASPBERRYPI_INTERFACE_H
#define RASPBERRYPI_INTERFACE_H

#include "ArduinoJson.h"

#include "transferdata.h"
#include "global_enums.h"
#include "driver/uart.h"

class RaspPi : public TransferData{
    protected:
        RaspPi();
        ~RaspPi();

        static RaspPi* _pi;
    public:
        RaspPi(RaspPi &other) = delete;
        void operator=(const RaspPi &other) = delete;

        //METHODS
        void turnOn();
        void turnOff();
        virtual void writeData(DynamicJsonDocument obj) override;

        //GETTER
        static RaspPi* getInstance();
        RaspPiStatus get_status();
    private:
        RaspPiStatus _rasppi_status;
};

#endif