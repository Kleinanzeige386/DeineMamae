void HC_SR04_Setup()
{
  pinMode(trigPin_v, OUTPUT);
  pinMode(echoPin_v, INPUT);
  pinMode(trigPin_h, OUTPUT);
  pinMode(echoPin_h, INPUT);

  pinMode(out_v, OUTPUT);
  pinMode(out_h, OUTPUT);
}

int getDistance_in_cm(int trigPin, int echoPin)
{
  long duration;
  int distance;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  // Sends US
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}


bool obstacleStatus (int aktuellerAbstand, int kritischerAbstand)
{
  bool warning = false;
  if(aktuellerAbstand<kritischerAbstand)
  {
    warning = true;
  }
  return warning;
}


void HC_SR04_getSensorData()
{
  int abstand_v = getDistance_in_cm(trigPin_v, echoPin_v);
  int abstand_h = getDistance_in_cm(trigPin_h, echoPin_h);
  bool warning_v = obstacleStatus(abstand_v, 15);
  bool warning_h = obstacleStatus(abstand_h, 33); //18cm vehiclesize

  digitalWrite(out_v, warning_v);
  digitalWrite(out_h, warning_h);
  
  Serial.print("vorne:");
  Serial.print(abstand_v);
  Serial.print(" ");
  Serial.print(warning_v);
  Serial.print("   ");
  Serial.print("hinten:");
  Serial.print(abstand_h);
  Serial.print(" ");
  Serial.print(warning_h);
  Serial.print("\n"); 
}