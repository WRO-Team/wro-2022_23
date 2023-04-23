#include <Wire.h>
#include <Pixy2.h>
Pixy2 pixy;
unsigned int FL=0;
unsigned int FLR=0;
unsigned int FLG=0;
int x=100;
byte Lenkwertl =0;
byte Lenkwertr =0;
/*pixy.ccc.blocks[i].m_signature //The signature number of the detected object (1-7 for normal signatures)
pixy.ccc.blocks[i].m_x //The x location of the center of the detected object (0 to 316)
pixy.ccc.blocks[i].m_y //The y location of the center of the detected object (0 to 208)
pixy.ccc.blocks[i].m_width //The width of the detected object (1 to 316)
pixy.ccc.blocks[i].m_height //The height of the detected object (1 to 208)
pixy.ccc.blocks[i].m_angle //The angle of the object detected object if the detected object is a color code (-180 to 180).
pixy.ccc.blocks[i].m_index T//he tracking index of the block
pixy.ccc.blocks[i].m_age //The number of frames the block has been tracked.
pixy.ccc.blocks[i].print() // A member function that prints the detected object information to the serial port*/
void setup() {
  Wire.begin(8);  
   Wire.onRequest(requestEvent); // register event      // join i2c bus (address optional for master)
  pixy.init();
  Serial.begin(9600);  // start serial for output
}

void loop() {
  /*Wire.requestFrom(8, 1);    // request 6 bytes from peripheral device #8

  while (Wire.available()) { // peripheral may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }*/
 pixy.ccc.getBlocks();
  //if getblocks > 1 ->  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks){
    for (byte i=0; i<pixy.ccc.numBlocks ; i++){
      FL = pixy.ccc.blocks[i].m_height*pixy.ccc.blocks[i].m_width;
      if(pixy.ccc.blocks[i].m_signature == 2 && FL > 1500 && pixy.ccc.blocks[i].m_x < 155){
      Lenkwertl =255 - pixy.ccc.blocks[i].m_x ;  
      }
      else{
      Lenkwertl =0; 
      }
      if(pixy.ccc.blocks[i].m_signature == 1 && FL > 1500 && pixy.ccc.blocks[i].m_x > 155){//Grünes Objekt
      Lenkwertr = pixy.ccc.blocks[i].m_x -50;
      if(Lenkwertr > 255){
        Lenkwertr = 255;
      }
      }
      else{
      Lenkwertr =0; 
      }
      Serial.print("x: ");
      Serial.println(pixy.ccc.blocks[i].m_x);
      Serial.print("y: ");
      Serial.println(pixy.ccc.blocks[i].m_y);
  //delay(500);
}}}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(Lenkwertr); // respond with message of 6 bytes
  Wire.write(Lenkwertl);
  // as expected by master
}
