#pragma once

/*
	InterruptsExternalExtender.h - External interrupts library for Simple Arduino Framework
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

		2014-01-04	Added pin direction change on attach procedure 
					Additional small optimization in handling mechanism

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
				// Last detected value of pins state
				//
				private:
					pins_type					_LastValue;

				//
				// Port & Mask & Pins registers
				//
				private:
					const index_type			_Port;
					volatile mask_type *		_Mask;
					volatile pins_type *		_Pins;

				//
				// Get Mask & Pins methods
				//
				private:
					inline volatile mask_type &	GetMask() { return *( this->_Mask ); }
					inline volatile mask_type &	GetPins() { return *( this->_Pins ); }

				//
				// Rising & Falling states
				//
				private:
					volatile condition_type		_OnRising;
					volatile condition_type		_OnFalling;

				//
				// User interrupts handler collection
				//
				public: // TODO : return to private
					T * volatile				_Interrupts[ sizeof( pins_type ) << 3 ]; 

				//
				// Size of user interrupts handler collection
				//
				public:
					static inline size_type GetSize() { 
						return sizeof( pins_type ) << 3; 
					}

				//
				// Constructor
				//
				public:
					Extender( index_type port ) 
						: _LastValue( 0 ), _OnRising( 0 ), _OnFalling( 0 ), _Port( port )
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
						return PCICR & ( 1 << this->_Port );
					}

				public:
					inline bool Enable() {
						return PCICR |= ( 1 << this->_Port );
					}

				public:
					inline bool Disable() {
						return PCICR &= ~( 1 << this->_Port );
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

				public:
					inline bool Enable( index_type index )
					{
						if( index >= this->GetSize() )
							return false;

						if( index >= this->GetSize() )
							return false;

						this->GetMask() |= 1 << index;
					}

				public:
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

				public:
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
					bool Attach( T * interrupt, index_type index, bool onRising = true, bool onFalling = true, bool enable = true )
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
						// 3. Set direction bit
						// 4. Set interrupt mask
						//

						// 
						// Notice !!! I DON'T think that we need this cli()/sei() protection
						//

						// cli();

						// Set interrupt object
						this->_Interrupts[ index ] = interrupt;

						// Set onFalling flags
						if( onFalling )
							this->_OnFalling |= bit;
						else
							this->_OnFalling &= ~bit;

						// Set onRising flags
						if( onRising )
							this->_OnRising |= bit;
						else
							this->_OnRising &= ~bit;

						// Set direction
						switch( this->_Port )
						{
							case PCIE0:
								DDRB &= ~bit;
								break;

							case PCIE1:
								DDRC &= ~bit;
								break;

							case PCIE2:
								DDRD &= ~bit;
								break;

							default:
								// error;
								break;
						}

						// Set mask
						if( enable )
							this->GetMask() |= bit;

						// sei(); 
						
						return true;
						
					}

				public:
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
				// Get bit number, return number of bit or 0xFF
				//
				private:
					inline index_type GetBitNumber( mask_type data )
					{
						switch( data )
						{
							case 0x01: return 0;
							case 0x02: return 1;
							case 0x04: return 2;
							case 0x08: return 3;
							case 0x10: return 4;
							case 0x20: return 5;
							case 0x40: return 6;
							case 0x80: return 7;
							default:
								return 0xFF;
						}
					}
				
				//
				// Get bit number, return number of bit or 0xFF
				//
				public:
					inline void CallUserInterruptHandler( register index_type n, register bool value )
					{
						register T * interrupt = this->_Interrupts[ n ];
										
						if( interrupt )
							interrupt->Throw( n, value );
					}

				//
				// Multiple Interrupt handler
				//		- this is regular handler, will be called if changes has detected on two or more pins
				//
				public:
					void HandleMultipleInterrupts( register pins_type pins, register pins_type changes )
					{
						register condition_type onRising	= this->_OnRising;	// get rising codition
						register condition_type onFalling	= this->_OnFalling;	// get falling codition

						if( changes ) // if we have chages, otherwize it's a fake interrupt
							for( register index_type i = 0; i < this->GetSize(); ++i ) // run bits loop 
							{
								register mask_type bit = 1 << i; // calculate mask for current bit

								if( changes & bit ) // if bit has changed
								{
									register bool value = !!( pins & bit ); // calculate current value of this bit

									if( value ) // if rising, otherwize it's a falling
									{
										if( onRising & bit ) // check rising condition
											this->CallUserInterruptHandler( i, value );
									}
									else
										if( onFalling & bit ) // check rising condition
											this->CallUserInterruptHandler( i, value );
								}
							}
					}

				//
				// Single Interrupt handler 
				//		-	it's a optimized handler - this handler will be called first, 
				//			and if has detect change on two or more pins will be called  Multiple Interrupt handler
				//
				public:
					void Handle()
					{
						register pins_type pins		= *( this->_Pins );
						register pins_type changes	= ( pins ^ this->_LastValue ) & this->GetMask();

						if( changes )
						{
							register index_type index = this->GetBitNumber( changes );

							if( index != 0xFF )
							{
								register bool value = pins & changes;

								if( value )
								{
									if( this->_OnRising & changes ) // check rising condition is true
										this->CallUserInterruptHandler( index, value );
								}
								else
									if( this->_OnFalling & changes ) // check rising condition is true
										this->CallUserInterruptHandler( index, value );
							}
							else
								this->HandleMultipleInterrupts( pins, changes );
						}

						this->_LastValue = pins;
					}
			};
	}
}

