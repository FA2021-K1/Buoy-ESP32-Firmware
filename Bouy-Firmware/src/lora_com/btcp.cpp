#include <lora_header/btcp.h>
#include <lora_header/buoy_header.h>

BtcpConnection::BtcpConnection(uint16_t local_buoy_id, uint16_t remote_buoy_id) : local_buoy_id(local_buoy_id), remote_buoy_id(remote_buoy_id)
{
    _connection_state = BtcpConnectionState::UNINITIALIZED;
}

void BtcpConnection::onPackageSend(std::shared_ptr<struct payload> payload)
{
}

void BtcpConnection::onPackageReceived(std::shared_ptr<struct payload> payload)
{
}

uint8_t BtcpLayer::register_connection(uint16_t remove_buoy_id, std::shared_ptr<BtcpConnection> connection){
    //check if a connection to this buoy is already registered
     
}

size_t BtcpLayer::get_maximum_payload_size()
{
    return LoraHardwareLayer::get_maximum_payload_size() - BTCP_HEADER_SIZE;
}