#ifndef LORA_HARDWARE
#define LORA_HARDWARE

#include <memory>
#include <queue>
#include <lora_header/buoy_header.h>
#include <lora_header/lora_protocol.h>

using namespace std;

class LoraHardwareLayer : LoraLayer
{
public:
    LoraHardwareLayer(buoy_id_t buoy_id);
    void send(std::unique_ptr<struct payload> payload, std::unique_ptr<std::stack<callback_t>> callbacks) override;
    void receive(std::unique_ptr<struct payload> payload) override;
    static size_t get_maximum_payload_size();

private:
    const buoy_id_t _buoy_id;
    queue<pair<unique_ptr<struct lora_package>,unique_ptr<stack<callback_t>>>> _send_queue;
};

#endif