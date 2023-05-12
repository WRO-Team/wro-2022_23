
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
 byte l=0;
 byte r=0;
 long y;
 //byte Lenkwertl;
 //byte Lenkwertr;
 byte Fahrtrichtung;
 #define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal                  
#define SevPin1 11
#define SevPin2 10
#define SevPWM  7 
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
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(SevPin1, OUTPUT);
  pinMode(SevPin2, OUTPUT);
  pinMode(SevPWM,  OUTPUT);
  pinMode(MotPin1, OUTPUT);
  pinMode(MotPin2, OUTPUT);
  pinMode(MotPWM,  OUTPUT);
  pinMode(30, INPUT_PULLUP);//Linienerkennung
  pinMode(22, INPUT_PULLUP);//grün
  pinMode(24, INPUT_PULLUP);//grün
  pinMode(26, INPUT_PULLUP);//rot
  pinMode(28, INPUT_PULLUP);//rot
}

void loop() {
Abstand();//Lidar misst Abstand
    /*Serial.print(l);
    Serial.print(" ");
    Serial.println(r);
    Serial.print(" ");
    Serial.print(Fahrtrichtung);*/
  if(digitalRead(30) == 1){//Signal von Arduino Nano mit Farbsensor wenn 3. Runde vollendet
    Fahrtrichtung=3;
  }
  HindernisG();// Werte von Pixy-Kamera entfangen
  HindernisR();
  if(r==0 && l==0){
    Fahrtrichtung =0;
  }
  if(c < 250 && c > 2){ //abstand nach vorn zu klein 
    Antrieb(80, 0, 1);
    if(a>b){
      links(200);
    }
    if(b>a){
      rechts(200);
    }
            //rückwärts fahren und einlenken
    long q= millis() + 1000;
    while(q > millis()){
      Abstand();
    }
    geradeaus();
    }
    else{
  switch (Fahrtrichtung){
  case 0:
  default: //Normalbetrieb
   Antrieb(100, 1, 0);
    //rlenken=((a+e)/4)-((b+d)/4);
    //llenken=((b+d)/4)-((a+e)/4);
    rlenken=((a/2)-(b/2));//Lenkeinschlag nach rechts, Abstandswert von links durch zwei minus Abstandswert von rechts durch zwei
    llenken=((b/2)-(a/2));////Lenkeinschlag nach links, Abstandswert von rechts durch zwei minus Abstandswert von links durch zwei
    if(llenken > 150){
      llenken = 150;
    }
    if(rlenken > 150){
      rlenken = 150;
    }
    if(llenken < 0){
      llenken = 0;
    }
    if(rlenken < 0){
      rlenken = 0;
    }
    if(e < 400 && e > 2|| g < 400 && g > 2){  //abstand nach links zu klein
    links(150);
    }
    else if(d < 400 && d > 2|| f < 400 && f > 2){  //abstand nach rechts zu klein
    rechts(150);
    }
    else if(llenken > 40){
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
    y=millis()+1000;
    while(y > millis()){
    /*if(a < 210 && a > 2 || e < 270 && e > 2|| g < 270 && g > 2){
        geradeaus();
    }
    else{*/
      rechts(r);
    //}
    Abstand();
    }
    break;
    case 2: //Grün
    y=millis()+1000;
    while(y > millis()){
    /*if(b < 210 && b > 2 || d < 270 && d > 2|| f < 270 && f > 2){
      geradeaus();
    }
    else{*/
      links(l);
    //}
    Abstand();
    }
    break;
    case 3:
    Antrieb(0,0,0);
    break;
    }
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
void HindernisG(){
  if(digitalRead(22)==1 && digitalRead(24)==1){
    Fahrtrichtung=2;//grün
    l=255;  }
  else if(digitalRead(22)==1){
    Fahrtrichtung=2;//grün
    l=130;
  }
  else if(digitalRead(24)==1){
    Fahrtrichtung=2;//grün
    l=180;
  }
  else{
    l=0;
    //Fahrtrichtung=0;
  }
}
void HindernisR(){
  if(digitalRead(26)==1 && digitalRead(28)==1){
    Fahrtrichtung=1;//grün
    r=255;
  }
  else if(digitalRead(26)==1){
    Fahrtrichtung=1;//grün
    r=130;
  }
  else if(digitalRead(28)==1){
    Fahrtrichtung=1;//grün
    r=180;
  }
  else{
    r=0;
    //Fahrtrichtung=0;
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
   //Serial.print("  ");
   //Serial.println(a); //messwert 90°
  }
  if(A==270){
    b = messwerte[A];
   //Serial.print("  ");
   //Serial.println(b); //messwert 270°
  }
  if(A==105){  //1
    e = messwerte[A];
   // Serial.print(" e: ");
    //Serial.print(e);
  }
  if(A==255){ //4
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
    A=A+15;
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

