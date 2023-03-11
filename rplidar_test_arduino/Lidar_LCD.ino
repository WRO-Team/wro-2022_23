
#define RPLIDAR_MOTOR 3

#include <RPLidar.h>
RPLidar lidar;

#include <Wire.h>
#include <LCD03.h>
LCD03 lcd;

/*#include "Wire.h"
#include <MPU6050_light.h>
MPU6050 mpu(Wire);*/

 int messwerte[360]; //Array mit den Messwerten von 0-360 Grad
 int distance;
 int angle;
 int A=0;
 int a=0;
 int b=0;
 int c=0;
 int d=0;
 int e=0;
 int f=0;
 int g=0;


       
void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  Serial1.begin(115200); 
  lidar.begin(Serial1);
  
  lcd.begin(20, 4);
  lcd.backlight();
  lcd.clear();

  /*Wire.begin();
  mpu.begin();
  // mpu.upsideDownMounting = true; 
  mpu.calcOffsets();*/

}

void loop() {
  lcd.print(a);
  long i= millis() + 1000;
  while(millis() < i){
  Abstand();
}
}
void Abstand(){
  if (IS_OK(lidar.waitPoint())) {
    distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here...
     messwerte[angle] = distance;
  if(A==180){ 
   c = messwerte[A];  
   //Serial.println(c); //messwert 0°
  }
  
  if(A==90){
    a = messwerte[A];
   // Serial.print("  ");
   //Serial.println(a); //messwert 90°
  }
  if(A==270){
    b = messwerte[A];
   // Serial.print("  ");
    //Serial.println(b); //messwert 270°
  }
  if(A==210){  //1
    e = messwerte[A];
   // Serial.print(" e: ");
    //Serial.print(e);
  }
  if(A==150){ //4
    d = messwerte[A];
    //Serial.print(" d: ");
   //Serial.println(d); 
  }
  if(A==240){ //4
    g = messwerte[A];
    //Serial.print(" g: ");
    //Serial.print(g); 
  }
  if(A==120){ //4
    f = messwerte[A];
    //Serial.print(" f: ");
    //Serial.println(f); 
  }
  if(A<330){
    A=A+30;
  }
  else{
    A=0;
  }
  
  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  } 
}
