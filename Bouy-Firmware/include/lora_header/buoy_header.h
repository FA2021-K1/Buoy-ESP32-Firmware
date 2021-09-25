#ifndef LORA_BUOY_HEADER
#define LORA_BUOY_HEADER

#include <cstdint>


/* BUOY Header ----------------------------------------------*/
struct buoy_header
{
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t next_header;
};

#define BUOY_BROADCAST_ID 0xffff

/* BTCP Header ----------------------------------------------*/
#define BTCP_HEADER_ID 0x06

struct btcp_header
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

struct metadata_header
{
    uint8_t size;
    uint8_t next_header;
};

#define METADATA_FLAG_MD 0b10000000
#define MEASUREMENT_FLAG_MD 0b10000000


/* Measurement Header ----------------------------------------------*/
#define MEASUREMENT_HEADER_ID 0x11

#define METADATA_SIZE_MASK 0b01111111
#define MEASUREMENT_SIZE_MASK 0b01111111

typedef metadata_header measurement_header;

/* Metadata payload field ----------------------------------------------*/
struct metadata_payload_field
{
    uint16_t buoy_id;
    uint32_t latest_measurement_id;
    uint32_t oldest_measurement_id; //has not been saved yet
};

/* Measurement payload special field ----------------------------------------------*/
struct measurement_payload_special_field
{
    uint16_t buoy_id;
    float latitude;
    float longitude;
    uint32_t timestamp; //unix time
};

/* Measurement payload value field ----------------------------------------------*/
struct measurement_payload_value_field
{
    uint8_t sensor_id;
    uint8_t type_id;
    double value;
};

/* Lora Package ---------------------------------------------*/
struct lora_package
{
    union{
        struct buoy_header buoy_header;
        struct{
            struct buoy_header buoy_header;
            struct btcp_header btcp_header;
        } btcp_pack;
        uint8_t data[255];
    };
    uint8_t size;
};

#endif