
#include <lora_header/lora_hardware.h>
#include <lora_header/buoy_header.h>
#include <cstring>

LoraHardwareLayer::LoraHardwareLayer(uint16_t buoy_id) : _buoy_id(buoy_id) {}

size_t LoraHardwareLayer::get_maximum_payload_size()
{
    return LORA_PACKAGE_SIZE - BUOY_HEADER_SIZE;
}

void LoraHardwareLayer::sendTo(std::unique_ptr<struct payload> payload, uint16_t receiver_id, std::unique_ptr<PackageCallable> callback)
{
    //create package
    auto package = std::unique_ptr<struct lora_package>(new struct lora_package());
    package->buoy_header.sender_id = _buoy_id;
    package->buoy_header.receiver_id = receiver_id;
    package->buoy_header.next_header = payload->header_id;
    std::memcpy(package->data + BUOY_HEADER_SIZE, payload->data, payload->size);
    package->size = BUOY_HEADER_SIZE + payload->size;

    // enqueue package
    _send_queue.push(std::make_pair<>(std::move(package), std::move(callback)));
}