
int i;


void setup() {
  // put your setup code here, to run once:
  broadcast_Setup();
  Serial.begin(2400);
  GY521_Setup();
  i=0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  broadcast_SM();
  GY521_getSensorData();

}
