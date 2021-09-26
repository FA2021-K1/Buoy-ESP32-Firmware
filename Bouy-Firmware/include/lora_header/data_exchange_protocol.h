#ifndef DATA_EXCHANGE_PROTOCOL
#define DATA_EXCHANGE_PROTOCOL

#include <memory>
#include <lora_header/btcp.h>

#include "lwip/sockets.h"
#include "lwip/sys.h"

enum DataProtocolState
{
    NEW,
    WAITING,
    METADATA_EXCHANGE,
    MEASUREMENTS_EXCHANGE
};

struct remote_buoy
{
    std::shared_ptr<struct btcp_state> btcp_state;
    DataProtocolState prot_state;
};

#endif