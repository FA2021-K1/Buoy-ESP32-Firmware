#ifndef RASPCOMMAND
#define RASPCOMMAND

#include <ArduinoJson.h>
#include <global_enums.h>

class RaspCommand
{
public:
    virtual std::string toJsonString();

    static RaspCommand fromString(std::string json);
};

class SyncCommand : RaspCommand
{
public:
    std::string toJsonString() override;
};

class AckCommand : RaspCommand
{
public:
    std::string toJsonString() override;
};

class ShutDownCommand : RaspCommand
{
public:
    std::string toJsonString() override;
};

class TransferDumpCommand : RaspCommand
{
public:
    TransferDumpCommand(std::string dump);
    std::string toJsonString() override;

private:
    std::string _dump;
};

#endif