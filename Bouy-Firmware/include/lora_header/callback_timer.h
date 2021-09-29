#ifndef CALLBACK_TIMER
#define CALLBACK_TIMER

#include <lora_header/lora_protocol.h>

class CallbackTimer
{
public:
    CallbackTimer(LoraLayer* subscriber, uint8_t id);
    void start(int64_t time);
    void stop();
    void update();

private:
    int64_t _timeout;
    bool _running;
    uint8_t _id;
    LoraLayer* const _subscriber;
};

#endif