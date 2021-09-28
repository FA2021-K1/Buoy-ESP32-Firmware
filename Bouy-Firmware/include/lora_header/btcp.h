#ifndef BTCP
#define BTCP

#include <cstdint>
#include <queue>
#include <memory>
#include <list>
#include <lora_header/lora_protocol.h>

using namespace std;

enum BtcpConnectionState
{
    UNINITIALIZED,
    SYN_QUEUED,
    SYN_SEND,
    SYN_ACK_SEND,
    ACK_SEND,
    ESTABLISHED,
    HANDSHAKE_SEND
};

class BtcpConnection : public LoraLayer
{
public:
    BtcpConnection(buoy_id_t remote_buoy_id, shared_ptr<LoraLayer> lower_layer);
    const buoy_id_t remote_buoy_id;
    void send(unique_ptr<struct payload> payload, unique_ptr<stack<callback_t>> callbacks) override;
    void receive(unique_ptr<struct payload> package) override;
    void connect(callback_t onConnect);
private:
    void reset();
    void send_syn();
    void send_syn_ack();
    void send_ack();
    void send_reset();
    std::unique_ptr<struct payload> make_btcp_payload(uint8_t flags, uint8_t seq_number, uint8_t ack_number, header_id_t next_header);

    uint8_t _failed_send_attempts;
    std::shared_ptr<struct payload> _last_payload;
    callback_t onConnectCallback;
    uint32_t _local_sequence_number;  //current package number -> increased by received ack
    uint32_t _remote_sequence_number; //last number that was received
    BtcpConnectionState _connection_state;
    uint8_t _failed_packages;
    queue<shared_ptr<struct lora_package>> receive_package_queue;
    queue<pair<shared_ptr<struct payload>, stack<callback_t>>> send_package_queue;
};

class BtcpBroadcastConnection : public BtcpConnection
{
    BtcpBroadcastConnection(shared_ptr<LoraLayer> lower_layer) : BtcpConnection(BUOY_ID_BROADCAST, lower_layer) {}
};

class BtcpLayer : public LoraLayer
{
public:
    BtcpLayer(shared_ptr<LoraLayer> lower_layer) : LoraLayer(lower_layer) {}
    size_t get_maximum_payload_size();
    shared_ptr<BtcpConnection> get_connection(buoy_id_t remote_id);
    void send(unique_ptr<struct payload> payload, unique_ptr<stack<callback_t>> callbacks) override;
    void receive(unique_ptr<struct payload> package) override;
    void handle_new_incoming(shared_ptr<struct payload> payload);

private:
    list<shared_ptr<BtcpConnection>> _btcp_connections_list;
};

void create_btcp_broadcast_sync_request(shared_ptr<struct lora_package> package);


#define BTCP_SUCCESS 0x00
#define BTCP_ERR_WRONG_STATE 0x10
#define BTCP_ERR_HANDSHAKE_FAILED 0x60
#define BTCP_ERR_PACKAGE_TO_SMALL 0x61
#define BTCP_ERR_WRONG_SEQ_NUMBER 0x62

#endif