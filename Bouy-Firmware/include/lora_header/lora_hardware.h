#ifndef LORA_HARDWARE
#define LORA_HARDWARE

#include <memory>
#include <queue>
#include <lora_header/buoy_header.h>

class PackageCallable
{
public:
    PackageCallable();
    virtual ~PackageCallable();
    virtual void onPackageSend(std::shared_ptr<struct payload> payload) = 0;
    virtual void onPackageReceived(std::shared_ptr<struct payload> payload) = 0;
};

class LoraHardwareLayer
{
public:
    LoraHardwareLayer(uint16_t buoy_id);
    void sendTo(std::unique_ptr<struct payload> payload, uint16_t receiver_id, std::unique_ptr<PackageCallable> callback);
    static size_t get_maximum_payload_size();

private:
    const uint16_t _buoy_id;
    std::queue<std::pair<std::unique_ptr<struct lora_package>, std::unique_ptr<PackageCallable>>> _send_queue;
};

#endif