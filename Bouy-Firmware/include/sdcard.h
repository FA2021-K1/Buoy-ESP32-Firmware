/***
 * SD Card class
 */
#ifndef SD_CARD_INTERFACE_H
#define SD_CARD_INTERFACE_H

#include <cstdint>
#include <vector>
#include <tuple>
#include <memory>

#include "metadata.h"
#include "global_enums.h"
#include "sensordata.h"

/**
 * Class that corresponds to the SDCard connected to the microcontroller.
 */
class SDCard {
public:
    SDCard(uint16_t buoy_id);
    
    /**
     * Initialize SPI connection. Check if folders / files exists, otherwise create.
     */
    void init();
    
    /**
     * Save one measurement (can contain multiple values) to SDCard.
     * Update Metadata + sanity checks.
     */
    void writeSensorData(SensorData sensordata);
    SensorData readSensorData(uint16_t buoy_id, uint32_t measurement_id);
    
    /**
     * Create new MetaData object from the saved json file on the SDCard.
     */
    void loadMetaData();

    uint32_t get_capacity() {return _capacity;}
    buoyStates_t get_buoy_states() {return _meta_data->_buoy_states;}

    /**
     * Given a new buoyStates object update the 
     */
    void setMetaDataFirstIDs(buoyStates_t new_buoy_states);

private:
    const uint16_t _buoy_id;
    uint32_t _capacity;
    std::unique_ptr<const MetaData> _meta_data;
};

#endif