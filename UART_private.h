#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

/* UART Registers */
#define UDR			 *((volatile u8*)0x2C)
#define UCSRA	     *((volatile u8*)0x2B)
#define UCSRB		 *((volatile u8*)0x2A)
#define UBRRL		 *((volatile u8*)0x29)

#define UCSRC		 *((volatile u8*)0x40)
#define UBRRH		 *((volatile u8*)0x40)

/* USART Modes */
#define USART_Asynchronus							0
#define USART_Synchronus							1

/* USART Enable/Disable USART Receiver/Transmitter */
#define USART_Receive_Enable						1
#define USART_Receive_Disable						0
#define USART_Transmitter_Enable					1
#define USART_Transmitter_Disable					0

/* USART Baud Rate options Datasheet Page 165 */
#define BAUD_RATE   		51

/* USART Data size */
#define USART_FIVE_BITS			                  	0
#define USART_SIX_BITS			                  	1
#define USART_SEVEN_BITS		                    2
#define USART_EIGHT_BITS	                       	3
#define USART_NINE_BITS			                  	4

/* USART Parity BITS */
#define USART_Parity_Mode_Disable    	   	        0
#define USART_Parity_Mode_Enable_Even	   	        1
#define USART_Parity_Mode_Enable_Odd	   	        2


/*GELLOZ*/
#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7
#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7


/* USART Stop BITS */
#define USART_One_Stop_Bit			   	            0
#define USART_Two_Stop_Bit			   	            1

/* USART ISR */
void __vector_15(void)     __attribute__((signal));
void __vector_13(void)     __attribute__((signal));


#endif /* UART_PRIVATE_H_ */
