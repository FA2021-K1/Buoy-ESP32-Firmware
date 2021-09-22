#ifndef TRANSFERDATA
#define TRANSFERDATA

#include "ArduinoJson.h"

class TransferData
{
    protected:
        TransferData() {}
    public:
        virtual ~TransferData() {}

        virtual void writeData(DynamicJsonDocument obj) = 0; 
};


#endif