
#include <lora_header/lora_hardware.h>
#include <cstring>

using namespace std;

LoraHardwareLayer::LoraHardwareLayer(buoy_id_t buoy_id) : LoraLayer(nullptr), _buoy_id(buoy_id) {}

size_t LoraHardwareLayer::get_maximum_payload_size()
{
    return LORA_PACKAGE_SIZE - BUOY_HEADER_SIZE;
}

void LoraHardwareLayer::receive(unique_ptr<struct payload> payload)
{
    if (payload->size < BUOY_HEADER_SIZE)
        return;
    struct buoy_header buoy_header;
    memcpy(&buoy_header, payload->data, BUOY_HEADER_SIZE);

    //check receiver id
    if (buoy_header.receiver_id == _buoy_id || buoy_header.receiver_id == BUOY_ID_BROADCAST)
    {
        //check if a handler is registered
        auto handle = LoraContext::get_handler(buoy_header.next_header);
        if (handle != nullptr)
        {
            unique_ptr<struct payload> next_payload = unique_ptr<struct payload>(new struct payload(buoy_header.sender_id, BUOY_ID_UNDEFINED, buoy_header.next_header));
            memcpy(next_payload->data, payload->data + BUOY_HEADER_SIZE, payload->size - BUOY_HEADER_SIZE);
            handle->receive(move(next_payload));
        }
    }
}

void LoraHardwareLayer::send(unique_ptr<struct payload> payload, unique_ptr<stack<callback_t>> callbacks)
{
    //create package
    auto package = unique_ptr<struct lora_package>(new struct lora_package());
    package->buoy_header.sender_id = _buoy_id;
    package->buoy_header.receiver_id = payload->receiver_id;
    package->buoy_header.next_header = payload->header_id;
    memcpy(package->data + BUOY_HEADER_SIZE, payload->data, payload->size);
    package->size = BUOY_HEADER_SIZE + payload->size;

    // enqueue package
    _send_queue.push(make_pair(move(package), move(callbacks)));
}