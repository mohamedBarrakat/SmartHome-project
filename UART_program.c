/*
 * UART_program.c
 *
 *  Created on: Aug 4, 2020
 *      Author: high tension
 */
#include "stdtypes.h"
#include "utils.h"

#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "LCD_int.h"

	/* Global Pointers */
static u8 * USART_pointer_to_transmitted_string = NULL;
static void (* USART_pointer_to_notification_function)(void) = NULL;
	/* Global Variables */
static u8  USART_size_of_string_transmitted;
static u8  USART_transmit_index=0;

void UART_init(void)
{
//	/* Baud Rate Selection */
//	clr_bit(UCSRA,1);//normal speed
//	UBRRL=51;//9600 baud rate
//u8 Local_UCSRC_Modifier=0b10000000;
//
//	/* USART MODE Synchronous/Asynchronous */
//#if ( USART_MODE == USART_Asynchronus )
//	clr_bit(Local_UCSRC_Modifier,6);
//#elif ( USART_MODE == USART_Synchronus )
//	set_bit(Local_UCSRC_Modifier,6);
//#endif
//
//	/* USART Enabling/Disabling TX/RX */
//#if ( USART_TRANSMITTING == USART_Transmitter_Enable)
//	set_bit(UCSRB,3);
//#elif ( USART_TRANSMITTING == USART_Transmitter_Disable)
//	clr_bit(UCSRB,3);
//#endif
//
//#if ( USART_RECEIVING == USART_Receive_Enable )
//	set_bit(UCSRB,4);
//#elif ( USART_RECEIVING == USART_Receive_Disable)
//	clr_bit(UCSRB,4);
//#endif
//
//	/* USART Data size */
//#if   ( USART_DATA_SIZE == USART_FIVE_BITS )
//	clr_bit(Local_UCSRC_Modifier,1);
//	clr_bit(Local_UCSRC_Modifier,2);
//	clr_bit(UCSRB,2);
//#elif ( USART_DATA_SIZE == USART_SIX_BITS )
//	set_bit(UCSRB,2);
//	clr_bit(Local_UCSRC_Modifier,1);
//	clr_bit(Local_UCSRC_Modifier,2);
//#elif ( USART_DATA_SIZE == USART_SEVEN_BITS )
//	clr_bit(UCSRB,2);
//	set_bit(Local_UCSRC_Modifier,1);
//	clr_bit(Local_UCSRC_Modifier,2);
//#elif ( USART_DATA_SIZE == USART_EIGHT_BITS )
//	set_bit(UCSRB,2);
//	set_bit(Local_UCSRC_Modifier,1);
//	clr_bit(Local_UCSRC_Modifier,2);
//#elif ( USART_DATA_SIZE == USART_NINE_BITS )
//	set_bit(UCSRB,2);
//	set_bit(Local_UCSRC_Modifier,1);
//	set_bit(Local_UCSRC_Modifier,2);
//#endif
//
//	/* USART Parity Mode */
//#if ( USART_PARITY_MODE == USART_Parity_Mode_Disable )
//	clr_bit(Local_UCSRC_Modifier,4);
//	clr_bit(Local_UCSRC_Modifier,5);
//#elif  ( USART_PARITY_MODE == USART_Parity_Mode_Enable_Even )
//	clr_bit(Local_UCSRC_Modifier,4);
//	set_bit(Local_UCSRC_Modifier,5);
//#elif  ( USART_PARITY_MODE == USART_Parity_Mode_Enable_Odd )
//	set_bit(Local_UCSRC_Modifier,4);
//	set_bit(Local_UCSRC_Modifier,5);
//#endif
//
//	/* USART STOP BITS */
//
//#if ( USART_STOP_BIT == USART_One_Stop_Bit )
//	clr_bit(Local_UCSRC_Modifier,3);
//#elif ( USART_STOP_BIT == USART_Two_Stop_Bit )
//	set_bit(Local_UCSRC_Modifier,3);
//#endif
////UCSRC=Local_UCSRC_Modifier;
//	UCSRC = 0b10000110;
	   set_bit(UCSRB,RXEN);
	    set_bit(UCSRB,TXEN);

	//    SetBit(UCSRC,URSEL);
	//
	//    ClrBit(UCSRC,UMSEL);
	//
	//    ClrBit(UCSRC,UPM1);
	//    ClrBit(UCSRC,UPM0);
	//
	//    ClrBit(UCSRC,USBS);
	//
	    clr_bit(UCSRB,UCSZ2);
	//    SetBit(UCSRC,UCSZ1);
	//    SetBit(UCSRC,UCSZ0);

	    UCSRC=0b10000110;
	    clr_bit(UCSRA,U2X);
	//    ClrBit(UBRRH,URSEL);
	//    ClrBit(UBRRH,PIN0);
	//    ClrBit(UBRRH,PIN1);
	//    ClrBit(UBRRH,PIN2);
	//    ClrBit(UBRRH,PIN3);
	    UBRRH=0;
	    UBRRL=51;
}

void UART_SendByteSynchronous(u8 DataByte)
{
//	u16 Local_USART_MAX_TIMEOUT_Counter=0;
//	while( (get_bit(UCSRA,5) == 0) && (Local_USART_MAX_TIMEOUT_Counter <= USART_MAX_TIMEOUT) )
//	{
//		Local_USART_MAX_TIMEOUT_Counter++;
//	}
	 UDR=DataByte;
	    while(get_bit(UCSRA,UDRE)==0);
//	if(Local_USART_MAX_TIMEOUT_Counter  <= USART_MAX_TIMEOUT)
//	{
//		UDR = DataByte;
//	}

}
void UART_ReceiveByteSynchronous(u8* ReceiveByte )
{
	//u16 Local_USART_MAX_TIMEOUT_Counter=0;
	/* Check Pointer Validation */
	if(ReceiveByte != NULL)
	{
		while (get_bit(UCSRA,7) == 0);// && (Local_USART_MAX_TIMEOUT_Counter <= USART_MAX_TIMEOUT))
		//{
			//Local_USART_MAX_TIMEOUT_Counter++;
		//}
		*ReceiveByte=UDR;
		clr_bit(UCSRA,7);
		/*if(Local_USART_MAX_TIMEOUT_Counter <= USART_MAX_TIMEOUT)
		{
			*ReceiveByte=UDR;
		}*/
	}

}


//void UART_SendStringAsynchronous(u8 *TransmittedString,u8 SizeOfString, void (*pfNotificationFunction)(void) )
//{
//	if ( (TransmittedString != NULL) && (pfNotificationFunction != NULL) )
//	{
//		/* To save String's address to the global pointer  */
//		USART_pointer_to_transmitted_string = TransmittedString;
//		/* To Save Notification function's address to the global pointer to function */
//		USART_pointer_to_notification_function = pfNotificationFunction;
//		/* To Save Size of the String in the Global Variable */
//		USART_size_of_string_transmitted = SizeOfString;
//		/* To Check if UDR is Empty */
//		if( (get_bit(UCSRA,5) == 1) )
//		{
//			/* To Enable Tx Interrupt */
//			set_bit(UCSRB,6);
//			/* To Send the 1st Byte of the string */
//			UDR = USART_pointer_to_transmitted_string[0];
//		}
//	}
//}

//void UART_UDR_EMPTY_CHECK(u8* ReceiveByte )
//{
//	while(get_bit(UCSRA,5)==0);
//}

//void UART_ReceiveStringAsynchronous(u8 *ReceiveString)
//{
//
//}

/* USART ISR FOR TX COMPLETE */
void __vector_15(void)
{
	USART_transmit_index++;
	if (USART_transmit_index < USART_size_of_string_transmitted)
	{
		/* To Send The next Byte */
		UDR = USART_pointer_to_transmitted_string[USART_transmit_index];
	}
	else
	{
		/* To Disable Tx Interrupt */
		clr_bit(UCSRB,6);
		/* To Call the Notification function */
		USART_pointer_to_notification_function();
	}
}

u8 UART_u8Receiver(void)
{

	while(get_bit(UCSRA,7)==0);
	//LCD_PrintNum('0'+get_bit(UCSRA,7));
//	set_bit(UCSRA,7);
	return (UDR);
}
//void __vector_13(void)
//{
//
//}

void Bluetooth_SendString(u8* Data)
{
    u8 i=0;

    while(Data[i]!='\0')
    {
    	UART_SendByteSynchronous(Data[i]);
        i++;
    }
}
void Bluetooth_SendNumber(u16 Number)
{
	u8 x,y;
	 if (Number==0)
	 {
		 UART_SendByteSynchronous(48);
	 }else if(Number>0 && Number<10)
	 {
		 UART_SendByteSynchronous((Number+48));
	 }else if(Number>=10 && Number<=99)
	 {
		 x=Number/10;
		 y=Number%10;
		 UART_SendByteSynchronous((x+48));
		 UART_SendByteSynchronous((y+48));
	 }
}
