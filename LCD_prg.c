/*
 * LCD_prg.c
 *
 *  Created on: Feb 14, 2020
 *      Author: high tension
 */
#include"LCD_int.h"
#include"utils.h"
#define F_CPU 8000000u
#include"util/delay.h"
#include"stdtypes.h"
#include"DIO_int.h"
#include"ATMega32_Reg.h"

u8 LCD_PIN_ARRAY[8]={LCD_PIN0,LCD_PIN1,LCD_PIN2,LCD_PIN3,LCD_PIN4,LCD_PIN5,LCD_PIN6,LCD_PIN7};
u8 LCD_PIN_PORT_ARRAY[8]={LCD_PIN0_PORT,LCD_PIN1_PORT,LCD_PIN2_PORT,LCD_PIN3_PORT,LCD_PIN4_PORT,LCD_PIN5_PORT,LCD_PIN6_PORT,LCD_PIN7_PORT};

void LCD_init(void)// initialization
{
	u8 i,j;
#if LCD_INIT_MODE == LCD_8_BIT_MODE
	/* LCD 8-bit Mode */
	DIO_u8SetPortDir(LCD_PORT,0b11111111);//LCD output
	DIO_u8SetPortDir(LCD_CTRL_PORT,LCD_CTRL_PIN);//RS-R/W-EN (Control)
	_delay_ms(30);
 	Write_cmd(0b00111100);
	_delay_ms(1);
	Write_cmd(0b0001111);
	_delay_ms(1);
	Write_cmd(0b00000001);
	_delay_ms(2);
	/* LCD 4-bit Mode */
#elif LCD_INIT_MODE == LCD_4_BIT_MODE
	DIO_u8SetPortDir(LCD_PORT,0b11110000);
	DIO_u8SetPortDir(LCD_CTRL_PORT,LCD_CTRL_PIN);
	_delay_ms(35);
	/* Send 4 bits high of the function set cmnd */
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT,0b00100000);
////	DIO_u8SetPortVal(LCD_PORT,0b00100000);
	Write_cmd(0b00100000);
//	Write_cmd(0b00100000);
	/* Enable Latch */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
////	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);
////	_delay_us(2);
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
////	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);
	/* Func set */
	Write_cmd(0b00101000);
	_delay_us(40);
	Write_cmd(0b00001111);
	_delay_us(40);
	Write_cmd(0x01);
	_delay_ms(2);
//	LCD_voidWriteCmnd(0b00000110);
//	Write_cmd(0b00000110);
#elif LCD_INIT_MODE == LCD_8_BIT_MODE_TEST
	/* LCD 8-bit Mode */
//	DIO_u8SetPortDir(LCD_PORT,0b11111111);//LCD output
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(LCD_PIN_ARRAY[i]==j)
			{
				DIO_u8SetPinDir(LCD_PIN_PORT_ARRAY[i],LCD_PIN_ARRAY[i],DIO_OUTPUT);
				break;
			}
		}
	}
//	DIO_u8SetPortDir(LCD_CTRL_PORT,LCD_CTRL_PIN);//RS-R/W-EN (Control)
	DIO_u8SetPinDir(LCD_RS_PORT,LCD_RS,DIO_HIGH);
	DIO_u8SetPinDir(LCD_RW_PORT,LCD_RW,DIO_HIGH);
	DIO_u8SetPinDir(LCD_Enable_PORT,LCD_Enable,DIO_HIGH);
	_delay_ms(30);
 	Write_cmd(0b00111100);
	_delay_ms(1);
	Write_cmd(0b00001111);
	_delay_ms(1);
	Write_cmd(0b00000001);
	_delay_ms(2);
#endif
}

void Write_cmd(u8 CMD)
{
	u8 i,j;
	/* LCD Write Command 8-bit Mode */
#if LCD_INIT_MODE == LCD_8_BIT_MODE
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_LOW);//RS
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);//R-W
	DIO_u8SetPortVal(LCD_PORT,CMD);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);// enable 0
	/* LCD Write Command 4-bit Mode */
#elif LCD_INIT_MODE == LCD_4_BIT_MODE
	/* 4 bit mode */
	/* RW = 0 */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);
	/* RS = 0 */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_LOW);
	/* SET Port value with Cmnd 4 bits High */
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd);
	DIO_u8SetPortVal(LCD_PORT,CMD);
	/* Enable Latch */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);
	_delay_us(1);
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);
	/* Send 4 bits low */
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Cmnd<<4);
	DIO_u8SetPortVal(LCD_PORT,CMD<<4);
	/* Enable Latch */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);
	_delay_us(1);
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);
	_delay_ms(2);
#elif LCD_INIT_MODE == LCD_8_BIT_MODE_TEST
	DIO_u8SetPinVal(LCD_RS_PORT,LCD_RS,DIO_LOW);//RS
	DIO_u8SetPinVal(LCD_RW_PORT,LCD_RW,DIO_LOW);//R-W
//	DIO_u8SetPortVal(LCD_PORT,CMD);
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(LCD_PIN_ARRAY[i]==j)
			{
				DIO_u8SetPinVal(LCD_PIN_PORT_ARRAY[i],LCD_PIN_ARRAY[i],get_bit(CMD,i));
				break;
			}
		}
	}
	DIO_u8SetPinVal(LCD_Enable_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_Enable_PORT,LCD_Enable,DIO_LOW);// enable 0
#endif
}

void Write_data(u8 DATA)
{
	u8 i,j;
	/* LCD Write Data 8-bit Mode */
#if LCD_INIT_MODE == LCD_8_BIT_MODE
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_HIGH);//data register 1
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);//Write 0
	DIO_u8SetPortVal(LCD_PORT,DATA);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);//enable 0
	/* LCD Write Data 4-bit Mode */
#elif LCD_INIT_MODE == LCD_4_BIT_MODE
	/* RW = 0 */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RW_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RW,DIO_LOW);
	/* RS = 1 */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_RS_PIN,DIO_u8_HIGH);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_RS,DIO_HIGH);
	/* SET Port value with Char Byte */
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char);
	DIO_u8SetPortVal(LCD_PORT,DATA);
	/* Enable Latch */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);
	_delay_us(1);
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);
	/* SET Port value with Char Byte */
//	DIO_u8SetPortValue(LCD_u8_DATA_PORT,Copy_u8Char<<4);
	DIO_u8SetPortVal(LCD_PORT,DATA<<4);
	/* Enable Latch */
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_HIGH);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_HIGH);
	_delay_us(1);
//	DIO_u8SetPinValue(LCD_u8_CONTROL_PORT,LCD_u8_E_PIN,DIO_u8_LOW);
	DIO_u8SetPinVal(LCD_CTRL_PORT,LCD_Enable,DIO_LOW);
	_delay_ms(2);
#elif LCD_INIT_MODE == LCD_8_BIT_MODE_TEST
	DIO_u8SetPinVal(LCD_RS_PORT,LCD_RS,DIO_HIGH);//data register 1
	DIO_u8SetPinVal(LCD_RW_PORT,LCD_RW,DIO_LOW);//Write 0
//	DIO_u8SetPortVal(LCD_PORT,DATA);
	for(i=0;i<=7;i++)
	{
		for(j=0;j<=7;j++)
		{
			if(LCD_PIN_ARRAY[i]==j)
			{
				DIO_u8SetPinVal(LCD_PIN_PORT_ARRAY[i],LCD_PIN_ARRAY[i],get_bit(DATA,i));
				break;
			}
		}
	}
	DIO_u8SetPinVal(LCD_Enable_PORT,LCD_Enable,DIO_HIGH);//enable 1
	_delay_ms(2);
	DIO_u8SetPinVal(LCD_Enable_PORT,LCD_Enable,DIO_LOW);//enable 0
#endif
}

void LCD_goto(u8 x,u8 y)//y 1st line and 2nd line ,x in the space horizontal
{
	if (y==0)
	{
		Write_cmd(0b10000000+x);//right shift
	}
	else
	{
		Write_cmd(0b11000000+x);
	}
}

void LCD_CLR(void)
{
	Write_cmd(0b00000001);
}
 void LCD_CGR(void)
 {
	 Write_cmd(0b01000000);//write on CGRAM 0b11100000 awl tlat 111 mesh bytktb fehom 7aga
 }

 void LCD_DDR(void)
 {
	 Write_cmd(0b10000000);
 }

 void LCD_PrintNum(u32 Num)
 {


	 u32 x=0,y=0,z=0,h=0,k=0,L=0,m=0,temp=0;

	 if (Num==0)
	 {
		 Write_data('0');
	 }else if(Num>0 && Num<10)
	 {
		 Write_data('0'+Num);
	 }else if(Num>=10 && Num<=99)
	 {
		 x=Num/10;
		 y=Num%10;
		 Write_data('0'+x);
		 Write_data('0'+y);
	 }else if(Num>=100 && Num<=999)
	 {
		 x=Num/100;//el 101 eg,101 ->1
		 y=Num%100;//1
		 //e=Num-x*100
		 temp=y/10;//0
		 z=y%10;//0
		 Write_data('0'+x);
		 Write_data('0'+temp);
		 Write_data('0'+z);
	 }else if(Num>=1000 && Num<=9999)
	 {
		 x=Num/1000;//1244 ->x=1*
		 temp=Num%1000;//temp=244
		 y=temp/100;//y=2*
		 z=temp%100;//z=44
		 temp=z;// temp=44
		 z=temp/10;//z=4*
		 h=temp%10;//h=4*
		 Write_data('0'+x);//1
		 Write_data('0'+y);//2
		 Write_data('0'+z);//4
		 Write_data('0'+h);//4

	 }
	 else if(Num>=10000 && Num<=99999)
	 	 {
	 		 x=Num/10000;//12444 ->x=1*
	 		 temp=Num%10000;//temp=2444
	 		 y=temp/1000;//y=2*
	 		 z=temp%1000;//z=444
	 		 temp=z;// temp=444
	 		 z=temp/100;//z=4*
	 		 h=temp%100;//h=44
	 		 temp=h;
	 		 h=temp/10;//h=4
			 k=temp%10;

	 		 Write_data('0'+x);//1
	 		 Write_data('0'+y);//2
	 		 Write_data('0'+z);//4
	 		 Write_data('0'+h);//4
	 		 Write_data('0'+k);//4

	 	 }
	 else if(Num>=100000 && Num<=999999)
	 	 {
	 		 x=Num/100000;//124444 ->x=1*
	 		 temp=Num%100000;//temp=24444
	 		 y=temp/10000;//y=2*
	 		 z=temp%10000;//z=4444
	 		 temp=z;// temp=4444
	 		 z=temp/1000;//z=4*
	 		 h=temp%1000;//h=444
	 		 temp=h;
	 		 h=temp/100;//h=4
			 k=temp%100;//k=44
			 temp=k;
			 k=temp/10;//k=4
			 L=temp%10;//L=4

	 		 Write_data('0'+x);//1
	 		 Write_data('0'+y);//2
	 		 Write_data('0'+z);//4
	 		 Write_data('0'+h);//4
	 		 Write_data('0'+k);//4
	 		 Write_data('0'+L);//4

	 	 }
	 else if(Num>=1000000 && Num<=9999999)
	 	 {
	 		 x=Num/1000000;//124444 ->x=1*
	 		 temp=Num%1000000;//temp=24444
	 		 y=temp/100000;//y=2*
	 		 z=temp%100000;//z=4444
	 		 temp=z;// temp=4444
	 		 z=temp/10000;//z=4*
	 		 h=temp%10000;//h=444
	 		 temp=h;
	 		 h=temp/1000;//h=4
			 k=temp%1000;//k=44
			 temp=k;
			 k=temp/100;//k=4
			 L=temp%100;//L=4
			 temp=L;
			 L=temp/10;
			 m=temp%10;

	 		 Write_data('0'+x);//1
	 		 Write_data('0'+y);//2
	 		 Write_data('0'+z);//3
	 		 Write_data('0'+h);//4
	 		 Write_data('0'+k);//5
	 		 Write_data('0'+L);//6
	 		 Write_data('0'+m);//7

	 	 }

 }

//void LCD_PrintNegNum(s32 NegNum)
// {
//	 u32 g;
//	 u8 x=0,y=0,z=0,h=0,temp=0;
//	if (NegNum<0)
//	{
//		Write_data('-');
//		g=(NegNum)*(-1);
//	}
//	else
//	{
//		g=NegNum;
//	}
//
//
//	 if (g==0)
//	 {
//		 Write_data('0');
//	 }else if(g>0 && g<10)
//	 {
//		 Write_data('0'+g);
//	 }else if(g>=10 && g<=99)
//	 {
//		 x=g/10;
//		 y=g%10;
//		 Write_data('0'+x);
//		 Write_data('0'+y);
//	 }else if(g>=100 && g<=999)
//	 {
//		 x=g/100;//el 101 eg,101 ->1
//		 y=g%100;//1
//		 //e=Num-x*100
//		 temp=y/10;//0
//		 z=y%10;//0
//		 Write_data('0'+x);
//		 Write_data('0'+temp);
//		 Write_data('0'+z);
//	 }else if(g>=1000 && g<=9999)
//	 {
//		 x=g/1000;//1244 ->x=1*
//		 temp=g%1000;//temp=244
//		 y=temp/100;//y=2*
//		 z=temp%100;//z=44
//		 temp=z;// temp=44
//		 z=temp/10;//z=4*
//		 h=temp%10;//h=4*
//		 Write_data('0'+x);//1
//		 Write_data('0'+y);//2
//		 Write_data('0'+z);//4
//		 Write_data('0'+h);//4
//
//	 }
//
// }

//void LCD_PrintFloatNum(u32 group1,u32 group2)
//{
//	u32 temp1,temp2;
//
//	if (group1%group2==0)
//	{
//		temp1=group1/group2;
//		LCD_PrintNum(temp1);
//	}
//	else
//	{
//		temp1=group1/group2;
//		LCD_PrintNum(temp1);
//		Write_data('.');
//		temp2=group1%group2;
//		LCD_PrintNum(temp2);
//	}
//
//
//}

void LCD_WriteString(u8* Data)
{
	 u8 i=0;

	    while(Data[i]!='\0')
	    {
	    	Write_data(Data[i]);
	    	_delay_ms(2);
	        i++;
	    }
}
