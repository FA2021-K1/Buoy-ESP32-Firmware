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

class RaspPi : public TransferData {
    public:
        RaspPi();

        // METHODS
        void turnOn();
        void turnOff();
        virtual void writeData(std::string json_string, std::string filename) override;
        virtual std::string readData(std::string filename) override;

        // GETTERS
        RaspPiStatus get_status();
    private:
        RaspPiStatus _rasppi_status;
};

#endif