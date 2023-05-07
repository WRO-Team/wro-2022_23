#include <Pixy2.h>
Pixy2 pixy;
unsigned int FL=0;
unsigned int FLR=0;
unsigned int FLG=0;
int x=100;
float zwischenrechnung;
byte Lenkwertl ;//=240;
byte Lenkwertr ;//=0;
/* 
pixy.ccc.blocks[i].m_signature //The signature number of the detected object (1-7 for normal signatures)
pixy.ccc.blocks[i].m_x //The x location of the center of the detected object (0 to 316)
pixy.ccc.blocks[i].m_y //The y location of the center of the detected object (0 to 208)
pixy.ccc.blocks[i].m_width //The width of the detected object (1 to 316)
pixy.ccc.blocks[i].m_height //The height of the detected object (1 to 208)
pixy.ccc.blocks[i].m_angle //The angle of the object detected object if the detected object is a color code (-180 to 180).
pixy.ccc.blocks[i].m_index T//he tracking index of the block
pixy.ccc.blocks[i].m_age //The number of frames the block has been tracked.
pixy.ccc.blocks[i].print() // A member function that prints the detected object information to the serial port*/

void setup(){
  pinMode(5, OUTPUT);//grün
  pinMode(6, OUTPUT);//grün
  pinMode(7, OUTPUT);//rot
  pinMode(8, OUTPUT);//rot
  pixy.init();
  Serial.begin(9600);  // start serial for output
}

void loop() {
  // Entscheidung auf 0 setzen
  //Lenkwertr = 0;
  //Lenkwertl = 0;  

 pixy.ccc.getBlocks();
 
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks){
   
    for (byte i=0; i<pixy.ccc.numBlocks ; i++){
      FL = pixy.ccc.blocks[i].m_height*pixy.ccc.blocks[i].m_width;
      //  rot m_signature == 1 und Objekt FL größer 1000 pixel und Objekt befindet sich im rechten teil 140/315 = 40%
      if(pixy.ccc.blocks[i].m_signature == 1 && FL > 1000 && pixy.ccc.blocks[i].m_x > 100){
      Lenkwertr = 255 * (pixy.ccc.blocks[i].m_x/315.0); 
      //Lenkwertl =0; 
      }
      else{
      //Lenkwertl =0;
      //Lenkwertr =0; 
      }
      // grün m_signature == 2 und Objekt FL größer 1000 pixel und Objekt befindet sich im rechten teil 174/315 = 55%
      if(pixy.ccc.blocks[i].m_signature == 2 && FL > 1000 && pixy.ccc.blocks[i].m_x < 200){
      Lenkwertl = 255 * (315.0-pixy.ccc.blocks[i].m_x)/315.0;
      //Lenkwertr =0;
      }
      else{
      //Lenkwertr =0;
      //Lenkwertl =0; 
      }
      Serial.print("Objektgröße: ");
      Serial.println(FL);
      Serial.print("Farbe: ");
      Serial.println(pixy.ccc.blocks[i].m_signature);
      Serial.print("Objektposition: ");
      Serial.println(pixy.ccc.blocks[i].m_x);
      }}
      else{
         Lenkwertl=0;
         Lenkwertr=0;
      }
      if(Lenkwertl > 210){
        digitalWrite(6, 1);
        digitalWrite(5, 1);
      }
      else if(Lenkwertl > 160){
        digitalWrite(6, 1);
        digitalWrite(5, 0);
      }
      else if(Lenkwertl > 100){
        digitalWrite(6, 0);
        digitalWrite(5, 1);
      }
      else{
       digitalWrite(6, 0);
       digitalWrite(5, 0); 
      }

      if(Lenkwertr > 210){
        digitalWrite(8, 1);
        digitalWrite(7, 1);
      }
      else if(Lenkwertr > 160){
        digitalWrite(8, 1);
        digitalWrite(7, 0);
      }
      else if(Lenkwertr > 100){
        digitalWrite(8, 0);
        digitalWrite(7, 1);
        
      }
      else{
       digitalWrite(8, 0);
       digitalWrite(7, 0); 
      }
     
    
    
    

}



