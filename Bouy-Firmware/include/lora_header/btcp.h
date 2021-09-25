#ifndef BTCP
#define BTCP

#include <cstdint>
#include <queue>
#include <memory>
#include <lora_header/buoy_header.h>

struct btcp_state
{
    uint16_t local_buoy_id;
    uint16_t remote_buoy_id;
    uint32_t local_sequence_number;  //next number to be send
    uint32_t remote_sequence_number; //next number to be received
    uint8_t connection_state;
    uint8_t failed_packages;
    std::queue<std::shared_ptr<struct lora_package>> receive_package_queue;
    std::queue<std::shared_ptr<struct lora_package>> send_package_queue;
};

void create_btcp_broadcast_sync_request(std::shared_ptr<struct lora_package> package);

#define BTCP_CONNECTION_ESTABLISHED 0x10
#define BTCP_CONNECTION_SYN_SEND 0x11
#define BTCP_CONNECTION_SYN_RECEIVED 0x12
#define BTCP_CONNECTION_SYN_ACK_RECEIVED 0x13
#define BTCP_CONNECTION_SYN_ACK_SEND 0x14
#define BTCP_CONNECTION_UNINITIALIZED 0x20
#define BTCP_CONNECTION_CLOSED 0x21
#define BTCP_CONNECTION_FIN_RECEIVED 0x30

#define BTCP_SUCCESS 0x00
#define BTCP_ERR_HANDSHAKE_FAILED 0x60
#define BTCP_ERR_PACKAGE_TO_SMALL 0x61
#define BTCP_ERR_WRONG_SEQ_NUMBER 0x62

#endif