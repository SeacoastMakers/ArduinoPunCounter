/*
PunCounter - a simple device to incenivize telling puns. 
Displays a count on the screen. Every time the button is pressed, a sound plays and the count is updated.
Great if you're a real button-pusher!
Written by Alex Nunn 2023 March 6th

Hardware:
Arduino 2x16 LCD 1602A
Arcade button
2k ohm pulldown resistor between button pin and ground
Speaker

*/

#include <LiquidCrystal.h>
#include <EEPROM.h>

const int BUTTON = A1;
const int SPEAKER = A2;

//1602A LCD pins
const int pin_BL = 10; 
const int pin_EN = 9; 
const int pin_RS = 8; 
const int pin_d7 = 7; 
const int pin_d6 = 6; 
const int pin_d5 = 5; 
const int pin_d4 = 4; 

//Create lcd object
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

//EEPROM address for storing the count
int EEPROMaddr = 0;

//Variable for managing the count while powered on
unsigned int currentcount= 0;

//Startup music
int melody1[]={
  659,784,880
};

int noteDurations1[] = {
  8, 16, 4
};

//Button sound effect
int melody2[] = {
  784, 587, 392
};
int noteDurations2[] = {
  8, 16, 8
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(BUTTON, INPUT);
  
  lcd.begin(16, 2);

  //Display a startup screen
  lcd.setCursor(0,0);
  lcd.print("Hello, Jokester");
  lcd.setCursor(0,1);
  lcd.print("LOLOLOLOLOL");
  
  //EEPROM.put(EEPROMaddr, 0); //To reset to 0 or clear any random data, run this one time. Recomment when done.

  
  EEPROM.get(EEPROMaddr, currentcount); //Load count from EEPROM
  delay(100); //Wait to avoid issues with EEPROM
  writeDisplayMain(); //Display main screen
  playTone(melody1,noteDurations1, 3); //Play startup music
}

//Main loop. When the button is pressed, the count is incremented by one and written to the EEPROM,
//the numerical part of the screen is updated to show the new count, and a sound plays
void loop() {
 if(digitalRead(BUTTON) == HIGH){
    currentcount++;
    EEPROM.put(EEPROMaddr, currentcount);
    writeDisplayCount();
    playTone(melody2,noteDurations2, 3);
    delay(150);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Main display screen
void writeDisplayMain()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write("Pun Count:");
  lcd.setCursor(0,1);
  char cstr[16];
  itoa(currentcount, cstr, 10);
  lcd.write(cstr);
}

//Update the section of the screen with the count
void writeDisplayCount()
{
  lcd.setCursor(0,1);
  char cstr[16];
  itoa(currentcount, cstr, 10);
  lcd.write(cstr);
}

//Plays melodies saved in an integer array format
void playTone(int melody[], int noteDurations[], int melodyLength)
{
  //Display LOL in the bottom right corner of the screen
  lcd.setCursor(13,1);
  lcd.write("LOL");
  
  for (int thisNote = 0; thisNote < melodyLength; thisNote++) {
    // note duration = one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER, melody[thisNote], noteDuration);

    // minimum time between notes. note's duration + 30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(SPEAKER);
  }

  //Clear the LOL from the corner of the screen
  lcd.setCursor(13,1);
  lcd.write("   ");
}
