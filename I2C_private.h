
#ifndef I2C_PRIVATE_H_
#define I2C_PRIVATE_H_

/* I2C Registers */
#define TWCR       *((volatile u8*)0x56)
#define TWBR       *((volatile u8*)0x20)
#define TWSR       *((volatile u8*)0x21)
#define TWDR       *((volatile u8*)0x23)
#define TWAR       *((volatile u8*)0x22)

/* I2C Bit-Macros */
#define TWPS0			0
#define TWPS1			1
/* TWCR Bits Macros */
#define TWIE            0
//#define Reserved      1
#define TWEN            2
#define TWWC            3
#define TWSTO           4
#define TWSTA           5
#define TWEA            6
#define TWINT           7

/* Acknowledgment */
#define I2C_Start_Cond_Ack					8
#define I2C_Repeated_Start_Cond_Ack			16
#define I2C_SLA_With_Write_Ack				24
#define I2C_SLA_With_Read_Ack				64
#define I2C_SLA_With_Write_NotAck			32
#define I2C_SLA_With_Read_NotAck			72
#define I2C_Data_Byte_Transmit_Ack			40
#define I2C_Data_Byte_Received_Ack			80
#define I2CData_Byte_Transmit_NotAck		48
#define I2CData_Byte_Received_NotAck		88


#endif /* I2C_PRIVATE_H_ */
