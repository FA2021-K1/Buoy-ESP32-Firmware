#include <memory>

#include "buoy.h"
#include "manager.h"
#include "rasppi.h"
#include "sensordata.h"
#include "value.h"
#include "sensors/tdssensor.h"
#include "raspicom/raspcommands.h"
#include "buoyble.h"
#include "datetime.h"
 
volatile int measurement_timer_counter;
hw_timer_t* measurement_timer = NULL;
portMUX_TYPE measurement_timer_mux = portMUX_INITIALIZER_UNLOCKED;

/**
 * Callback function for measurement timer interrupt
 */
void IRAM_ATTR measurementCallback() {
    portENTER_CRITICAL_ISR(&measurement_timer_mux);
    measurement_timer_counter++;
    portEXIT_CRITICAL_ISR(&measurement_timer_mux);
}


Manager::Manager() {
    _startTransmission = false;
}


void Manager::setupTimers() {
    measurement_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(measurement_timer, &measurementCallback, true);
    timerAlarmWrite(measurement_timer, 10000000, true);
    timerAlarmEnable(measurement_timer);
}


void Manager::takeMeasurements() {

    // // poll time and location from GPS module
    // Location_t location = _gpssensor->get_location();
    // DateTime datetime = _gpssensor->get_datetime();

    // mock gps data
    Location_t location(123, -1.2);
    DateTime datetime(2013, 11, 11, 11, 11, 11, 99);

    // sample all sensors and create SensorData instance
    auto all_values = _buoy->sampleAllSensors();
    auto buoy_id = _buoy->get_buoy_id();
    auto last_id = _sdcard->get_buoy_states().at(buoy_id).second;
    SensorData sensordata(buoy_id, last_id, location, datetime, all_values);

    // print to json string to Serial and save to sdcard
    Serial.println("Printing obtained SensorData: ");
    Serial.println(sensordata.toJsonString().c_str());
    _sdcard->writeSensorData(sensordata);
}


void Manager::dumpMeasurements() {

    // SensorData test_read = _sdcard->readSensorData(_buoy->get_buoy_id(), );
    // if (test_read) {Serial.println("FOUND FILE");}
    // else {Serial.println("FILE NOT FOUND");}

    // _rasppi->turnOn();
    // vTaskDelay(10000 / portTICK_PERIOD_MS);
    // TransferDumpCommand dumpCommand = TransferDumpCommand(sensordata.toJsonString());    
    // _rasppi->writeData(dumpCommand.toJsonString());

    // // wait for ping from BLE module
    // while (_buoyble->getValue_bool()) {
    //     delay(1000);
    // }
}


void Manager::createObjects() {
    _buoy = std::make_shared<Buoy>(1234);
    // _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>(_buoy->get_buoy_id());
    // _gpssensor = std::make_shared<GPSSensor>();
    _buoyble = std::make_shared<BuoyBLE>();

    // attach sensors
    _buoy->attachSensor(std::make_shared<TDSSensor>(7));
    _buoy->attachSensor(std::make_shared<TDSSensor>(18));
    
    _sdcard->init();
    // _gpssensor->init();
    _buoyble->init();

    _sdcard->loadMetaData();

}


void Manager::execute() {

    // test for measurement timer
    if (measurement_timer_counter > 0) {
        portENTER_CRITICAL_ISR(&measurement_timer_mux);
        measurement_timer_counter--;
        portEXIT_CRITICAL_ISR(&measurement_timer_mux);
        
        Serial.println("Measurement Interrupt called!");
        takeMeasurements();
    }

    // wait for ping from BLE module
    if (_buoyble->getValue_bool()) {
        dumpMeasurements();
    }

}