#define SevPin1 11
#define SevPin2 10
#define SevPWM  7
#define MotPin1 9
#define MotPin2 8
#define MotPWM  6
// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>

// You need to create an driver instance 
RPLidar lidar;
 int messwerte[360]; //Array mit den Messwerten von 0-360 Grad
 int distance;
 int angle;
 int A=0;
 int a=0;
 int b=0;
 int c=0;
 byte Fahrtrichtung =0;
 
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal                  

void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  Serial.begin(115200);
  Serial1.begin(115200); 
  lidar.begin(Serial1);
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(SevPin1, OUTPUT);
  pinMode(SevPin2, OUTPUT);
  pinMode(SevPWM,  OUTPUT);
  pinMode(MotPin1, OUTPUT);
  pinMode(MotPin2, OUTPUT);
  pinMode(MotPWM,  OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here...
     messwerte[angle] = distance;
  if(A==0){ 
    c = messwerte[A];  
    Serial.print(c); //messwert 0°
  }
  
  if(A==90){
    a = messwerte[A];
    Serial.print("  ");
    Serial.print(a); //messwert 90°
  }
  if(A==270){
    b = messwerte[A];
    Serial.print("  ");
    Serial.println(b); //messwert 270°
  }
  if(A<270){
    A=A+90;
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
  Antrieb(120, 1, 0);
  if(a > 400){
    rechts(200);
  }
  else if(b < 250){
    links(150);
  }
  else{
    geradeaus();
  }
  break;
  case 2:
  Antrieb(120, 1, 0);
  if(b > 400){
    links(200);
  }
  else if(a < 250){
    rechts(150);
  }
  else{
    geradeaus();
  }
  break;
  }
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

