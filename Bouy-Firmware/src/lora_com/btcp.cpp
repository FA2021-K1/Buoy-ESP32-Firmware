#include <lora_header/btcp.h>
#include <lora_header/buoy_header.h>

void create_btcp_broadcast_sync_request(lora_package *package, btcp_state *state)
{
    package->btcp_pack.buoy_header.sender_id = state->local_buoy_id;
    package->btcp_pack.buoy_header.receiver_id = BUOY_BROADCAST_ID;
    package->btcp_pack.buoy_header.next_header = BTCP_HEADER_ID;
    package->btcp_pack.btcp_header.seq_number = state->local_sequence_number++;
    package->btcp_pack.btcp_header.ack_number = 0;
    package->btcp_pack.btcp_header.next_header = NO_MORE_HEADER_ID;
    package->btcp_pack.btcp_header.flags = BTCP_FLAG_SYN;

    package->size = 9; // 5 Byte buoy_header; 4 byte btcp_header
}

void create_sync_response(lora_package *package, btcp_state *state)
{
    package->btcp_pack.buoy_header.sender_id = state->local_buoy_id;
    package->btcp_pack.buoy_header.receiver_id = state->remote_buoy_id;
    package->btcp_pack.buoy_header.next_header = BTCP_HEADER_ID;
    package->btcp_pack.btcp_header.seq_number = state->local_sequence_number++;
    package->btcp_pack.btcp_header.ack_number = state->remote_sequence_number;
    package->btcp_pack.btcp_header.next_header = NO_MORE_HEADER_ID;
    package->btcp_pack.btcp_header.flags = BTCP_FLAG_ACK | BTCP_FLAG_SYN;
}

void create_btcp_package(lora_package *package, btcp_state *state)
{
    package->btcp_pack.buoy_header.sender_id = state->local_buoy_id;
    package->btcp_pack.buoy_header.receiver_id = state->remote_buoy_id;
    package->btcp_pack.buoy_header.next_header = BTCP_HEADER_ID;
    package->btcp_pack.btcp_header.seq_number = state->local_sequence_number;
    package->btcp_pack.btcp_header.ack_number = state->remote_sequence_number;
    package->btcp_pack.btcp_header.flags = BTCP_FLAG_ACK;
}