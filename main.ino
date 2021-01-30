//The main code to run the Pun Counter
/*Hardware:
-Arduino Uno
-Arcade button
-LCD Panel
-
*/

#include <EEPROM.h>
int addr = 0; //EEPROM address


void setup(){
  
  
}


void loop(){
  
  
  
}


void incrementCounter(){
  EEPROM.write(addr, val);
  addr = addr + 1;
  if (addr == EEPROM.length()) {
    addr = 0;
  }
}
