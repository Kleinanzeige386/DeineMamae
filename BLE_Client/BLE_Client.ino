#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>

// Replace with the UUID of the Service and Characteristic you want to connect to
#define SERVICE_UUID           "87d3e047-840a-4db5-8427-74085e62c4fa"
#define CHARACTERISTIC_UUID    "2130eca3-8769-4b9a-8873-709c6a0d8997"

BLEClient*  pClient = NULL;
BLERemoteCharacteristic* pRemoteCharacteristic = NULL;

int i=0;

bool connectToServer() {
  BLEDevice::init("Controller");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  BLEScanResults scanResults = pBLEScan->start(5);
  BLEAddress* pServerAddress = NULL;

  for (int i = 0; i < scanResults.getCount(); i++) {
    BLEAdvertisedDevice advertisedDevice = scanResults.getDevice(i);
    BLEUUID advertised_ServiceUUID = advertisedDevice.getServiceUUID();
    if (advertised_ServiceUUID.equals((BLEUUID) SERVICE_UUID)) {
      pServerAddress = new BLEAddress(advertisedDevice.getAddress());
      break;
    }
  }

  if (pServerAddress == NULL) {
    Serial.println("ERROR 404: No Matching Service UUID found");
    return false;
  }

  pClient  = BLEDevice::createClient();
  pClient->connect(*pServerAddress);
  
  if (!pClient->isConnected()) {
    Serial.println("ERROR 001: Couldn't connect to Client");
    return false;
  }

  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == NULL) {
    Serial.println("ERROR 002: Couldn't connect to service");
    return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteCharacteristic == NULL) {
    Serial.println("ERROR 003: Couldn't acces Characteristic");
    return false;
  }

  Serial.println("Server connection established sucessfully");
  return true;
}

void writeCharacteristic(uint8_t value) {
  pRemoteCharacteristic->writeValue(&value, 1);
}

void setup() {
  Serial.begin(115200);
  Serial.println("===========================================im fucking restarting");
  delay(1000);

  while(!connectToServer()){}
  writeCharacteristic(i); // replace with the value you want to write
}

void loop() {
  writeCharacteristic(i);
  Serial.println(i++);
}