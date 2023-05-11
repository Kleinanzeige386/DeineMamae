#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
struct direction
{
  bool right;
  bool left;
  bool front;
  bool back;
};

void GY521_Setup()
{
   while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Wire.begin(9, 8);
  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (1)
    {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
}

void GY521_getSensorData()
{
  direction mydirection;
  sensors_event_t a, g, temp; 
  mpu.getEvent(&a, &g, &temp);
 
  if(a.acceleration.x>=0)
  {
    mydirection.right = true;
    mydirection.left = false;

  }
  if(a.acceleration.x <0 )
  {
    mydirection.left = true; 
    mydirection.right = false;
    
  }
  if(a.acceleration.y >= 0)
  {
    mydirection.front = true; 
    mydirection.back = false;
    
  }
   if(a.acceleration.y < 0)
  {
    mydirection.front = false; 
    mydirection.back = true;
    
  }
   /* Print out the values for debugging */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
 
  Serial.println("");

  delay(10);
}