/*
	Logger.cpp - Logger library for Simple Arduino Framework
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

		2013-11-06	Initial version
*/

#include <stdio.h>
#include "Logger.h"

namespace Logger
{
	//
	// Dynamic logger level
	//
	uint8_t	__Level	= eTRACE;

	//
	// Logger file handler
	//
	FILE FileHandler = {0};
	
	//
	// Write log message
	//
	int Write( uint8_t level, const char * module, const char * fmt, ... )
	{
		if( level > __Level)
			return 0;

		va_list ap;
		va_start(ap, fmt);

		const char * levelStr = NULL;

		//
		// Debug level to string
		//
		switch( level )
		{
			case eFATAL:	levelStr = "FATAL";		break;
			case eCRITICAL:	levelStr = "CRITICAL";	break;
			case eERROR:	levelStr = "ERROR";		break;
			case eWARNING:	levelStr = "WARNING";	break;
			case eINFO:		levelStr = "INFO";		break;
			case eDEBUG:	levelStr = "DEBUG";		break;
			case eDEEP:		levelStr = "DEEP";		break;
			case eTRACE:	levelStr = "TRACE";		break;
			default:		levelStr = "Unknown"; 
		}

		//
		// Hardcoded time stamp
		//
		uint32_t timeStamp = millis();

		//
		// Write header
		//
		int header_len = 
			fprintf( &FileHandler, 
						"%2d:%02d:%02d.%03u | %8s | %8s | ", 
						( uint8_t ) ( timeStamp / 1000 / 60 / 60 ) % 24, 
						( uint8_t ) ( timeStamp / 1000 / 60 ) % 60,
						( uint8_t ) ( timeStamp / 1000 ) % 60, 
						( uint16_t ) timeStamp % 1000, 
						module, levelStr );

		if( header_len < 0 )
			return header_len;
 
		//
		// Write message
		//
		int msg_len = vfprintf( &FileHandler, fmt, ap );
		

		if( msg_len < 0 )
			return msg_len;

		//
		// Write endl
		//
		int endl_len = fprintf( &FileHandler, "\r\n" );

		if( endl_len < 0 )
			return msg_len;
		
		//
		// return status
		//
		return header_len + msg_len + endl_len;
	}
}
