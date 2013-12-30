/*
	InterruptsExternalExtender.h - Macros library for Simple Arduino Framework
	Copyright (c) 2013 Gregory Linschitz.  All right reserved.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the MIT License.

	The MIT License (MIT)

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.


	Changelog:

		2013-12-28	Initial version

*/

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
