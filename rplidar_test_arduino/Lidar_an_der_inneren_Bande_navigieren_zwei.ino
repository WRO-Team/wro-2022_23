#define SevPin1 11
#define SevPin2 10
#define SevPWM  7
#define MotPin1 9
#define MotPin2 8
#define MotPWM  6
#define RPLIDAR_MOTOR 3

#include <RPLidar.h>
RPLidar lidar;

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
 int W=0;
 int Winkelunterschied=0;
 int Winkel=0;
 byte Fahrtrichtung =0;
       
void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  Serial.begin(115200);
  Serial1.begin(115200); 
  lidar.begin(Serial1);
  
  /*Wire.begin();
  mpu.begin();
  // mpu.upsideDownMounting = true; 
  mpu.calcOffsets();*/

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(SevPin1, OUTPUT);
  pinMode(SevPin2, OUTPUT);
  pinMode(SevPWM,  OUTPUT);
  pinMode(MotPin1, OUTPUT);
  pinMode(MotPin2, OUTPUT);
  pinMode(MotPWM,  OUTPUT);
  pinMode(4, INPUT_PULLUP);
}

void loop() {
  
  Abstand();
  //Serial.println(a);
  /*mpu.update();// Drehung nach Links +; Drehung nach Rechts -
	//Serial.print("\tZ : ");
	//Serial.println(mpu.getAngleZ());
  Winkel = mpu.getAngleZ();*/
  //if(digitalRead(4) == 1){
    //Fahrtrichtung=3;
  //}
  switch (Fahrtrichtung){
  case 0:
  default:
    if(Fahrtrichtung == 0){
      Antrieb(120, 1, 0);
      if(a > 1000){
      Fahrtrichtung = 1;
      }
      if(b > 1000){
      Fahrtrichtung = 2;
      } 
    }
    break;
  case 1:
  Antrieb(80, 1, 0);
  if(c < 200 && c > 2){
    Antrieb(80, 0, 1);
    rechts(200);
    long q= millis() + 1000;
    while(q > millis()){
      Abstand();
    }
    geradeaus();
  }
  else if(a < 200 && a > 2|| d < 400 && d > 2|| f < 400 && f > 2){
    links(150);
  }
  else  if(a > 300){ //&& W == 0
    rechts(150);
    //Abstand();
    /*mpu.update();
    if((Winkel - 90) >= mpu.getAngleZ()){
      W=1;
    }*/
  }
  else{
    geradeaus();
  }
  //geradeaus();
  //delay(350);
  break;
  case 2:
  Antrieb(80, 1, 0);
  if(c < 200 && c > 2){
    Antrieb(80, 0, 1);
    links(200);
    long q= millis() + 1000;
    while(q > millis()){
      Abstand();
    }
    geradeaus();
  }
  else if(b < 200 && b > 2|| e < 400 && e > 2|| g < 400 && g > 2){
    rechts(150);
  }
  else if(b > 300){ //&& W == 0
    links(150);
    //Abstand();
    /*mpu.update();
    if((Winkel + 90) <= mpu.getAngleZ()){
      W=2;
    }*/
  }
  else{
    geradeaus();
  }
  break;
  case 3:
   /* int Fahrbahnbreite = 150 + a + b;
    int minAbstand = Fahrbahnbreite/2 - 150;
  if(a < minAbstand){
    links(150);
  }
  if(b < minAbstand){
    rechts(150);
  }
  if(a > minAbstand && b > minAbstand){
    geradeaus();
  }
  if(c < 1100){*/
    Antrieb(0,0,0);
  //}
  break;
  }
  //W=0;
}
void links(byte a){
  analogWrite(SevPWM,   a);
  digitalWrite(SevPin1, 0);
  digitalWrite(SevPin2, 1);
}
void rechts(byte b){
  analogWrite(SevPWM,   b);
  digitalWrite(SevPin1, 1);
  digitalWrite(SevPin2, 0);
}
void geradeaus(){
  analogWrite(SevPWM,   0);
  digitalWrite(SevPin1, 0);
  digitalWrite(SevPin2, 0);
}
void Antrieb (byte PWM, bool PINUNO, bool PINDUE){
  analogWrite(MotPWM,   PWM);
  digitalWrite(MotPin1, PINUNO);
  digitalWrite(MotPin2, PINDUE);
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
   Serial.println(c); //messwert 0°
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

