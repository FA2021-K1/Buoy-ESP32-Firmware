#ifndef LORA_PROTOCOL
#define LORA_PROTOCOL

#include <list>
#include <lora_header/buoy_header.h>
#include <lora_header/btcp.h>

struct lora_context
{
    lora_context(uint16_t buoy_id) : buoy_id(buoy_id){}
    const uint16_t buoy_id;
    std::list<std::shared_ptr<struct btcp_state>> btcp_state_list;
};

uint8_t process_package(std::shared_ptr<struct lora_package> package,std::shared_ptr<struct lora_context> context);
uint8_t process_btcp(std::shared_ptr<struct lora_package> package,std::shared_ptr<struct lora_context> context);

void update_seq_number(std::shared_ptr<struct btcp_state> state, std::shared_ptr<struct lora_context> context, uint8_t ack_number);
void btcp_cleanup(std::shared_ptr<struct btcp_state> state, std::shared_ptr<struct lora_context> context);

#define LORA_SUCESS 0x00
#define LORA_WRONG_ADDRESS 0x01
#define LORA_ERR_PACKAGE_TO_SMALL 0x10
#define LORA_ERR_UNKNOWN_HEADER 0x11

#endif