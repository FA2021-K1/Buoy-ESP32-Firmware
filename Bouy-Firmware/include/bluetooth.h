/***
 * Interface for the Bluetooth module.
 * Provides functions and structs to initialize the bluetooth module
 * and register an interrupt routine on an incoming ping
 */
#ifndef BLUETOOTH_INTERFACE_H
#define BLUETOOTH_INTERFACE_H

class Bluetooth
{
    public:
        Bluetooth();
        ~Bluetooth();
};

#endif BLUETOOTH_INTERFACE_H