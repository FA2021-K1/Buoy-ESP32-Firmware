/***
 * SD Card class
 */
#ifndef SD_CARD_INTERFACE_H
#define SD_CARD_INTERFACE_H

#include "transferdata.h"
#include <cstdint>

class SDCard : public TransferData
{
    private:
        uint32_t _capactiy;
    
    public:
        SDCard(){}
        ~SDCard(){}
        uint32_t get_capacity();
        void init();
        void writeData(void);
};

#endif