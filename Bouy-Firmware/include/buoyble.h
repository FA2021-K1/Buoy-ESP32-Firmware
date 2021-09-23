#ifndef BLUETOOTH_INTERFACE_H
#define BLUETOOTH_INTERFACE_H

#include <BLEServer.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <string>

/**
 * Interface for the Bluetooth Low Energy (BLE) module.
 * 
 * Provides functions initialize the bluetooth module and read incoming data.
 */
class BuoyBLE
{
    public:
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