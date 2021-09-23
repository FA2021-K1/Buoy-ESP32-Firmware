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

        /**
         * Write string to destination. The destination folder is hard-coded.
         * The file name is automatically generated.
         * 
         * @param json_string String to be sent in JSON format.
         */
        virtual void writeData(std::string json_string) = 0;

        /**
         * This function will read all files from the hard-coded destination folder
         * and return them as a stream of strings in json format. TODO
         */
        virtual std::string readData() = 0;
};


#endif