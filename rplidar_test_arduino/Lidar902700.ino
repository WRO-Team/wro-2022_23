/*
 * RoboPeak RPLIDAR Arduino Example
 * This example shows the easy and common way to fetch data from an RPLIDAR
 * 
 * You may freely add your application code based on this template
 *
 * USAGE:
 * ---------------------------------
 * 1. Download this sketch code to your Arduino board
 * 2. Connect the RPLIDAR's serial port (RX/TX/GND) to your Arduino board (Pin 0 and Pin1)
 * 3. Connect the RPLIDAR's motor ctrl pin to the Arduino board pin 3 
 */
 
/* 
 * Copyright (c) 2014, RoboPeak 
 * All rights reserved.
 * RoboPeak.com
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
// This sketch code is based on the RPLIDAR driver library provided by RoboPeak
#include <RPLidar.h>

// You need to create an driver instance 
RPLidar lidar;
int messwerte[360]; //Array mit den Messwerten von 0-360 Grad
 float distance;
 int angle;
#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
                        // This pin should connected with the RPLIDAR's MOTOCTRL signal 
long Z;                  
#define SevPin1 11
#define SevPin2 10
#define SevPWM 7
#define MotPin1 9
#define MotPin2 8
#define MotPWM 6

void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  Serial.begin(115200);
  Serial1.begin(115200); 
  lidar.begin(Serial1);
  
  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);

  pinMode(SevPin1, OUTPUT);
  pinMode(SevPin2, OUTPUT);
  pinMode(SevPWM, OUTPUT);
  pinMode(MotPin1, OUTPUT);
  pinMode(MotPin2, OUTPUT);
  pinMode(MotPWM, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    
    //perform data processing here...
    if(distance > 5){
    messwerte[angle] = distance;
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
  Serial.println(messwerte[90]);
  if(messwerte[90] < 300 ){
  analogWrite(SevPWM, 255);
  digitalWrite(SevPin1, 0);
  digitalWrite(SevPin2, 1);    
  }
  else{
  analogWrite(SevPWM, 0);
  digitalWrite(SevPin1, 0);
  digitalWrite(SevPin2, 0);  
  }
  /*
  if(angle > 89 && angle < 91){ 
    Serial.print("dis90° ");
    Serial.println(distance);
    delay(500);
    }
    if(angle > 355 && angle < 360){ 
    Serial.print("  dis0° ");
    Serial.println(distance);
    delay(500);
    }
    if(angle > 269 && angle < 271){ 
    Serial.print("  dis270° ");
    Serial.println(distance);
    delay(500);
    }*/
}
