#ifndef TRANSFERDATA
#define TRANSFERDATA

#include "ArduinoJson.h"

class TransferData
{
    protected:
        TransferData() {}
    public:
        virtual ~TransferData() {}

        virtual void writeData(char* json_string) = 0; 
};


#endif