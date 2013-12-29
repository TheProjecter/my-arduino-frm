//
//  You should declare LOG_LEVEL before include header file.
//  If you need customize module name you should declare LOG_MODULE
//
#define LOG_LEVEL eTRACE
#define LOG_MODULE "TEST"
#include "Logger.h"


void setup()
{
  Serial.begin( 9600 );
  ATTACH_LOGGER_TO_SERIAL();
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
