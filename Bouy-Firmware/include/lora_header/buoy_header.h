#ifndef LORA_BUOY_HEADER
#define LORA_BUOY_HEADER

#include <cstdint>

struct buoy_header
{
    uint16_t sender_id;
    uint16_t receiver_id;
    uint8_t next_header;
};

struct btcp_header
{
    uint8_t seq_number;
    uint8_t ack_number;
    union{
        uint8_t raw_flags;
        struct
        {
            uint8_t ack : 1,
                    syn : 1,
                    rst : 1,
                    fin : 1,
                    reserved : 4;
        };        
    };
    uint8_t flags;
    uint8_t next_header;
};

struct metadata_header
{
    struct
    {
        uint8_t more_data : 1,
                size      : 7;
    };
    uint8_t next_header;
};

typedef metadata_header measurement_header;

struct meta_data_payload_field
{
    uint16_t buoy_id;
    uint32_t latest_measurement_id;
    uint32_t oldest_measurement_id; //has not been saved yet
};

struct measurement_payload_special_field
{
    uint16_t buoy_id;
    float latitude;
    float longitude;
    uint32_t timestamp; //unix time
};

struct measurement_payload_value_field
{
    uint8_t sensor_id;
    uint8_t type_id;
    double value;
};

#endif