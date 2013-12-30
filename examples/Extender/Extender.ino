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

#include <InterruptsExternalExtender.h>

//
// User defined external interrup class
//
//		This class should implement method 
//			- void Throw( int n, bool status ) 
//
//	Notice !!! This library include virtual interface IInterrupt. 
//				if you want to use different classes with one extender, 
//				you can inherit your classes from this interface 
//				and implement interface in your classes 
//
class ExternalInterruptDemo
{
	public:
		ExternalInterruptDemo()
		{
			;
		}

	public:
		void Throw( int n, bool status ) {
			digitalWrite( 13, !digitalRead( 13 ) );
		}
};

//
// Declaration new external interrup extender on PORTD
//
Interrupts::External::Extender<ExternalInterruptDemo> iExtender( PCIE0 );

//
// Interrupt Handling
//
ISR( PCINT0_vect ) {
	iExtender.Handle();
};

//
// 
//
void setup() 
{
	pinMode( 13, OUTPUT );

	iExtender.Attach( new ExternalInterruptDemo(), 0, true, true );
	iExtender.Attach( new ExternalInterruptDemo(), 1, true, false );
	iExtender.Attach( new ExternalInterruptDemo(), 2, false, true );
	iExtender.Attach( new ExternalInterruptDemo(), 3, true, true );

	iExtender.Enable();
}

//
// 
//
void loop()
{
}
