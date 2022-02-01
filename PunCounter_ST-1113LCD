/*
Arduino 2x16 LCD 1602A
Arcade button
Speaker
PunCounter - a simple button-press counter that stores the value inbetween power cycles
Written by Alex Nunn
*/

#include <LiquidCrystal.h>
#include <EEPROM.h>

//LCD pin to Arduino
const int pin_BL = 10; 
const int pin_EN = 9; 
const int pin_RS = 8; 
const int pin_d7 = 7; 
const int pin_d6 = 6; 
const int pin_d5 = 5; 
const int pin_d4 = 4; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

//Address for EEPROM storage
int EEPROMaddr = 0;

//Pin info for button
const int BUTTON = A1;

//Speaker and sound settings
const int SPEAKER = 3;
//Notes to play. Obtained from toneMelody example file.
int melody[] = {
  784, 587, 392
};
int noteDurations[] = {
  16, 16, 16
};


const int delaytime = 50;
unsigned int currentcount= 0;
char countline[16];


void setup() {
  pinMode(BUTTON, INPUT);

  //EEPROM.put(EEPROMaddr, 0); //To reset to 0 or clear any random data, run this one time. Recomment when done.
  EEPROM.get(EEPROMaddr, currentcount);
  
  lcd.begin(16, 2);

  lcd.setCursor(0,0);

  lcd.print("Hello, Jokester");
  lcd.setCursor(0,1);
  lcd.print("LOLOLOLOLOL");
  delay(1000);
  msgDisp1();
}

void loop() {
 if(digitalRead(BUTTON) == HIGH){
    currentcount++;
    EEPROM.put(EEPROMaddr, currentcount);
    msgDisp1();
    playTone();
    delay(200);
  }
}

void msgDisp1()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Pun Count:");
  lcd.setCursor(0,1);
  char cstr[16];
  itoa(currentcount, cstr, 10);
  lcd.write(cstr);
}

void playTone()
{
  for (int thisNote = 0; thisNote < 3; thisNote++) {
    // note duration = one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER, melody[thisNote], noteDuration);

    // minimum time between notes. note's duration + 30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER);
  }
}
