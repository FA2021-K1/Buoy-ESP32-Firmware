#ifndef LORA_BUOY_HEADER
#define LORA_BUOY_HEADER

#include <cstdint>

#define NO_MORE_HEADER_ID 0

/* BUOY Header ----------------------------------------------*/
struct __attribute__((__packed__)) buoy_header
{
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t next_header;
};

#define BUOY_HEADER_SIZE 5
#define BUOY_BROADCAST_ID 0xffff

/* BTCP Header ----------------------------------------------*/
#define BTCP_HEADER_ID 0x06
#define BTCP_HEADER_SIZE 4

struct __attribute__((__packed__)) btcp_header
{
    uint8_t seq_number;
    uint8_t ack_number;
    uint8_t flags;
    uint8_t next_header;
};

#define BTCP_FLAG_ACK 0b00000001
#define BTCP_FLAG_SYN 0b00000010
#define BTCP_FLAG_RST 0b00000100
#define BTCP_FLAG_FIN 0b00001000


/* Metadata Header ----------------------------------------------*/
#define METADATA_HEADER_ID 0x10
#define METADATA_HEADER_SIZE 2

struct __attribute__((__packed__)) metadata_header
{
    uint8_t size;
    uint8_t next_header;
};

#define METADATA_FLAG_MD 0b10000000
#define METADATA_SIZE_MASK 0b01111111

/* Measurement Header ----------------------------------------------*/
#define MEASUREMENT_HEADER_ID 0x11
#define MEASUREMENT_HEADER_SIZE 2

#define MEASUREMENT_FLAG_MD 0b10000000
#define MEASUREMENT_SIZE_MASK 0b01111111

typedef metadata_header measurement_header;

/* Metadata payload field ----------------------------------------------*/
struct __attribute__((__packed__)) metadata_payload_field
{
    uint16_t buoy_id;
    uint32_t latest_measurement_id;
    uint32_t oldest_measurement_id; //has not been saved yet
};
#define METADATA_PAYLOAD_FIELD_SIZE 10

/* Measurement payload special field ----------------------------------------------*/
struct __attribute__((__packed__)) measurement_payload_special_field
{
    uint16_t buoy_id;
    float latitude;
    float longitude;
    uint32_t timestamp; //unix time
};
#define MEASUREMENT_PAYLOAD_SPECIAL_FIELD_SIZE 14

/* Measurement payload value field ----------------------------------------------*/
struct __attribute__((__packed__)) measurement_payload_value_field
{
    uint8_t sensor_id;
    uint8_t type_id;
    double value;
};
#define MEASUREMENT_PAYLOAD_VALUE_FIELD_SIZE 10

/* Lora Package ---------------------------------------------*/
struct lora_package
{
    union{
        struct buoy_header buoy_header;
        struct __attribute__((__packed__)){
            struct buoy_header buoy_header;
            struct btcp_header btcp_header;
        } btcp_pack;
        uint8_t data[255];
    };
    uint8_t size;
    uint8_t state;
};


#define PACKAGE_STATE_ENQUEUED 0x00
#define PACKAGE_STATE_SEND 0x10
#define PACKAGE_STATE_ACK 0x11
#define PACKAGE_STATE_RECEIVED 0x20
#define PACKAGE_STATE_RECEIVED_ACK_SEND 0x21

#endif