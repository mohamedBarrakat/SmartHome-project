/*
 * UART_interface.h
 *
 *  Created on: Aug 4, 2020
 *      Author: high tension
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#define USART_MAX_TIMEOUT (u16)20000
void UART_init(void);

void UART_SendByteSynchronous(u8 DataByte);
void UART_ReceiveByteSynchronous(u8* ReceiveByte );
//void UART_UDR_EMPTY_CHECK(u8* ReceiveByte );
u8 UART_u8Receiver(void);
void Bluetooth_SendString(u8* Data);
void Bluetooth_SendNumber(u16 Number);

//void UART_SendStringAsynchronous(u8 *TransmittedString,u8 SizeOfString, void (*pfNotificationFunction)(void) );
//void UART_ReceiveStringAsynchronous(u8 *ReceiveString);
#endif /* UART_INTERFACE_H_ */
