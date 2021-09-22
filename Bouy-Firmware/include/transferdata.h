#ifndef TRANSFERDATA
#define TRANSFERDATA

#include "ArduinoJson.h"

class TransferData
{
    public:
        TransferData() {} 
        virtual ~TransferData() {}
        virtual void writeData(std::string json_string) = 0; 
};


#endif