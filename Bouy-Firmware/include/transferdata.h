#ifndef TRANSFERDATA
#define TRANSFERDATA

#include "ArduinoJson.h"

/**
 * Pure abstract class for all components that can send an receive data.
 */
class TransferData {
    public:
        TransferData() {} 
        virtual ~TransferData() {}
        virtual void writeData(std::string json_string) = 0;
        virtual std::string readData() = 0;
};


#endif