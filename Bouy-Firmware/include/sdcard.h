/***
 * SD Card class
 */
#ifndef SD_CARD_INTERFACE_H
#define SD_CARD_INTERFACE_H

#include <cstdint>

#include "ArduinoJson.h"

#include "transferdata.h"

/**
 * Class that corresponds to the SDCard connected to the microcontroller.
 */
class SDCard : public TransferData {
public:
    SDCard() {}
    ~SDCard() {}
    
    void init();
    virtual void writeData(std::string json_string) override;
    virtual std::string readData() override;

    uint32_t get_capacity() {return _capacity;}
private:
    uint32_t _capacity;
};

#endif