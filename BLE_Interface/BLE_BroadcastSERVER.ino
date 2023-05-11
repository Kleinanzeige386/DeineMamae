#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define potPin 34
#define SERVICE_UUID "87d3e047-840a-4db5-8427-74085e62c4fa"
#define APP_CHARACTERISTIC_UUID "c488982d-59bc-4cdc-a991-76c004c1b279"
#define SENSOR_CHARACTERISTIC_UUID "2130eca3-8769-4b9a-8873-709c6a0d8997"
#define DEVICE_NAME "On Board"

using namespace std;

std::string message;
std::string speed_horizontal;
std::string speed_vertical;
BLEServer *pServer = NULL;
boolean deviceConnected;

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  };
};

BLECharacteristic *pApp_Characteristic;
BLECharacteristic *pSensor_Characteristic;

void broadcast_Setup()
{
  message = "";
  speed_horizontal ="";
  speed_vertical = "";
  Serial.begin(115200);
  BLEDevice::init(DEVICE_NAME);

  // server one
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // service one
  BLEService *pAppService = pServer->createService(SERVICE_UUID);
  pApp_Characteristic = pAppService->createCharacteristic(
      APP_CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_NOTIFY);

  pApp_Characteristic->addDescriptor(new BLE2902());
  pAppService->start();

  // service two
  BLEService *pSensorService = pServer->createService(SERVICE_UUID);
  pSensor_Characteristic = pSensorService->createCharacteristic(
                      BLEUUID(SENSOR_CHARACTERISTIC_UUID),
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pSensor_Characteristic->setCallbacks(new BLECharacteristicCallbacks());

  pSensorService->start();
}

void broadcast_SM()
{
  message = "["+speed_horizontal + ","+ speed_vertical + "]";
  if (!deviceConnected)
  {
    pServer->getAdvertising()->start();
  }

  if (deviceConnected)
  {
    pApp_Characteristic->setValue(message);
    pApp_Characteristic->notify();
  }
  delay(500);
}

void broadcast_setMessage(std::string inMessage){
  message = inMessage;
}

void set_horizontal_acc(std::string x){
  speed_horizontal = x;
}

void set_vertical_acc(std::string x){
  speed_vertical = x;
}