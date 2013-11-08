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
	#define eFATAL		0x01
	#define eCRITICAL	0x02
	#define eERROR		0x03
	#define eWARNING	0x04
	#define eINFO		0x05
	#define eDEBUG		0x06
	#define eDEEP		0x07
	#define eTRACE		0x08

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
	int Write( uint8_t level, const char * module, const char * fmt, ... );
}
