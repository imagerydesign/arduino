#include <EEPROM.h>

void setup()
{
  for ( int i = 0 ; i < EEPROM.length() ; i++ )
    EEPROM.write(i, 0);
  digitalWrite(13, HIGH);// turn the LED on when we're done
}

void loop()
{
  
}


