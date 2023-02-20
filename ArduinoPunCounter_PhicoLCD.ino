/* PunCounter device
 *  This is a library for a device that displays a counter. Every time the button is pressed, it increments the counter and plays a sound.
 *  
 *  Components:
 *  Arcade button (with a 20k resistor to ground)
 *  Small 8 ohm speaker
 *  Arduino Uno
 *  3D printed case
 *  LCD: Phico Datavision LCD-display module model no: DV-16215-1-S2RB.
 */

#include <DV16215.h>
#include "pitches.h"
#include <EEPROM.h>

// Create SoftwareSerial and myLCD with SoftwareSerial connection
SoftwareSerial connection(11, 10, true); // RX, TX, inverted logic
LCD_DV16215 myLCD(&connection);

//Speaker and button
const int SPEAKER = 5;
const int BUTTON = 8;
const int delaytime = 50;

//Sound effect
int melody[] = {NOTE_F3,NOTE_G3};
int noteDurations[] = {16,8};

//EEPROM variables
int EEPROMaddr = 0;
unsigned int alltimecount = 0;
unsigned int currentcount = 0;

void setup() 
{
  Serial.begin(9600,SERIAL_8N1); // debugging if needed
  myLCD.clearAllDisplays();   // Clear everything just in case
  pinMode(BUTTON, INPUT);
  myLCD.clearDisplay();
  //uncomment this and run it once if you need to clear the memory address
  //EEPROM.get(EEPROMaddr, 0);
  EEPROM.get(EEPROMaddr, alltimecount);
  msgDisp1();
  msgDisp2();
}


void loop() 
{
  if(digitalRead(BUTTON) == HIGH){
    currentcount++;
    alltimecount++;
    
    myLCD.clearDisplay();
    msgDisp1();
    delay(4);
    msgDisp2();
    delay(4);
    playMelody();
    EEPROM.put(EEPROMaddr, alltimecount);
  }
}

void msgDisp1()
{
  //myLCD.clearDisplay();
  myLCD.setDisplayTop(0,1);
  myLCD.write("Pun Count:");
  myLCD.setDisplayTop(0,2);
  char cstr[16];
  utoa(currentcount, cstr, 10);
  myLCD.write(cstr);
}

void msgDisp2()
{
  myLCD.setDisplayBottom(0,1);
  myLCD.write("All Time:");
  myLCD.setDisplayBottom(0,2);
  char cstr[16];
  utoa(alltimecount, cstr, 10);
  myLCD.write(cstr);
}

void playMelody(){
  for (int thisNote = 0; thisNote < 2; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them. the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(SPEAKER);
  }
}
