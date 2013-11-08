#pragma once

/*
	Platform.h - Platform library for Simple Arduino Framework
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

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

namespace Platform
{
	inline static void pinMode( uint8_t pin, uint8_t mode ) {
		::pinMode( pin, mode );
	}

	inline static void digitalWrite( uint8_t pin, uint8_t value ) {
		::digitalWrite( pin, value );
	}

	inline static int digitalRead( uint8_t pin ) {
		return ::digitalRead( pin );
	}

	inline static void analogWrite( uint8_t pin, int value ) {
		::analogWrite( pin, value );
	}

	inline static int analogRead( uint8_t pin ) {
		return ::analogRead( pin );
	}

	inline static void shiftOut( uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val ) {
		::shiftOut( dataPin, clockPin, bitOrder, val ); 
	}
};
