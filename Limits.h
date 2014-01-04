#pragma once

/*
	Limits.h - Macros library for Simple Arduino Framework
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

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif


namespace Common
{
	class Limits
	{
		public:
			inline static int8_t	Min( int8_t value )		{ return 0x80;			}
			inline static int16_t	Min( int16_t value )	{ return 0x8000;		}	
			inline static int32_t	Min( int32_t value )	{ return 0x80000000;	}

		public:
			inline static int8_t	Max( int8_t value )		{ return 0x7F;			}
			inline static int16_t	Max( int16_t value )	{ return 0x7FFF;		}	
			inline static int32_t	Max( int32_t value )	{ return 0x7FFFFFFF;	}

		public:
			inline static uint8_t	Min( uint8_t value )	{ return 0;				}
			inline static uint16_t	Min( uint16_t value )	{ return 0;				}
			inline static uint32_t	Min( uint32_t value )	{ return 0;				}

		public:
			inline static uint8_t	Max( uint8_t value )	{ return 0xFF;			}
			inline static uint16_t	Max( uint16_t value )	{ return 0xFFFF;		}
			inline static uint32_t	Max( uint32_t value )	{ return 0xFFFFFFFF;	}

	};
}
