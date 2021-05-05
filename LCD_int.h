/*
 * LCD_int.h
 *
 *  Created on: Feb 14, 2020
 *      Author: high tension
 */

#ifndef LCD_INT_H_
#define LCD_INT_H_

#include"utils.h"
#define F_CPU 8000000u
#include"util/delay.h"
#include"stdtypes.h"
#include"DIO_int.h"
#include"ATMega32_Reg.h"

#define LCD_PORT DIO_PORTB //output port
#define LCD_CTRL_PORT DIO_PORTA//control
#define LCD_CTRL_PIN 0b11100000
/*pins from 0 to 7*/
#define LCD_RS					7
#define LCD_RW					6
#define LCD_Enable 				5
#define LCD_RS_PORT 		DIO_PORTA
#define LCD_RW_PORT			DIO_PORTA
#define LCD_Enable_PORT		DIO_PORTA
#define LCD_4_BIT_MODE    		 0
#define LCD_8_BIT_MODE     		 1
#define LCD_8_BIT_MODE_TEST      2
/* LCD 8-bit Full Configurable */
#define LCD_PIN0  			DIO_PIN1
#define LCD_PIN1			DIO_PIN2
#define LCD_PIN2            DIO_PIN3
#define LCD_PIN3            DIO_PIN4
#define LCD_PIN4            DIO_PIN4
#define LCD_PIN5            DIO_PIN5
#define LCD_PIN6            DIO_PIN6
#define LCD_PIN7            DIO_PIN7
#define LCD_PIN0_PORT       DIO_PORTA
#define LCD_PIN1_PORT       DIO_PORTA
#define LCD_PIN2_PORT       DIO_PORTA
#define LCD_PIN3_PORT       DIO_PORTA
#define LCD_PIN4_PORT       DIO_PORTB
#define LCD_PIN5_PORT       DIO_PORTB
#define LCD_PIN6_PORT       DIO_PORTB
#define LCD_PIN7_PORT       DIO_PORTB




/* LCD Input Mode */
#define LCD_INIT_MODE                LCD_8_BIT_MODE_TEST


void Write_cmd(u8 CMD);
void Write_data(u8 DATA);
void LCD_init(void);
void LCD_goto(u8 x,u8 y);
void LCD_CLR(void);
void LCD_CGR(void);
void LCD_DDR(void);
void LCD_PrintNum(u32 Num);
//void LCD_PrintNegNum(s32 NegNum);
//void LCD_PrintFloatNum(u32 group1,u32 group2);
void LCD_WriteString(u8* Data);



#endif /* LCD_INT_H_ */
