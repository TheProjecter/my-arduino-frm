#pragma once

/*
	Macros.h - Common library for Simple Arduino Framework
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

namespace Common
{
	#define DO_EVERY( interval, action )									DO_EVERY_TMPL( uint16_t, millis(), interval, 0, action )
	#define DO_EVERY_MICRO( interval, action )								DO_EVERY_TMPL( uint16_t, micros(), interval, 0, action )

	#define DO_EVERY_SHIFT( interval, shift, action )						DO_EVERY_TMPL( uint16_t, millis(), interval, shift, action )
	#define DO_EVERY_MICRO_SHIFT( interval, shift, action )					DO_EVERY_TMPL( uint16_t, micros(), interval, shift, action )

	#define DO_EVERY_T( time_type, interval, action )						DO_EVERY_TMPL( time_type, millis(), interval, 0, action )
	#define DO_EVERY_MICRO_T( time_type, interval, action )					DO_EVERY_TMPL( time_type, micros(), interval, 0, action )

	#define DO_EVERY_SHIFT_T( time_type, interval, shift, action )			DO_EVERY_TMPL( time_type, millis(), interval, shift, action )
	#define DO_EVERY_MICRO_SHIFT_T( time_type, interval, shift, action )	DO_EVERY_TMPL( time_type, micros(), interval, shift, action )

	#define DO_EVERY_TMPL( time_type, time_fn, interval, shift, action )									\
	{																										\
		static	time_type __lastHandleTime	= time_type ( time_fn ) - time_type ( interval + 1 ) + shift;	\
				time_type __nowHandleTime	= time_type ( time_fn );										\
																											\
				if( __nowHandleTime - __lastHandleTime > interval )											\
				{																							\
					__lastHandleTime = __nowHandleTime;														\
					action;																					\
				}																							\
	}
}

