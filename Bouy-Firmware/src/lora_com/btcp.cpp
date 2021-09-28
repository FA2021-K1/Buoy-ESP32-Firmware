#include <lora_header/btcp.h>
#include <lora_header/buoy_header.h>
#include <lora_header/lora_hardware.h>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

BtcpConnection::BtcpConnection(buoy_id_t remote_buoy_id, shared_ptr<LoraLayer> lower_layer) : LoraLayer(lower_layer), remote_buoy_id(remote_buoy_id)
{
    _connection_state = BtcpConnectionState::UNINITIALIZED;
}

void BtcpConnection::connect(callback_t onConnect)
{
    if (_connection_state == BtcpConnectionState::UNINITIALIZED)
    {
        onConnectCallback = onConnect;
        send_syn();
    }
    else
    {
        onConnect(BTCP_ERR_WRONG_STATE);
    }
}

void BtcpConnection::send_syn()
{
    auto payload = make_btcp_payload(BTCP_FLAG_SYN, _local_sequence_number, 0, NO_MORE_HEADER_ID);
    _failed_send_attempts = 0;
    _last_payload = payload->clone();
    _connection_state = BtcpConnectionState::SYN_SEND;
    _lower_layer->send(std::move(payload), nullptr);
}

void BtcpConnection::send(unique_ptr<struct payload> payload, unique_ptr<stack<callback_t>> callbacks)
{
}

void BtcpConnection::receive(unique_ptr<struct payload> payload)
{
    if (payload->size < BTCP_HEADER_SIZE)
        return;
    struct btcp_header *btcp_header = reinterpret_cast<struct btcp_header *>(payload->data);

    if (btcp_header->flags & BTCP_FLAG_RST)
    {
        reset();
        return;
    }

    switch (_connection_state)
    {
    case BtcpConnectionState::UNINITIALIZED:
        // only a handshake with syn flag set will be accepted
        if (btcp_header->flags == BTCP_FLAG_SYN)
        {
            _remote_sequence_number = btcp_header->seq_number;
            send_syn_ack();
        }
        //ignore other packages
        break;
    case BtcpConnectionState::SYN_SEND:
        if (btcp_header->flags == (BTCP_FLAG_ACK | BTCP_FLAG_SYN))
        {
            _remote_sequence_number = btcp_header->seq_number;
            //respond with ack
            //check if received ack_number is correct
            if (btcp_header->ack_number == _local_sequence_number + 1)
            {
                _local_sequence_number++;
                send_ack();
            }
            else
            {
                send_reset();
            }
        }
        else if (btcp_header->flags == BTCP_FLAG_SYN)
        {
            // reset connection, try again
            send_reset();
        }
        else
        {
            //ignore package
        }
        break;
    case BtcpConnectionState::SYN_ACK_SEND:
        if (btcp_header->flags == BTCP_FLAG_SYN)
        {
            // guess that our syn,ack package was not received
            _remote_sequence_number = btcp_header->seq_number;
            send_syn_ack();
        }
        else if (btcp_header->flags == BTCP_FLAG_ACK)
        {
            //check sequence number
            if (btcp_header->ack_number == _local_sequence_number + 1)
            {
                _connection_state = BtcpConnectionState::ESTABLISHED;
            }
            else
            {
                send_reset();
            }
        }
        else
        {
            send_reset();
        }

        break;
    default:
        break;
    }
}

void BtcpConnection::send_reset()
{
    unique_ptr<struct payload> payload = unique_ptr<struct payload>(new struct payload(BUOY_ID_UNDEFINED, remote_buoy_id, BTCP_HEADER_ID));
    struct btcp_header *btcp_header = reinterpret_cast<struct btcp_header *>(payload->data);
    btcp_header->flags = BTCP_FLAG_RST;
    btcp_header->next_header = NO_MORE_HEADER_ID;
    payload->size = BTCP_HEADER_SIZE;
    auto callback_stack = unique_ptr<stack<callback_t>>(new stack<callback_t>());
    auto callback = [this]()
    { this->_connection_state = BtcpConnectionState::UNINITIALIZED; };
    callback_stack->push(callback);
    _connection_state = BtcpConnectionState::RESET_QUEUED;
    _lower_layer->send(move(payload), move(callback_stack));
    reset();
}

void BtcpConnection::reset()
{
    _connection_state = BtcpConnectionState::UNINITIALIZED;
}

unique_ptr<struct payload> BtcpConnection::make_btcp_payload(uint8_t flags, uint8_t seq_number, uint8_t ack_number, header_id_t next_header)
{
    unique_ptr<struct payload> payload = unique_ptr<struct payload>(new struct payload(BUOY_ID_UNDEFINED, remote_buoy_id, BTCP_HEADER_ID));
    struct btcp_header *btcp_header = reinterpret_cast<struct btcp_header *>(payload->data);
    btcp_header->flags = flags;
    btcp_header->seq_number = seq_number;
    btcp_header->ack_number = ack_number;
    btcp_header->next_header = next_header;
    payload->size = BTCP_HEADER_SIZE;
    return payload;
}

void BtcpConnection::send_ack()
{
    auto payload = make_btcp_payload(BTCP_FLAG_ACK, _local_sequence_number, _remote_sequence_number + 1, NO_MORE_HEADER_ID);
    auto callback_stack = unique_ptr<stack<callback_t>>(new stack<callback_t>());
    auto callback = [this]()
    { this->_connection_state = BtcpConnectionState::ACK_SEND; };
    callback_stack->push(callback);
    _connection_state = BtcpConnectionState::ACK_QUEUED;
    _lower_layer->send(move(payload), move(callback_stack));
}

void BtcpConnection::send_syn_ack()
{
    auto payload = make_btcp_payload(BTCP_FLAG_SYN | BTCP_FLAG_ACK, );
    unique_ptr<struct payload> payload = unique_ptr<struct payload>(new struct payload(BUOY_ID_UNDEFINED, remote_buoy_id, BTCP_HEADER_ID));
    struct btcp_header *btcp_header = reinterpret_cast<struct btcp_header *>(payload->data);
    btcp_header->flags = BTCP_FLAG_ACK | BTCP_FLAG_SYN;
    btcp_header->seq_number = _local_sequence_number;
    btcp_header->ack_number = _remote_sequence_number + 1;
    btcp_header->next_header = NO_MORE_HEADER_ID;
    payload->size = BTCP_HEADER_SIZE;
    auto callback_stack = unique_ptr<stack<callback_t>>(new stack<callback_t>());
    auto callback = [this]()
    { this->_connection_state = BtcpConnectionState::SYN_ACK_SEND; };
    callback_stack->push(callback);
    _connection_state = BtcpConnectionState::SYN_ACK_QUEUED;
    _lower_layer->send(move(payload), move(callback_stack));
}

void BtcpLayer::receive(unique_ptr<struct payload> payload)
{
    shared_ptr<BtcpConnection> btcp_connection;
    auto it = find_if(_btcp_connections_list.begin(), _btcp_connections_list.end(), [&payload](const shared_ptr<BtcpConnection> &ptr)
                      { return payload->sender_id == ptr->remote_buoy_id; });
    if (it == _btcp_connections_list.end())
        handle_new_incoming(move(payload)); //no endpoint exists
    else
    {
        btcp_connection = *it;
        btcp_connection->receive(move(payload));
    }
}

void BtcpLayer::handle_new_incoming(shared_ptr<struct payload> payload)
{
    struct btcp_header btcp_header;
    memcpy(&btcp_header, payload->data, BTCP_HEADER_SIZE);
    if (btcp_header.flags == BTCP_FLAG_SYN)
    {
        //tcp handshake request
        //TODO
    }
}

shared_ptr<BtcpConnection> BtcpLayer::get_connection(uint16_t remote_id)
{
    shared_ptr<BtcpConnection> btcp_connection;
    auto it = find_if(_btcp_connections_list.begin(), _btcp_connections_list.end(), [&remote_id](const shared_ptr<BtcpConnection> &ptr)
                      { return remote_id == ptr->remote_buoy_id; });
    if (it == _btcp_connections_list.end())
    {
        btcp_connection = make_shared<BtcpConnection>(remote_id, _lower_layer);
        _btcp_connections_list.push_back(btcp_connection);
        return btcp_connection;
    }
    else
    {
        return *it;
    }
}

size_t BtcpLayer::get_maximum_payload_size()
{
    return LoraHardwareLayer::get_maximum_payload_size() - BTCP_HEADER_SIZE;
}