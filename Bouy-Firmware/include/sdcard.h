/***
 * SD Card class
 */
#ifndef SD_CARD_INTERFACE_H
#define SD_CARD_INTERFACE_H

#include "transferdata.h"
#include <cstdint>

class SDCard : public TransferData
{    
    public:
        SDCard(){}
        ~SDCard(){}

        //METHODS
        void init();
        void writeData(JsonObject obj) override;

        //GETTERS
        uint32_t get_capacity();
    private:
        uint32_t _capactiy;
};

#endif