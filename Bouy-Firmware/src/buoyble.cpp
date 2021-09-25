#include <buoyble.h>
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "686fc1ae-b815-48a4-9b26-300eaefd2b03"
#define CHARACTERISTIC_UUID "77fc5631-ab53-44fb-a5c0-753b08423814"

class BuoyBLEServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pserver) {
      Serial.println("BLE Device connected");
  }

  void onDisconnect(BLEServer* pserver) {
    Serial.println("BLE Device disconnected");
    pserver->getAdvertising()->start();
    Serial.println("BLE advertising restarted");
  }
};

void BuoyBLE::init()
{
  Serial.println("Starting BLE Server!");

  BLEDevice::init("Buoy-BLE-Server");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BuoyBLEServerCallbacks());
  pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );


  pCharacteristic->setValue("OFF");
  pService->start();
  //BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  //pAdvertising->start();
  Serial.println("Characteristic defined: OFF, adverising started");
}

std::string BuoyBLE::getValue()
{
  Serial.printf("BLE CharVal retrieved: %s\n", pCharacteristic->getValue().c_str());
    return pCharacteristic->getValue();

}

bool BuoyBLE::getValue_bool()
{
  return pCharacteristic->getValue() == "ON";
}

void BuoyBLE::setValueOn()
{
  pCharacteristic->setValue("ON");
}

void BuoyBLE::setValueOff()
{
  pCharacteristic->setValue("OFF");
}

void BuoyBLE::setValue(std::string value)
{
  pCharacteristic->setValue(value);
}
