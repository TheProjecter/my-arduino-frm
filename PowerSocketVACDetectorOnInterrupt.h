#pragma once

/*
	PowerSocketVACDetectorOnInterrupt.h - PowerSocket library for Simple Arduino Framework
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

		2014-01-06	Initial version

*/


#include "Limits.h"
#include "TimingDrivers.h"
#include "InterruptsExternalExtender.h"

#include "PowerSocketIVACDetector.h"

namespace PowerSocket
{
	//
	//	VACDetector by external interrupt
	//
	template<typename T = Timing::MillisTimingDriver<int8_t> >
		class VACDetectorOnInterrupt : public IVACDetector, public Interrupts::External::IInterrupt
		{
			//
			// Types declaration section
			//
			private:
				typedef typename T::time_type time_type;

			//
			// Declaration private members section
			//
			private:
				volatile	time_type	_Marker;
							time_type	_Timeout;

			//
			// Public methods section
			//
			public:
				inline time_type	GetMarker()						{ return this->_Marker;				}
				inline time_type	SetTimeout( time_type timeout ) { return this->_Timeout = timeout;	}
				inline time_type	GetTimeout()					{ return this->_Timeout;			}


			//
			// Constructors section
			//
			public:
				VACDetectorOnInterrupt( int frequency = 50, int timeout_factor = 1 )
					: _Marker( 0 ), _Timeout( T::GetBaseFrequency() * timeout_factor / frequency )
				{
					;
				}


			public:
				VACDetectorOnInterrupt( time_type timeout ) 
					: _Marker( 0 ), _Timeout( timeout )
				{
					;
				}

			//
			//	Implementation of IInterrupt interface section
			//
			public:
				void Throw( int index, bool status ) {
					this->_Marker = Now();
				}

			//
			// Implementation of IVACDetector interface section
			//
			public:
				virtual bool IsActive() {
					return this->_Marker != -1;
				}


			public:
				virtual void Reset( bool isActive = true ) 
				{
					if( isActive )
						this->Throw( 0, isActive );
					else
						this->_Marker = -1;
				}


			public:
				virtual void Handle() 
				{
					cli();

					if( this->_Marker != -1 && ( ( this->Now() - this->_Marker ) & Common::Limits::Max( time_type() ) ) > this->_Timeout )
						this->_Marker = -1;

					sei();
				}

			//
			//	Timing methods section
			//
			public:
				inline static time_type Now() { 
					return time_type( T::Now() & Common::Limits::Max( time_type() ) ); 
				}


		};

}