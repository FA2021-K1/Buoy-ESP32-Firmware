/***
 * SD Card class
 */
#ifndef SD_CARD_INTERFACE_H
#define SD_CARD_INTERFACE_H

#include <cstdint>

#include "ArduinoJson.h"

#include "transferdata.h"


class SDCard : public TransferData {
    private:
        uint32_t _capacity;

    public:
        SDCard() {}
        ~SDCard() {}

        // METHODS
        void init();
        virtual void writeData(std::string json_string) override;

        // GETTERS
        uint32_t get_capacity() {return _capacity;}
};

#endif