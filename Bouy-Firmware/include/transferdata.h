#ifndef TRANSFERDATA
#define TRANSFERDATA

typedef int JsonObject; // for the moment until we include some json lib

class TransferData
{
    protected:
        TransferData() {}
    public:
        virtual ~TransferData() {}

        virtual void writeData(JsonObject) = 0; 
};


#endif