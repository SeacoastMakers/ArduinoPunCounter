/* PhicoDisplayModule Library-example
 *  This library provides wrapper functions in order to control
 *  Phico Datavision LCD-display module model no: DV-16215-1-S2RB.
 *  
 *  Functions underneath the hood uses SoftwareSerial library 
 *  on given pins. Please note that!
 *  
 *  Arduino board used here was Arduino Uno R3. Although any board should work, 
 *  since activity is based on SoftwareSerial-library.
 *  
 *  You have to remove solderbridge S3 and add solderbridge S2 in order
 *  to get this display to work with 9600 baud and inverted logic.
 *  
 */

#include <DV16215.h>
//#include String

// Create SoftwareSerial
SoftwareSerial connection(11, 10, true); // RX, TX, inverted logic

// Create myLCD with SoftwareSerial connection
LCD_DV16215 myLCD(&connection);

const int SPEAKER = 6;
const int BUTTON = 8;
const int delaytime = 50;
int currentcount= 0;
char countline[16];

void setup() 
{
  Serial.begin(9600,SERIAL_8N1); // debugging if needed
  myLCD.clearAllDisplays();   // Clear everything just in case
  pinMode(BUTTON, INPUT);
  myLCD.clearDisplay();
  msgDisp1();
}

void loop() 
{
  if(digitalRead(BUTTON) == HIGH){
    currentcount++;
    myLCD.clearDisplay();
    msgDisp1();
    delay(200);
  }
}

void msgDisp1()
{
  //myLCD.clearDisplay();
  myLCD.setDisplayTop(0,1);
  myLCD.write("Pun Count:");
  myLCD.setDisplayTop(0,2);
  char cstr[16];
  itoa(currentcount, cstr, 10);
  myLCD.write(cstr);
}

void msgDisp2()
{
  myLCD.setDisplayBottom(0,1);
  myLCD.write("_____________");
  myLCD.setDisplayBottom(0,2);
  myLCD.write("_____________");
  delay(2000);
}
