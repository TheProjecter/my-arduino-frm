#pragma once

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

#if ARDUINO < 100
  #include <WProgram.h>
#else
  #include <Arduino.h>
#endif

namespace Interrupts
{
	namespace External
	{
		//
		//
		//
		class IInterrupt
		{
			public:
				virtual void Throw( int n, bool state ) = 0;
		};

		//
		//
		//
		template<typename T>
			class Extender
			{
				//
				// Internal types declaration
				//
				public:
					typedef uint8_t		pins_type;
					typedef uint8_t		mask_type;
					typedef uint8_t		condition_type;
					typedef uint8_t		index_type;
					typedef uint8_t		size_type;

				//
				//
				//
				private:
					pins_type					_LastValue;

				//
				//
				//
				private:
					const index_type			_Port;
					volatile mask_type *		_Mask;
					volatile pins_type *		_Pins;

				//
				//
				//
				private:
					inline volatile mask_type &	GetMask() { return *( this->_Mask ); }
					inline volatile mask_type &	GetPins() { return *( this->_Pins ); }
				//
				//
				//
				private:
					volatile condition_type		_OnRising;
					volatile condition_type		_OnFalling;

				//
				//
				//
				public: // TODO : return to private
					T * volatile				_Interrupts[ sizeof( pins_type ) << 3 ]; 

				//
				//
				//
				public:
					static inline size_type GetSize() { 
						return sizeof( pins_type ) << 3; 
					}

				//
				//
				//
				public:
					Extender( index_type port ) 
						: _LastValue( 0 ), _OnRising( 0 ), _OnFalling( 0 ), _Port( 1 << port )
					{
						for( int i = 0; i < sizeof( pins_type ) << 3; ++i )
							this->_Interrupts[ i ] = NULL;

						switch( port )
						{
							case PCIE0:
								this->_Mask = &PCMSK0;
								this->_Pins = &PINB;
								break;

							case PCIE1:
								this->_Mask = &PCMSK1;
								this->_Pins = &PINC;
								break;

							case PCIE2:
								this->_Mask = &PCMSK2;
								this->_Pins = &PIND;
								break;
						}

						this->GetMask() = 0;
					}

				//
				// Disable/Enable port interrupt handling
				//
				public:
					inline bool IsEnabled() {
						return PCICR & this->_Port;
					}

					inline bool Enable() {
						return PCICR |= this->_Port;
					}

					inline bool Disable() {
						return PCICR &= ~this->_Port;
					}


				//
				// Disable/Enable specified interrupt
				//
				public:
					inline bool IsEnabled( index_type index ) 
					{
						if( index >= this->GetSize() )
							return false;

						return this->GetMask() & ( 1 << index );
					}

					inline bool Enable( index_type index )
					{
						if( index >= this->GetSize() )
							return false;

						if( index >= this->GetSize() )
							return false;

						this->GetMask() |= 1 << index;
					}

					inline bool Disable( index_type index )
					{
						if( index >= this->GetSize() )
							return false;

						this->GetMask() &= ~( 1 << index );
					}

				//
				// Change/Get on rising state
				//
				public:
					inline bool IsOnRising( index_type index ) 
					{
						if( index >= this->GetSize() )
							return false;

						return this->_OnRising & ( 1 << index );
					}

					inline bool OnRising( index_type index, bool state )
					{
						if( index >= this->GetSize() )
							return false;

						if( state )
							this->_OnRising |= 1 << index;
						else
							this->_OnRising &= ~( 1 << index );
					}

				//
				// Change/Get on falling state
				//
				public:
					inline bool IsOnFalling( index_type index ) 
					{
						if( index >= this->GetSize() )
							return false;

						return this->_OnFalling & ( 1 << index );
					}

					inline bool OnFalling( index_type index, bool state )
					{
						if( index >= this->GetSize() )
							return false;

						if( state )
							this->_OnFalling |= 1 << index;
						else
							this->_OnFalling &= ~( 1 << index );
					}
				//
				// Attach/Detach interrupt
				//
				public:
					bool Attach( T * interrupt, index_type index, bool onRising, bool onFalling, bool enable = true )
					{
						if( index >= this->GetSize() )
							return false;

						if( interrupt == NULL )
							return false;

						if( !this->Detach( index ) )
							return false;

						mask_type bit = 1 << index;

						//
						// 1. Set interrupt object
						// 2. Set OnFalling & OnRising state
						// 3. Set interrupt mask
						//

						// 
						// Notice !!! I DON'T think that we need this cli()/sei() protection
						//

						// cli();

						this->_Interrupts[ index ] = interrupt;

						if( onFalling )
							this->_OnFalling |= bit;
						else
							this->_OnFalling &= ~bit;

						if( onRising )
							this->_OnRising |= bit;
						else
							this->_OnRising &= ~bit;

						this->GetMask() |= bit;

						// sei(); 
						
						return true;
						
					}

					bool Detach( index_type index )
					{
						if( index >= this->GetSize() )
							return false;

						//
						// 1. Unset mask
						// 2. Set interrupt object to NULL
						// 
						// Notice !!! it's should be protected cli()/sei()
						//

						cli();

						this->GetMask() &= ~( 1 << index );
						this->_Interrupts[ index ] == NULL;

						sei();

						return true;
					}

				//
				// Interrupt handler
				//
				void Handle()
				{
					pins_type pins = *( this->_Pins );

					if( pins != this->_LastValue )
					{
						mask_type		mask		= this->GetMask();
						condition_type	onRising	= this->_OnRising;
						condition_type	onFalling	= this->_OnFalling;

						for( int i = 0; i < this->GetSize(); ++i )
						{
							mask_type bit = 1 << i;
					
							if( mask & bit ) // if interrupt enabled
							{
								pins_type value	= pins & bit;

								if( value != ( this->_LastValue & bit ) ) // if value changed
									if( value )
									{
										if( onRising & bit ) // check rising condition is true
										{
											T * interrupt = this->_Interrupts[ i ];
											if( interrupt )
												interrupt->Throw( i, !!value );
										}
									}
									else
										if( onFalling & bit ) // check rising condition is true
										{
											T * interrupt = this->_Interrupts[ i ];
											if( interrupt )
												interrupt->Throw( i, !!value );
										}
							}
						}

						this->_LastValue = pins;
					}
				}
			};
	}
}

