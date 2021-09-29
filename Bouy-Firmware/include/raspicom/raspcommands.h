#ifndef RASPCOMMAND
#define RASPCOMMAND

#include <libraries/ArduinoJson.h>
#include <global_enums.h>

class RaspCommand
{
public:
    virtual std::string toJsonString();
    static RaspCommand* fromJsonString(std::string json);
};

class SyncCommand : public RaspCommand
{
public:
    std::string toJsonString() override;
};

class AckCommand : public RaspCommand
{
public:
    std::string toJsonString() override;
};

class ShutDownCommand : public RaspCommand
{
public:
    std::string toJsonString() override;
};

class TransferDumpCommand : public RaspCommand
{
public:
    TransferDumpCommand(std::string dump);
    std::string toJsonString() override;

private:
    std::string _dump;
};

#endif