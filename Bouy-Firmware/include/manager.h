#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "hardwareclasses/buoy.h"
#include "hardwareclasses/rasppi.h"
// #include "hardwareclasses/sdcard.h"
#include "hardwareclasses/tdssensor.h"
#include "hardwareclasses/gpssensor.h"
// #include "hardwareclasses/buoyble.h"
// #include "hardwareclasses/loramodule.h"

/**
 * The Manager class owns all objects except for the sensor which belong to Buoy.
 * It also handles all program logic.
 */
class Manager {
public:
  Manager();

  /**
   * Instantiates all HW objects. Creates shared pointers in manager.
   */
  void createObjects();

  /**
   * Initializes timer interrupts.
   */
  void setupTimers();

  /**
   * Poll GPS, sample all sensors, create SensorData object, write to SDCard.
   */
  void takeMeasurements();

  /**
   * One-by-one load measurement file and send to Rasppi.
   */
  void dumpMeasurements();

  /**
   * Check for any interrupts (measurement timer, bluetooth for now).
   */
  void execute();

  std::shared_ptr<Buoy> get_buoy() {return _buoy;}
  std::shared_ptr<RaspPi> get_rasppi() {return _rasppi;}
  // std::shared_ptr<SDCard> get_sdcard() {return _sdcard;}
  std::shared_ptr<GPSSensor> get_gpssensor() {return _gpssensor;}
  // std::shared_ptr<BuoyBLE> get_buoyble() {return _buoyble;}
  // std::shared_ptr<LoraModule> get_lora() {return _lora;}

  // void startTransmission() {
  //   this->_startTransmission = true;
  // }

private:
  std::shared_ptr<Buoy> _buoy;
  std::shared_ptr<RaspPi> _rasppi;
  // std::shared_ptr<SDCard> _sdcard;
  std::shared_ptr<GPSSensor> _gpssensor;
  // std::shared_ptr<BuoyBLE> _buoyble;
  // std::shared_ptr<LoraModule> _lora;

  uint32_t _measurement_id;

  // volatile bool _startTransmission;
};

#endif
