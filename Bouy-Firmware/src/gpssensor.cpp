#include <Arduino.h>
#include <TinyGPS++.h>

#include "gpssensor.h"
#include "datetime.h"
#include "hardwarelayout.h"

void GPSSensor::init() {
    Serial1.begin(9600, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN, false, 64);
    // CFG-PRT
    byte packet[] = {
        0xB5, // sync char 1
        0x62, // sync char 2
        0x06, // class
        0x00, // id
        0x14, // length
        0x00, // 
        0x01, // payload
        0x00, // payload
        0x00, // payload
        0x00, // payload
        0xD0, // payload
        0x08, // payload
        0x00, // payload
        0x00, // payload
        0x00, // payload
        0xC2, // payload
        0x01, // payload
        0x00, // payload
        0x07, // payload
        0x00, // payload
        0x03, // payload
        0x00, // payload
        0x00, // payload
        0x00, // payload
        0x00, // payload
        0x00, // payload
        
        0xC0, // CK_A
        0x7E, // CK_B
    };
    for(int i = 0; i < sizeof(packet); i++) {
        Serial1.write(packet[i]);
    }
    delay(100);
    Serial1.flush();

    Serial1.begin(115200, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN, false, 64);
}

Location GPSSensor::get_location()
{
    int i = 1000;
    while (i > 0) {
        while(!(Serial1.available() > 0)) {
            delay(1);
        }
        byte gpsData = Serial1.read();
        _tgps.encode(gpsData);
        Serial.write(gpsData);
        if (_tgps.location.isUpdated()){
            Serial.print("Latitude= "); 
            Serial.print(_tgps.location.lat(), 6);
            Serial.print(" Longitude= "); 
            Serial.println(_tgps.location.lng(), 6);
            break;
        }
        i--;
    }

    if (i == 0)
    {
        _status = NO_FIX;
        Serial.println("GPS: no fix!");
    }
    else {
        _status = VALID;
        Serial.println("GPS: position valid");
    }

    _hdop = _tgps.hdop.value();

    return std::pair<double, double>(_tgps.location.lat(), _tgps.location.lng());
}

int32_t GPSSensor::get_hdop()
{
    return _hdop;
}

GPSStatus GPSSensor::get_status()
{
    return _status;
}

DateTime GPSSensor::get_datetime()
{
    int i = 1000;
    while (i > 0) {
        while (!Serial1.available() > 0) {
            delay(1);
        }
        byte gpsData = Serial1.read();
        _tgps.encode(gpsData);
        Serial.write(gpsData);
        if (_tgps.time.isUpdated() && _tgps.date.isUpdated()){
            break;
        }
        i--;
    }

    if (i == 0) {
        _status = NO_FIX;
        Serial.println("GPS: no fix!");
    }
    else {
        _status = VALID;
        Serial.println("GPS: DateTime valid");
    }

    DateTime dt(_tgps.date.year(), _tgps.date.month(), _tgps.date.day(),
                _tgps.time.hour() + 2, _tgps.time.minute(),
                _tgps.time.second(), _tgps.time.centisecond());

    return dt;
}
