#include <Wire.h> // Wire Bibliothek einbinden
#include <LiquidCrystal_I2C.h> // Vorher hinzugefügte LiquidCrystal_I2C Bibliothek einbinden
LiquidCrystal_I2C lcd(0x27, 16, 2); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)" 
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
#define processorOut 7
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int orangeLine = 0;
int blaueLine = 0;
void setup() 
{
lcd.init(); //Im Setup wird der LCD gestartet 
lcd.backlight(); //Hintergrundbeleuchtung einschalten (lcd.noBacklight(); schaltet die Beleuchtung aus). 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(processorOut, OUTPUT);
  digitalWrite(processorOut, LOW);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);
}

void loop() 
{ 
  digitalWrite(processorOut, LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  if (redFrequency < 30 && greenFrequency < 30 && blueFrequency < 30) {
    lcd.clear();
    lcd.print("Weiss");
  }
  else if (redFrequency < blueFrequency) {
    lcd.clear();
    lcd.print("Rot");
    orangeLine = orangeLine + 1;
    lcd.setCursor(0, 1);
    lcd.print(orangeLine);
    delay(200);
  }

  else if (blueFrequency < redFrequency) {
    lcd.clear();
    lcd.print("Blau");
    blaueLine = blaueLine + 1;
    lcd.setCursor(8, 1);
    lcd.print(blaueLine);
    delay(200);
  }
      lcd.setCursor(0, 1);
    lcd.print("OLine:");
  lcd.setCursor(6, 1);
    lcd.print(orangeLine);
  lcd.setCursor(8, 1);
    lcd.print("BLine:");
  lcd.setCursor(14, 1);
    lcd.print(blaueLine);
if (orangeLine >= 12 && blaueLine >= 12) {
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("STOP in ");
      lcd.setCursor(8, 1);
      lcd.print("5");
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("4");
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("3");
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("2");
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("1");
      delay(1000);
      digitalWrite(processorOut, HIGH);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("######STOP#######");
      delay(10000);
} 
}
