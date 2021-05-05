/*
 * UARD_config.h
 *
 *  Created on: Aug 4, 2020
 *      Author: high tension
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

/* USART Modes Options
 USART_Asynchronus
 USART_Synchronus
*/
#define  USART_MODE      USART_Asynchronus

/* Enable/Disable USART Receiver/Transmitter Options
 USART_Receive_Enable
 USART_Receive_Disable
 USART_Transmitter_Enable
 USART_Transmitter_Disable
 */
#define USART_TRANSMITTING    	USART_Transmitter_Enable
#define USART_RECEIVING			USART_Receive_Enable

/* Data size Options
 USART_FIVE_BITS
 USART_SIX_BITS
 USART_SEVEN_BITS
 USART_EIGHT_BITS
 USART_NINE_BITS
 */
#define USART_DATA_SIZE		   USART_EIGHT_BITS

/* Parity BITS Options
 USART_Parity_Mode_Disable
 USART_Parity_Mode_Enable_Even
 USART_Parity_Mode_Enable_Odd
 */
#define USART_PARITY_MODE	  USART_Parity_Mode_Disable

/* Stop BITS Options
 USART_One_Stop_Bit
 USART_Two_Stop_Bit
 */
#define USART_STOP_BIT         USART_One_Stop_Bit


#endif /* UART_CONFIG_H_ */
