//
//  You should declare LOG_LEVEL before include header file.
//  If you need customize module name you should declare LOG_MODULE
//
#define LOG_LEVEL eTRACE
#define LOG_MODULE "TEST"
#include "Logger.h"


//
// Create a output function for redirect logger to UART
// This works because Serial.write, although of
// type virtual, already exists.
//
static int uart_putchar (char c, FILE *stream)
{
  Serial.write(c) ;
  return 0 ;
}

void setup()
{
  Serial.begin( 9600 );
  fdev_setup_stream( &Logger::FileHandler, uart_putchar, NULL, _FDEV_SETUP_WRITE );
}

void loop()
{
  FATAL( "Internal code of this level is %d",  eFATAL );
  CRITICAL( "Internal code of this level is %d",  eCRITICAL );
  ERROR( "Internal code of this level is %d",  eERROR );
  WARNING( "Internal code of this level is %d",  eWARNING );
  INFO( "Internal code of this level is %d",  eINFO );
  DEBUG( "Internal code of this level is %d",  eDEBUG );
  DEEP( "Internal code of this level is %d",  eDEEP );
  TRACE( "Internal code of this level is %d",  eTRACE );
  
  Serial.println( "" );  Serial.println( "" );
  Logger::SetLogLevel( eWARNING );

  FATAL( "Internal code of this level is %d",  eFATAL );
  CRITICAL( "Internal code of this level is %d",  eCRITICAL );
  ERROR( "Internal code of this level is %d",  eERROR );
  WARNING( "Internal code of this level is %d",  eWARNING );
  INFO( "Internal code of this level is %d",  eINFO );
  DEBUG( "Internal code of this level is %d",  eDEBUG );
  DEEP( "Internal code of this level is %d",  eDEEP );
  TRACE( "Internal code of this level is %d",  eTRACE );
  
  Serial.println( "" );  Serial.println( "" );
  Logger::SetLogLevel( eTRACE );

  delay( 1000 );
}
