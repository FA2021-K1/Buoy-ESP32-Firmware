#ifndef TRANSFERDATA
#define TRANSFERDATA

#include "ArduinoJson.h"

class TransferData {
    public:
        TransferData() {} 
        virtual ~TransferData() {}
        virtual void writeData(std::string json_string, std::string filename) = 0;
        virtual std::string readData(std::string filename) = 0;
};


#endif