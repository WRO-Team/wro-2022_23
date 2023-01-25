#include <RPLidar.h>
#include <RPLidar.h>

// You need to create an driver instance
RPLidar lidar;

#define RPLIDAR_MOTOR 3 // The PWM pin for control the speed of RPLIDAR's motor.
// This pin should connected with the RPLIDAR's MOTOCTRL signal

int messwerte[360]; //Array mit den Messwerten von 0-360 Grad
int index; //Indexnummer des Arrays 'messwerte'
int max; //Maximum der Messwerte
int min; //Minimum der Messwerte
int angle; //Winkelangabe in Grad der Messwerte
int distance; //Distanz


//Funktion, um Array 'messwerte' zu füllen//
int fillmesswerte() {
  angle = lidar.getCurrentPoint().angle;
  for (index = 0; index < 360; index++) {
    if (angle == index) {
      messwerte[index] = lidar.getCurrentPoint().distance;
    }

  }
}

//Funktion, um Maximum der Messwerte zu ermitteln//
int findmax () {
  max = messwerte[0];
  int pos;
  int index = 0;
  for (index; index < 360; index++) {
    if (max < messwerte[index]) {
      max = messwerte[index];
      pos = index;
    }

  }
  
 /* Serial.print("Maximum: ");
  Serial.print(max);
  Serial.print(" bei ");
  Serial.print(pos);
  Serial.println(" Grad");
  Serial.println("*************************************************************");*/
  
}

//Funktion, um Minimum der Messwerte zu ermitteln//

int findmin() {
  min = messwerte[0];
  int pos;
  int index = 0;
  for (index; index < 360; index++) {
    if (min > messwerte[index]) {
      min = messwerte[index];
      pos = index;
    }



  }
  /*Serial.print("Minimum: ");
  Serial.print(min);
  Serial.print(" bei ");
  Serial.print(pos);
  Serial.println(" Grad");
  Serial.println("*************************************************************");*/
}

//Funktion, um Messwerte auszugeben//

void printmesswerte() {
  for (index = 0; index < 360; index++) {
    Serial.println(index);
    Serial.println(messwerte[index]);
    Serial.println();
  }

}




void setup() {
  // bind the RPLIDAR driver to the arduino hardware serial
  lidar.begin(Serial1);
  Serial.begin(9600);

  // set pin modes
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}


void loop() {

  if (IS_OK(lidar.waitPoint())) {
    //perform data processing here...
    fillmesswerte();
    if (lidar.getCurrentPoint().startBit) {
      // a new scan, display the previous data...
      printmesswerte();
      findmax();
      findmin();
    }

  } else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor

    // try to detect RPLIDAR...
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
      //detected...
      lidar.startScan();
      analogWrite(RPLIDAR_MOTOR, 200);
      delay(1000);
    }
  }
}
