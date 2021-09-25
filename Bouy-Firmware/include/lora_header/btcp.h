#ifndef BTCP
#define BTCP

#include <cstdint>

struct btcp_state
{
    uint16_t remote_buoy_id;
    uint32_t local_sequence_number; //next number to be send
    uint32_t remote_sequence_number; //next number to be received
    uint8_t connection_state;
};

#define BTCP_CONNECTION_ESTABLISHED 0x10
#define BTCP_CONNECTION_SYN_RECEIVED 0x11


#endif