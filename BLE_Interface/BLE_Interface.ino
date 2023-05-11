//ultrasonic sensor front
#define trigPin_v  4
#define echoPin_v  5

//ultrasonic sensor back
#define trigPin_h 6
#define echoPin_h 7

//output pin for group "Driving"
#define out_v   18
#define out_h 19

void setup() {
  // put your setup code here, to run once:
  broadcast_Setup();
  GY521_Setup();
  HC_SR04_Setup();
  Serial.begin(2400);
}

void loop() {
  // put your main code here, to run repeatedly:
  broadcast_SM();
  GY521_getSensorData();
  delay(5);
  HC_SR04_getSensorData();
}
