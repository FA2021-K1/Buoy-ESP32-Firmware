#include <memory>

#include "buoy.h"
#include "rasppi.h"
#include "manager.h"

void Manager::create_objects() {
    _buoy = std::make_shared<Buoy>(1234);
    _rasppi = std::make_shared<RaspPi>();
    _sdcard = std::make_shared<SDCard>();
    _sdcard->init();
}