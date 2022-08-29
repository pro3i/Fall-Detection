/*
  Arduino LSM6DS3 - Simple Accelerometer

  This example reads the acceleration values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>
#include <SPI.h>
#include <WiFiNINA.h>



void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }


  Serial.println("X\tY\tZ\tX\tY\tZ");

 
}

void loop() {
  
  float x, y, z, a, b, c;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    
    // The eqaution shows how 4g is obtained 
    // x = data[0] * 4.0 / 32768.0;
    
    //change accelration range 
    //2g *0.5
    //8G *2
    //16G *4
//    x = x * 2;
//    y = y * 2;
//    z = z * 2;

   
  }
  
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(a, b, c);
    //1000dps *0.5
    //500 dps *025
    //250 dps *0.125

    //a = a * 0.5;
    //b = b * 0.5;
    //c = c * 0.5;
    
    
  }

    Serial.print(x);
    Serial.print(',');
    Serial.print(y);
    Serial.print(',');
    Serial.print(z);
    Serial.print(',');
    Serial.print(a);
    Serial.print(',');
    Serial.print(b);
    Serial.print(',');
    Serial.println(c);
 

}
