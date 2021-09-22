#include "gpssensor.h"
#include <Arduino.h>
#include <TinyGPS++.h>

void GPSSensor::init()
{
    Serial1.begin(9600, SERIAL_8N1, 12, 14, false, 64);
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

    Serial1.begin(115200, SERIAL_8N1, 12, 14, false, 64);
}

location_t GPSSensor::getLocation()
{
    int i = 1000;
    while (i > 0) {
        while(!Serial1.available() > 0) {
            delay(1);
        }
        byte gpsData = Serial1.read();
        tgps.encode(gpsData);
        Serial.write(gpsData);
        if (tgps.location.isUpdated()){
            Serial.print("Latitude= "); 
            Serial.print(tgps.location.lat(), 6);
            Serial.print(" Longitude= "); 
            Serial.println(tgps.location.lng(), 6);
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

    hdop = tgps.hdop.value();

    return std::pair<double,double>(tgps.location.lat(), tgps.location.lng());
}

int32_t GPSSensor::gethdop()
{
    return hdop;
}

GPSStatus GPSSensor::get_status()
{
    return _status;
}

DateTime GPSSensor::getDateTime()
{
    int i = 1000;
    while (i > 0) {
        while(!Serial1.available() > 0) {
            delay(1);
        }
        byte gpsData = Serial1.read();
        tgps.encode(gpsData);
        Serial.write(gpsData);
        if (tgps.time.isUpdated() && tgps.date.isUpdated()){
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
        Serial.println("GPS: DateTime valid");
    }

    DateTime dt;
    dt.year = tgps.date.year();
    dt.month = tgps.date.month();
    dt.day = tgps.date.day();
    dt.hour = tgps.time.hour() + 2; //GPS time is UTC
    dt.minute = tgps.time.minute();
    dt.second = tgps.time.second();
    dt.centisecond = tgps.time.centisecond();

    return dt;
}


