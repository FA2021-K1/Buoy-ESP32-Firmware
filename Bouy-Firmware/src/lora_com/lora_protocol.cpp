#include <lora_header/lora_protocol.h>
#include <hardwarelayout.h>
#include <algorithm>
#include <iterator>

using namespace std;

uint8_t LoraContext::register_handle(header_id_t header_id, shared_ptr<LoraLayer> callable)
{
    if (_handler.find(header_id) == _handler.end())
    {
        _handler.insert(make_pair(header_id, callable));
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}

uint8_t LoraContext::unregister_handle(header_id_t header_id)
{
    auto handle = _handler.find(header_id);
    if (handle == _handler.end())
    {
        return EXIT_FAILURE;
    }
    else
    {
        _handler.erase(handle);
        return EXIT_SUCCESS;
    }
}

std::shared_ptr<LoraLayer> LoraContext::get_handler(header_id_t header_id)
{
    auto handle = _handler.find(header_id);
    if (handle == _handler.end())
        return nullptr;
    else
        return handle->second;
}
/*
uint8_t process_package(std::shared_ptr<struct lora_package> package, std::shared_ptr<struct lora_context> context)
{
    if (package->size < BUOY_HEADER_SIZE)
        return LORA_ERR_PACKAGE_TO_SMALL;
    if (package->buoy_header.receiver_id != context->buoy_id && package->buoy_header.receiver_id != BUOY_ID_BROADCAST)
    {
        // got package that was not for us
        return LORA_WRONG_ADDRESS;
    }

    switch (package->buoy_header.next_header)
    {
    case BTCP_HEADER_ID:
        return process_btcp(package, context);
        break;
    default:
        return LORA_ERR_UNKNOWN_HEADER;
        break;
    }
}

uint8_t process_btcp(std::shared_ptr<struct lora_package> package, std::shared_ptr<struct lora_context> context)
{
    if (package->size < BUOY_HEADER_SIZE + BTCP_HEADER_SIZE)
        return BTCP_ERR_PACKAGE_TO_SMALL;

    //look if already have state of that buoy
    std::shared_ptr<struct btcp_state> btcp_state;
    auto it = find_if(context->btcp_state_list.begin(), context->btcp_state_list.end(), [&package](const std::shared_ptr<struct btcp_state>& ptr){return package->buoy_header.sender_id == ptr->remote_buoy_id;});
    if(it != context->btcp_state_list.end()) btcp_state = *it;

    // create state struct if necessary
    if (btcp_state == nullptr)
    {
        btcp_state = std::make_shared<struct btcp_state>();
        //add new struct to list
        context->btcp_state_list.push_back(btcp_state);
        //init state
        btcp_state->remote_buoy_id = package->buoy_header.sender_id;
        btcp_state->local_buoy_id = context->buoy_id;
        btcp_state->local_sequence_number = 0;
        btcp_state->remote_sequence_number = 0;
        btcp_state->failed_packages = 0;
        btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
    }

    switch (btcp_state->connection_state)
    {
    case BTCP_CONNECTION_SYN_SEND:
        //ack,syn flag should be set
        if (!(package->btcp_pack.btcp_header.flags & BTCP_FLAG_ACK) || !(package->btcp_pack.btcp_header.flags & BTCP_FLAG_SYN))
        {
            btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
            return BTCP_ERR_HANDSHAKE_FAILED;
        }
        //check that ack number is correct
        if (package->btcp_pack.btcp_header.ack_number == btcp_state->local_sequence_number)
        {
            btcp_state->local_sequence_number++;
            btcp_state->remote_sequence_number = package->btcp_pack.btcp_header.seq_number;
            btcp_state->connection_state = BTCP_CONNECTION_SYN_ACK_RECEIVED;
        }
        else
        {
            btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
            return BTCP_ERR_HANDSHAKE_FAILED;
        }
        break;
    case BTCP_CONNECTION_UNINITIALIZED: //FALLTHROUGH
    case BTCP_CONNECTION_CLOSED:
        //syn flag should be set
        if (!(package->btcp_pack.btcp_header.flags & BTCP_FLAG_SYN))
        {
            btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
            return BTCP_ERR_HANDSHAKE_FAILED;
        }
        //check if ack flag is set as well
        if (package->btcp_pack.btcp_header.flags & BTCP_FLAG_ACK)
        {
            // we get syn, ack but haven't sent a syn, maybe we sent a broadcast syn
            std::list<std::shared_ptr<struct btcp_state>>::iterator broadcast_btcp_state_it;
            std::shared_ptr<struct btcp_state> broadcast_btcp_state = nullptr;
            for (broadcast_btcp_state_it = context->btcp_state_list.begin(); broadcast_btcp_state_it != context->btcp_state_list.end(); broadcast_btcp_state_it++)
                if ((*broadcast_btcp_state_it)->remote_buoy_id != BUOY_ID_BROADCAST)
                {
                    broadcast_btcp_state = (*broadcast_btcp_state_it);
                    break;
                }
            if (broadcast_btcp_state == nullptr)
            {
                // we did not find any broadcast so we haven't sent any syn
                btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
                return BTCP_ERR_HANDSHAKE_FAILED;
            }
            //check if ack number matches
            if (package->btcp_pack.btcp_header.ack_number == broadcast_btcp_state->local_sequence_number)
            {
                btcp_state->local_sequence_number = broadcast_btcp_state->local_sequence_number;
                btcp_state->remote_sequence_number = package->btcp_pack.btcp_header.seq_number;
            }
            else
            {
                btcp_state->connection_state = BTCP_CONNECTION_UNINITIALIZED;
                return BTCP_ERR_HANDSHAKE_FAILED;
            }
        }
        else
        {
            //syn request-> respond with syn, ack
            btcp_state->remote_sequence_number = package->btcp_pack.btcp_header.seq_number;
            btcp_state->connection_state = BTCP_CONNECTION_SYN_RECEIVED;
        }
    case BTCP_CONNECTION_ESTABLISHED:
        //syn flag should not be set, but will be ignored
        //check seq number
        if (package->btcp_pack.btcp_header.seq_number != btcp_state->remote_sequence_number)
        {
            btcp_state->failed_packages++; //TODO maybe ACK was lost
            return BTCP_ERR_WRONG_SEQ_NUMBER;
        }
        if (package->btcp_pack.btcp_header.flags & BTCP_FLAG_RST)
        {
            //hard reset of connection
            btcp_cleanup(btcp_state, context);
            return BTCP_SUCCESS;
        }
        if (package->btcp_pack.btcp_header.flags & BTCP_FLAG_ACK)
        {
            update_seq_number(btcp_state, context, package->btcp_pack.btcp_header.ack_number);
        }
        if (package->btcp_pack.btcp_header.flags & BTCP_FLAG_FIN)
        {
            //close of connection requested
            btcp_state->connection_state = BTCP_CONNECTION_FIN_RECEIVED;
        }

        //process following data

        break;
    default:
        //should not happen
        break;
    }
    return BTCP_SUCCESS;
}

void btcp_cleanup(std::shared_ptr<struct btcp_state> state, std::shared_ptr<struct lora_context> context)
{
    state->connection_state = BTCP_CONNECTION_CLOSED;
}

void update_seq_number(std::shared_ptr<struct btcp_state> state, std::shared_ptr<struct lora_context> context, uint8_t ack_number)
{
    if (state->local_sequence_number == ack_number)
    {
        //last packages is acknowledged, next package can be sent
    }
    else if (state->local_sequence_number - 1 == ack_number)
    {
        //last package was not received, resend package
    }
}*/