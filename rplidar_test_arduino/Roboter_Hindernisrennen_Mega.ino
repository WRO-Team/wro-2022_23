
#include <RPLidar.h>
RPLidar lidar;
 int messwerte[360]; //Array mit den Messwerten von 0-360 Grad
 int distance;
 int angle;
 int A=0;
 int B=0;
 int a=0;
 int b=0;
 int c=0;
 int e=0;
 int d=0;
 int f=0;
 int g=0;
 int llenken=0;
 int rlenken=0;
 byte Lenkwertl;
 byte Lenkwertr;
 byte Fahrtrichtung;
 #define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal                  
// Include Arduino Wire library for I2C
#include <Wire.h>
 
// Define Slave I2C Address
#define SLAVE_ADDR 9
 
// Define Slave answer size
#define ANSWERSIZE 6
#define SevPin1 11
#define SevPin2 10
#define SevPWM  7 //6 Arduino mega
#define MotPin1 9
#define MotPin2 8
#define MotPWM  6
#define RPLIDAR_MOTOR 3

void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  Serial.begin(115200);
  Serial1.begin(115200); 
  lidar.begin(Serial1);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  Wire.begin();

  Serial.println("I2C Master Demonstration");
   pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(SevPin1, OUTPUT);
  pinMode(SevPin2, OUTPUT);
  pinMode(SevPWM,  OUTPUT);
  pinMode(MotPin1, OUTPUT);
  pinMode(MotPin2, OUTPUT);
  pinMode(MotPWM,  OUTPUT);
}

void loop() {
Abstand();
  if(Lenkwertl > 0){
    Fahrtrichtung=2;//rot
  }
  if(Lenkwertr >  0){
    Fahrtrichtung=1;//grün
  }
  switch (Fahrtrichtung){
  case 0:
  default: //Fahrtrichtung ermitteln -- orientierung an der äuseren bande
   Antrieb(100, 1, 0);
    //rlenken=((a+e)/4)-((b+d)/4);
   // llenken=((b+d)/4)-((a+e)/4);
    rlenken=((a/2)-(b/2));
    llenken=((b/2)-(a/2));
    if(llenken > 150){
      llenken = 150;
    }
    if(rlenken > 150){
      rlenken = 150;
    }
    /*if(llenken < 0){
      llenken = 0;

    }if(rlenken < 0){
      rlenken = 0;
    }*/
    /*if(e < 300 && e > 2|| g < 300 && g > 2){  //abstand nach links zu klein
    rechts(150);
    }
    else if(d < 300 && d > 2|| f < 300 && f > 2){  //abstand nach rechts zu klein
    links(150);
    }
    else*/ if(llenken > 40){
      links(llenken);
    }
    else if(rlenken > 40){
      rechts(rlenken);
    }
    else{
      geradeaus();
    }
    break;
    case 1: //Rot
    if(a < 200 && a > 2 || d < 200 && d > 2|| f < 200 && f > 2){
      geradeaus();
    }
    else{
      rechts(Lenkwertr);
    }
    break;
    case 2: //Grün
    if(a < 200 && a > 2 || e < 200 && e > 2|| g < 200 && g > 2){
      geradeaus();
    }
    else{
      links(Lenkwertl);
    }
    break;}

  Wire.requestFrom(8, 2);    // request 2 bytes from peripheral device #8
  while (Wire.available()) { // peripheral may send less than requested
     byte Lenkwertl = Wire.read(); // receive a byte as character
     byte Lenkwertr = Wire.read();
     //Lenkwertl = l; 
    //Lenkwertr = r;
    Serial.println(); 
    Abstand();        
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
  if(A==100){  //1
    e = messwerte[A];
   // Serial.print(" e: ");
    //Serial.print(e);
  }
  if(A==260){ //4
    d = messwerte[A];
    //Serial.print(" d: ");
   //Serial.println(d); 
  }
  if(A==120){ //4
    g = messwerte[A];
    //Serial.print(" g: ");
    //Serial.print(g); 
  }
  if(A==240){ //4
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
