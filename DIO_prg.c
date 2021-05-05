/*
 * DIO_prg.c
 *
 *  Created on: Feb 8, 2020
 *      Author: karim
 */

#include "utils.h"
#include "ATMega32_Reg.h"
#include "DIO_int.h"


u8 DIO_u8SetPinDir(u8 PortNo, u8 PinNo, u8 PinDir)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PinNo >= DIO_PIN0)   && (PinNo <=DIO_PIN7)    &&
		(PinDir >= DIO_INPUT) && (PinDir <= DIO_OUTPUT) )
	{
		switch(PortNo)
		{
			case DIO_PORTA:
				switch(PinDir)
				{
					case DIO_OUTPUT:
						set_bit(DDRA, PinNo);
					break;

					case DIO_INPUT:
						clr_bit(DDRA, PinNo);
					break;
				}
			break;

			case DIO_PORTB:
				switch(PinDir)
				{
					case DIO_OUTPUT:
						set_bit(DDRB, PinNo);
					break;

					case DIO_INPUT:
						clr_bit(DDRB, PinNo);
					break;
				}
			break;

			case DIO_PORTC:
				switch(PinDir)
				{
					case DIO_OUTPUT:
						set_bit(DDRC, PinNo);
					break;

					case DIO_INPUT:
						clr_bit(DDRC, PinNo);
					break;
				}
			break;

			case DIO_PORTD:
				switch(PinDir)
				{
					case DIO_OUTPUT:
						set_bit(DDRD, PinNo);
					break;

					case DIO_INPUT:
						clr_bit(DDRD, PinNo);
					break;
				}
			break;
		}
	}
	else
	{
		FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}

u8 DIO_u8SetPinVal(u8 PortNo, u8 PinNo, u8 PinVal)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PinNo >= DIO_PIN0)   && (PinNo <=DIO_PIN7)    &&
		(PinVal >= DIO_LOW) && (PinVal <= DIO_HIGH) )
	{
		switch(PortNo)
		{
			case DIO_PORTA:
				switch(PinVal)
				{
					case DIO_HIGH:
						set_bit(PORTA, PinNo);
					break;

					case DIO_LOW:
						clr_bit(PORTA, PinNo);
					break;
				}
			break;

			case DIO_PORTB:
				switch(PinVal)
				{
					case DIO_HIGH:
						set_bit(PORTB, PinNo);
					break;

					case DIO_LOW:
						clr_bit(PORTB, PinNo);
					break;
				}
			break;

			case DIO_PORTC:
				switch(PinVal)
				{
					case DIO_HIGH:
						set_bit(PORTC, PinNo);
					break;

					case DIO_LOW:
						clr_bit(PORTC, PinNo);
					break;
				}
			break;

			case DIO_PORTD:
				switch(PinVal)
				{
					case DIO_HIGH:
						set_bit(PORTD, PinNo);
					break;

					case DIO_LOW:
						clr_bit(PORTD, PinNo);
					break;
				}
			break;
		}
	}
	else
	{
		FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}
													/*u8 PinA3Val; */
u8 DIO_u8GetPinVal(u8 PortNo, u8 PinNo, u8* PinVal)//DIO_u8GetPinVal(DIO_PORTA,DIO_PIN3,&PinA3Val)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PinNo >= DIO_PIN0)   && (PinNo <=DIO_PIN7)    &&
		(PinVal != STD_NULL) )
	{
		switch(PortNo)
		{
			case DIO_PORTA:
				*PinVal = get_bit(PINA, PinNo);
			break;

			case DIO_PORTB:
				*PinVal = get_bit(PINB, PinNo);
				break;


			case DIO_PORTC:
				*PinVal = get_bit(PINC, PinNo);
				break;


			case DIO_PORTD:
				*PinVal = get_bit(PIND, PinNo);
			break;
		}
	}
	else
	{
		FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}

u8 DIO_u8SetPortDir(u8 PortNo, u8 PortDir)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PortDir>=0b00000000) && (PortDir<=0b11111111)	 )
	{

		switch (PortNo)
		{
			case DIO_PORTA:
				DDRA=PortDir; // el mfrod yb2a DDRA=PortDir portdir deh 7tb2a address like 0b00010011 mslan
				break;

			case DIO_PORTB:
				DDRB=PortDir;
				break;

			case DIO_PORTC:
				DDRC=PortDir;
				break;

			case DIO_PORTD:
				DDRD=PortDir;
				break;
		}
	}
	else
	{
		FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}

u8 DIO_u8SetPortVal(u8 PortNo, u8 PortVal)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PortVal>=0b00000000)  && (PortVal<=0b11111111)	 )
	{

		switch (PortNo)
		{
			case DIO_PORTA:
				 PORTA=PortVal;
				 break;

			case DIO_PORTB:
				 PORTB=PortVal;
				 break;

			case DIO_PORTC:
				 PORTC=PortVal;
				 break;

			case DIO_PORTD:
				 PORTD=PortVal;
				 break;
		}
	}
	else
	{
		FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}


u8 DIO_u8GetPortVal(u8 PortNo, u8* PortVal)
{
	u8 FuncReturnState = STD_OK;

	if( (PortNo >= DIO_PORTA) && (PortNo <= DIO_PORTD) &&
		(PortVal != STD_NULL))
	{
		switch (PortNo)
		{
			case DIO_PORTA:
				*PortVal = PINA;
				break;
			case DIO_PORTB:
				*PortVal = PINB;
				break;
			case DIO_PORTC:
				*PortVal = PINC;
				break;
			case DIO_PORTD:
				*PortVal = PIND;
				break;
		}
	}
	else
	{
		u8 FuncReturnState = STD_NOK;
	}

	return FuncReturnState;
}


