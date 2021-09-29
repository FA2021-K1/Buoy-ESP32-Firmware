#include <lora_header/callback_timer.h>
#include <FreeRTOS.h>

CallbackTimer::CallbackTimer(LoraLayer* subscriber,uint8_t id) : _subscriber(subscriber){
    _running = false;
    _id = id;
}
void CallbackTimer::start(int64_t time) {
    _running = true;
    _timeout = xTaskGetTickCount() + time;
}
void CallbackTimer::stop(){
    _running = false;
}

void CallbackTimer::update(){
    if(_running){
        if(xTaskGetTickCount() >= _timeout){
            _running = false;
            _subscriber->onTimeout(_id);
        }
    }
}