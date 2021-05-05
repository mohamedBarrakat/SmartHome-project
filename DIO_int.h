/*
 * DIO_int.h
 *
 *  Created on: Feb 8, 2020
 *      Author: karim
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "stdtypes.h"

#define DIO_PORTA  0
#define DIO_PORTB  1
#define DIO_PORTC  2
#define DIO_PORTD  3

#define DIO_PIN0  0
#define DIO_PIN1  1
#define DIO_PIN2  2
#define DIO_PIN3  3
#define DIO_PIN4  4
#define DIO_PIN5  5
#define DIO_PIN6  6
#define DIO_PIN7  7

#define DIO_OUTPUT  1
#define DIO_INPUT   0

#define DIO_HIGH    1
#define DIO_LOW     0

#define STD_OK 1
#define STD_NOK 0

#define STD_NULL (void*)(0x00)


/*DIO_PORTA-DIO_PORTD */
u8 DIO_u8SetPinDir(u8 PortNo, u8 PinNo, u8 PinDir);
u8 DIO_u8SetPinVal(u8 PortNo, u8 PinNo, u8 PinVal);
u8 DIO_u8GetPinVal(u8 PortNo, u8 PinNo, u8* PinVal);
u8 DIO_u8SetPortDir(u8 PortNo, u8 PortDir);
u8 DIO_u8SetPortVal(u8 PortNo, u8 PortVal);
u8 DIO_u8GetPortVal(u8 PortNo, u8* PortVal);

#endif /* DIO_INT_H_ */
