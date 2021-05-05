//#include "stdtypes.h"
//#include "utils.h"
//
//#include "I2C_interface.h"
//#include "I2C_private.h"
//#include "I2C_config.h"
//
//void I2C_voidMasterInit(void)
//{
//	/* Set Prescaler Value */
//	clr_bit(TWSR,0);
//	clr_bit(TWSR,1);
//	/* Using 200kHz From Equation Page 173 */
//	TWBR=12;
//	/* Enable Acknowledgement */
//	set_bit(TWCR,TWEA);
//	/* Enable I2C */
//	set_bit(TWCR,TWEN);
//
//}
//
//void I2C_voidSlaveInit(u8 SlaveAdress)
//{ //Adress should be in range of 0->127
//	/* Init Adress of the Slave */
//	TWAR= SlaveAdress<<1;
//	/* General Call initially set to 0 -> Bit 0 */
//	/* Enable  Ack */
//	set_bit(TWCR,TWEA);
//	/* Enable I2C */
//	set_bit(TWCR,TWEN);
//}
//
//void I2C_SendStartCondition(void)
//{
//	/* Start Condtion */
//	set_bit(TWCR,TWSTA);
//	/* Clear Flag */
//	set_bit(TWCR,TWINT);
//	/* Polling on Flag */
//	while(get_bit(TWCR,TWINT)==0);
//	/* Check Ack */
//	if((TWSR &0b11111000) == I2C_Start_Cond_Ack)
//	{
//		/* States ENUM */
//	}
//	else
//	{
//		/* Error ENUM */
//	}
//}
//
//void I2C_SendRepeatedStart(void)
//{
//	/* Start Condtion */
//	set_bit(TWCR,TWSTA);
//	/* Clear Flag */
//	set_bit(TWCR,TWINT);
//	/* Polling on Flag */
//	while(get_bit(TWCR,TWINT)==0);
//	/* Check Ack */
//	if((TWSR &0b11111000) == I2C_Repeated_Start_Cond_Ack)
//	{
//		/* States ENUM */
//	}
//	else
//	{
//		/* Error ENUM */
//	}
//}
//
//void I2C_SendSlaveAdressWithWrite(u8 SlaveAdress)
//{
//	/* Clear Start Condition Bit */
//	clr_bit(TWCR,TWSTA);
//	/* Send Slave Address + Write Bit */
//	SlaveAdress = ((SlaveAdress<<1) | 0);
//	/* Sending Data Byte */
//	TWDR = SlaveAdress;
//	/* Clearing flag by Writing a logical 1 */
//	set_bit(TWCR,TWINT);
//	/* Polling on Flag */
//	while(get_bit(TWCR,TWINT)==0);
//	/* Check Ack */
//	if((TWSR &0b11111000) == I2C_SLA_With_Write_Ack)
//	{
//		/* States ENUM */
//	}
//	else
//	{
//		/* Error ENUM */
//	}
//}
//
//void I2C_SendSlaveAdressWithRead(u8 SlaveAdress)
//{
//	/* Clear Start Condition Bit */
//	clr_bit(TWCR,TWSTA);
//	/* Send Slave Address + Read Bit */
//	SlaveAdress = ((SlaveAdress<<1) | 1);
//	/* Sending Data Byte */
//	TWDR = SlaveAdress;
//	/* Clearing flag by Writing a logical 1 */
//	set_bit(TWCR,TWINT);
//	/* Polling on Flag */
//	while(get_bit(TWCR,TWINT)==0);
//	/* Check Ack */
//	if((TWSR &0b11111000) == I2C_SLA_With_Read_Ack)
//	{
//		/* States ENUM */
//	}
//	else
//	{
//		/* Error ENUM */
//	}
//}
//void I2C_SendDataByteMASTER(u8 Data)
//{
//	/* Sending Data To TWDR */
//	TWDR= Data;
//	/* Clearing flag by Writing a logical 1 */
//	set_bit(TWCR,TWINT);
//	/* Polling on Flag */
//	while(get_bit(TWCR,TWINT)==0);
//	/* Check Ack */
//	if((TWSR &0b11111000) == I2C_Data_Byte_Transmit_Ack)
//	{
//		/* States ENUM */
//	}
//	else
//	{
//		/* Error ENUM */
//	}
//}
//
//void I2C_ReadDataByteMASTER(u8* PointerToReceivedDataVariable)
//{
//	if (PointerToReceivedDataVariable !=NULL)
//	{
//		/* Clearing flag by Writing a logical 1 */
//		set_bit(TWCR,TWINT);
//		/* Polling on Flag */
//		while(get_bit(TWCR,TWINT)==0);
//		/* Check Ack */
//		if((TWSR &0b11111000) == I2C_Data_Byte_Received_Ack)
//		{
//			/* States ENUM */
//			*PointerToReceivedDataVariable = TWDR;
//		}
//		else
//		{
//			/* Error ENUM */
//		}
//	}
//}
//
//void I2C_SendStopCondition(void)
//{
//	/* Clearing flag by Writing a logical 1 */
//	set_bit(TWCR,TWINT);
//	/* Sending Stop Condition */
//	set_bit(TWCR,TWSTO);
//	/* Clearing flag by Writing a logical 1 */
//	set_bit(TWCR,TWINT);
//
//}
#include "stdtypes.h"
#include "utils.h"

#include "I2C_interface.h"
#include "I2C_private.h"
//#include "I2C_config.h"


void i2c_init_master(void)
{
	TWBR = 0x02; // bit rate = 400.000 kbps, F_CPU = 8M   SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0));    //baud rate
	TWCR = (1<<TWEN);                      //enable I2C
	return;
}

void i2c_init_slave(void)
{
	TWAR = (1<<1);    // my address = 0x01
	TWCR = (1<<TWEN); //enable I2C
	return;
}

void i2c_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);      // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	while(!(TWCR & (1<<TWINT)));                     // Wait till start condition is transmitted
	while((TWSR & 0xF8) != START_ACK);               // Check for the acknowledgment
	return;
}

void i2c_repeated_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);         // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	while(!(TWCR & (1<<TWINT)));                        // wait till restart condition is transmitted
	while((TWSR & 0xF8) != REP_START_ACK);              // Check for the acknowledgment
	return;
}

void i2c_send_slave_address_with_write_req(unsigned char slave_address)
{
//	Write_data('4');
	TWDR = (slave_address<<1);                     //Address and write instruction
//	Write_data('5');
	TWCR = (1<<TWINT) | (1<<TWEN);                 // Clear TWI interrupt flag, Enable TWI
//	Write_data('6');
	while (!(TWCR & (1<<TWINT)));                  // Wait till complete TWDR byte transmitted
//	Write_data('7');
	while((TWSR & 0xF8) != SLAVE_ADD_AND_WR_ACK);  // Check for the acknowledgment
//	Write_data('8');
	return;
}

void i2c_send_slave_address_with_read_req(unsigned char slave_address)
{
	TWDR = (slave_address<<1);                     //Address
	TWDR |= (1<<0);                                // read instruction
//	TWDR = slave_address;
	TWCR = (1<<TWINT) | (1<<TWEN);                 // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));                  // Wait till complete TWDR byte received
	while((TWSR & 0xF8) != SLAVE_ADD_AND_RD_ACK);  // Check for the acknowledgment
}

void i2c_write_byte(unsigned char byte)
{
	TWDR = byte;                         // put data in TWDR
	TWCR = (1<<TWINT) | (1<<TWEN);       // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT)));        // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != WR_BYTE_ACK); // Check for the acknowledgment
	return;
}

unsigned char i2c_read_byte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);             // Clear TWI interrupt flag,Enable TWI
	while(!(TWCR & (1<<TWINT)));               // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != RD_BYTE_WITH_NACK); // Check for the acknowledgment
	return TWDR;
}

void i2c_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); // Clear TWI interrupt flag, Put stop condition on SDA,Enable TWI
	return;
}

void i2c_slave_check_slave_address_received_with_write_req(void)
{
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT);       // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while (!(TWCR & (1<<TWINT)));                    // Wait for TWINT flag
	while((TWSR & 0xF8) != SLAVE_ADD_RCVD_WR_REQ) ;
	return;
}

void i2c_slave_check_slave_address_received_with_read_req(void)
{
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWINT); // enable acknowledgment after receive, Enable TWI, Clear TWI interrupt flag
	while (!(TWCR & (1<<TWINT)));              // Wait for TWINT flag
	while((TWSR & 0xF8) != SLAVE_ADD_RCVD_RD_REQ);
	return;
}

unsigned char i2c_slave_read_byte(void)
{
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);     // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while(!(TWCR & (1<<TWINT)));                   // Wait for TWINT flag
	while((TWSR & 0xF8) != SLAVE_DATA_RECEIVED);
	return TWDR;
}

void i2c_slave_write_byte(unsigned char byte)
{
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN);    // Clear TWI interrupt flag,Get enable acknowledgment, Enable TWI
	while(!(TWCR & (1<<TWINT)));                  // Wait for TWINT flag
	while((TWSR & 0xF8) != SLAVE_BYTE_TRANSMITTED);    // Data byte in TWDR has been transmitted
	return;
}
