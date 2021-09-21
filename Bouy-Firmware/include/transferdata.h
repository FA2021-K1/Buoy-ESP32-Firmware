#ifndef TRANSFERDATA
#define TRANSFERDATA

class TransferData
{
    protected:
        TransferData() {}
    public:
        virtual ~TransferData() {}

        virtual void writeData(void) = 0; 
};


#endif