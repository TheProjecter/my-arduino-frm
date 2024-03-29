#pragma once

/*
	Logger.h - Logger library for Simple Arduino Framework
	Copyright (c) 2013 Gregory Linschitz. All right reserved.

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

		2014-01-08	Adedd INIT_SERIAL_AND_ATTACH_LOGGER & LOG_EMPTY_LINE
		2014-01-01	Added Binnary format defines 
		2013-12-26	Added Serial attach mechanism
		2013-11-06	Initial version

*/


#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif


namespace Logger
{
	//
	// Logger levels section
	//
	#define eOFF		0x00
	#define eEMPTY		0x01
	#define eFATAL		0x02
	#define eCRITICAL	0x03
	#define eERROR		0x04
	#define eWARNING	0x05
	#define eINFO		0x06
	#define eDEBUG		0x07
	#define eDEEP		0x08
	#define eTRACE		0x09

	//
	// Helpers
	//
	#define BYTE_TO_BIN_FMT			"%d%d%d%d%d%d%d%d"
	#define BYTE_TO_BIN( n )		!!( (n) & 0x80 ), !!( (n) & 0x40 ), !!( (n) & 0x20 ), !!( (n) & 0x10 ), \
									!!( (n) & 0x08 ), !!( (n) & 0x04 ), !!( (n) & 0x02 ), !!( (n) & 0x01 ) 

	#define WORD_TO_BIN_FMT			BYTE_TO_BIN_FMT " " BYTE_TO_BIN_FMT
	#define WORD_TO_BIN( n )		BYTE_TO_BIN( ( (n) >> 8 ) & 0xFF ), BYTE_TO_BIN( (n) & 0xFF )


	#define DWORD_TO_BIN_FMT		WORD_TO_BIN_FMT " " WORD_TO_BIN_FMT
	#define DWORD_TO_BIN( n )		WORD_TO_BIN( ( (n) >> 16 ) & 0xFFFF ), BYTE_TO_BIN( (n) & 0xFFFF )


	//
	// Disable logger if LOG_LEVEL not defined
	//
	#ifndef LOG_LEVEL
		#define LOG_LEVEL eOFF
	#endif

	//
	// if logger module not defined define as MAIN
	//
	#ifndef LOG_MODULE
		#define LOG_MODULE "Main"
	#endif

	//
	// Set logger interfaces
	//
	#if LOG_LEVEL >= eEMPTY
		#define LOG_EMPTY_LINE()		Logger::Write( eEMPTY, LOG_MODULE, "" )
	#else
		#define LOG_EMPTY_LINE()
	#endif

	#if LOG_LEVEL >= eFATAL
		#define FATAL( ... )			Logger::Write( eFATAL, LOG_MODULE, __VA_ARGS__ )
	#else
		#define FATAL( ... )
	#endif

	#if LOG_LEVEL >= eCRITICAL
		#define CRITICAL( ... )			Logger::Write( eCRITICAL, LOG_MODULE, __VA_ARGS__ )
	#else
		#define CRITICAL( ... )
	#endif

	#if LOG_LEVEL >= eERROR
		#define ERROR( ... )			Logger::Write( eERROR, LOG_MODULE, __VA_ARGS__ )
	#else
		#define ERROR( ... )
	#endif

	#if LOG_LEVEL >= eWARNING
		#define WARNING( ... )			Logger::Write( eWARNING, LOG_MODULE, __VA_ARGS__ )
	#else
		#define WARNING( ... )
	#endif

	#if LOG_LEVEL >= eINFO
		#define INFO( ... )				Logger::Write( eINFO, LOG_MODULE, __VA_ARGS__ )
	#else
		#define INFO( ... )
	#endif

	#if LOG_LEVEL >= eDEBUG
		#define DEBUG( ... )			Logger::Write( eDEBUG, LOG_MODULE, __VA_ARGS__ )
	#else
		#define DEBUG( ... )
	#endif

	#if LOG_LEVEL >= eDEEP
		#define DEEP( ... )				Logger::Write( eDEEP, LOG_MODULE, __VA_ARGS__ )
	#else
		#define DEEP( ... )
	#endif

	#if LOG_LEVEL >= eTRACE
		#define TRACE( ... )			Logger::Write( eTRACE, LOG_MODULE, __VA_ARGS__ )
	#else
		#define TRACE( ... )
	#endif

	//
	// Dynamic logger level
	//
	extern uint8_t __Level;

	//
	// Set/Get dynamic logger level
	//
	inline void		SetLogLevel( uint8_t level )	{ __Level = level;	}
	inline uint8_t	GetLogLevel()					{ return __Level;	}

	//
	// Logger file handler
	//
	extern FILE FileHandler;

	//
	// Raw logger write message
	//
	extern int Write( uint8_t level, const char * module, const char * fmt, ... );

	//
	// if logger was disabled or undeclared ATTACH_LOGGER_TO_SERIAL should be empty;
	//
	#if LOG_LEVEL >= eFATAL
		//
		// Create a output function for redirect logger to UART
		// This works because Serial.write, although of
		// type virtual, already exists.
		//
		static int uart_putchar( char c, FILE * stream )
		{
		  Serial.write(c) ;
		  return 0 ;
		}

		#define ATTACH_LOGGER_TO_SERIAL()				fdev_setup_stream( &Logger::FileHandler, Logger::uart_putchar, NULL, _FDEV_SETUP_WRITE )
		#define INIT_SERIAL_AND_ATTACH_LOGGER( boud )	{ Serial.begin( boud ); ATTACH_LOGGER_TO_SERIAL(); }
	#else
		#define ATTACH_LOGGER_TO_SERIAL()
		#define INIT_SERIAL_AND_ATTACH_LOGGER( boud )
	#endif
}
