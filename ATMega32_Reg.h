/*
 * ATMega32_Reg.h
 *
 *  Created on: Feb 8, 2020
 *      Author: karim
 */

#ifndef ATMEGA32_REG_H_
#define ATMEGA32_REG_H_
/*PORTS (Output/Input)*/
#define DDRA *((volatile u8*)0x3A)
#define DDRB *((volatile u8*)0x37)
#define DDRC *((volatile u8*)0x34)
#define DDRD *((volatile u8*)0x31)
/*PORTS Volt (0-1)*/
#define PORTA *((volatile u8*)0x3B)
#define PORTB *((volatile u8*)0x38)
#define PORTC *((volatile u8*)0x35)
#define PORTD *((volatile u8*)0x32)
/*PIN REGISTERS*/
#define PINA *((volatile u8*)0x39)
#define PINB *((volatile u8*)0x36)
#define PINC *((volatile u8*)0x33)
#define PIND *((volatile u8*)0x30)
/*Interrupt REGISTERS*/
#define GICR   *((volatile u8*)0x5B)
#define MCUCR  *((volatile u8*)0x55)
//#define SREG   *((volatile u8*)0x5F)
#define MCUCSR *((volatile u8*)0x54)
#define GIFR   *((volatile u8*)0x5A)
/*ADC REGISTERS*/
#define ADCSRA *((volatile u8*)0x26)
#define ADMUX  *((volatile u8*)0x27)
#define ADCH   *((volatile u8*)0x25)
#define ADCL   *((volatile u8*)0x24)
#define ADC    *((volatile u16*)0x24)
#define SFIOR  *((volatile u8*)0x50)




#endif /* ATMEGA32_REG_H_ */
