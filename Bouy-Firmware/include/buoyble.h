/***
 * Interface for the Bluetooth module.
 * Provides functions and structs to initialize the bluetooth module
 * and register an interrupt routine on an incoming ping
 */
#ifndef BLUETOOTH_INTERFACE_H
#define BLUETOOTH_INTERFACE_H

#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <string>

class BuoyBLE
{
    public:
        //BuoyBLE();
        //~BuoyBLE();

        void init();
        std::string getValue();
        bool getValue_bool();
        void setValueOff();
        void setValueOn();
        void setValue(std::string value);

    private:
        std::string value = "OFF";
        BLEServer *pServer;
        BLEService *pService;
        BLECharacteristic *pCharacteristic;
};

#endif