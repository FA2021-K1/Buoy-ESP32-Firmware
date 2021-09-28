#ifndef LORA_PROTOCOL
#define LORA_PROTOCOL

#include <list>
#include <time>
#include <memory>
#include <functional>
#include <lora_header/buoy_header.h>
#include <unordered_map>
#include <stack>
#include <queue>

typedef std::function<void(uint8_t)> callback_t;

class LoraLayer
{
public:
    LoraLayer(std::shared_ptr<LoraLayer> lower_layer) : _lower_layer(lower_layer) {}
    virtual ~LoraLayer();
    virtual void send(std::unique_ptr<struct payload> payload, std::unique_ptr<std::stack<callback_t>> callbacks) = 0;
    virtual void receive(std::unique_ptr<struct payload> payload) = 0;
    virtual void onTimeout(uint8_t identifier);

protected:
    std::shared_ptr<LoraLayer> _lower_layer;
};

struct packet_timeout_callback
{
    int64_t time;
    uint8_t identifier;
    std::shared_ptr<LoraLayer> layer;
};

class LoraContext
{
public:
    static uint8_t register_handle(header_id_t header_id, std::shared_ptr<LoraLayer> callable);
    static uint8_t unregister_handle(header_id_t header_id);
    static std::shared_ptr<LoraLayer> get_handler(header_id_t header_id);
    static void queue_callback(std::shared_ptr<LoraLayer>, uint8_t identifier)
    {
        struct timeval tv_now;
        gettimeofday(&tv_now, NULL);
        int64_t time_us = (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
        struct packet_timeout_callbacks callback = {.time = }
        _timeouts.push()
    }

private:
    LoraContext();
    static std::unordered_map<uint8_t, std::shared_ptr<LoraLayer>> _handler;
    static std::queue<struct packet_timeout_callback> _timeouts;
};

#define LORA_SUCESS 0x00
#define LORA_WRONG_ADDRESS 0x01
#define LORA_ERR_PACKAGE_TO_SMALL 0x10
#define LORA_ERR_UNKNOWN_HEADER 0x11

#endif