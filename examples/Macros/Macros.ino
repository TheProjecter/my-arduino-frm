#include "Macros.h"

#define ledPin 13

void setup()
{
  Serial.begin( 9600 );
  pinMode( ledPin, OUTPUT );
}

void loop()
{
  DO_EVERY_MICRO( 25000, digitalWrite( ledPin, !digitalRead( ledPin ) ) );
  
  DO_EVERY( 1000, 
    Serial.print( "Action every 1000 ms. Readed = " );
    Serial.println( digitalRead( ledPin ) ) 
  );
  
  DO_EVERY( 5000, 
    Serial.print( "Action every 5000 ms. Readed  = " );
    Serial.println( digitalRead( ledPin ) ) 
  );
}
