//#include "stdtypes.h"
//#include "utils.h"
//#define F_CPU 8000000UL
//#include <util/delay.h>
//
//#include "I2C_interface.h"
//
//#include "EEPROM_interface.h"
//#include "EEPROM_private.h"
//#include "EEPROM_config.h"
//
//
//
//void EEPROM_WriteDataByte(u16 ByteAdress, u8 Data)
//{	/* Local Variable To configure Slave Adress */
//	u8 Local_Variable;
//	/* Should be a variable that receive the return state of the start condition function  */
//	I2C_SendStartCondition();
//	Local_Variable = (EEPROM_Fixed_Address)|(EEPROM__u8_A2_Value<<2)|((ByteAdress>>8)&3);
//	/* Send Slave  Adress With Write */
//	I2C_SendSlaveAdressWithWrite(Local_Variable);
//	I2C_SendDataByteMASTER((u8)ByteAdress);
//	I2C_SendDataByteMASTER(Data);
//	I2C_SendStopCondition();
//	_delay_ms(10);
//}
//
//void EEPROM_ReadDataByte (u16 ByteAdress, u8* Data)
//{
//	if (Data !=NULL)
//	{
//		/* Local Variable To configure Slave Adress */
//		u8 Local_Variable;
//		/* Should be a variable that receive the return state of the start condition function  */
//		I2C_SendStartCondition();
//		Local_Variable = (EEPROM_Fixed_Address)|(EEPROM__u8_A2_Value<<2)|((ByteAdress>>8)&3);
//		/* Send Slave  Adress With Write */
//		I2C_SendSlaveAdressWithWrite(Local_Variable);
//		/* Sending the Rest of the Data Byte */
//		I2C_SendDataByteMASTER((u8)ByteAdress);
//		/* Repeated start condition */
//		I2C_SendRepeatedStart();
//		/* Send slave adress with read */
//		I2C_SendSlaveAdressWithRead(Local_Variable);
//		/* Reading Data */
//		I2C_ReadDataByteMASTER(Data);
//
//		I2C_SendStopCondition();
//		_delay_ms(10);
//	}
//}
#include "I2C_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"
//#include "eeprom.h"
//#include "I2C.h"

void eeprom_init(void)
{
	i2c_init_master();
}

void eeprom_write_byte(unsigned short address, unsigned char data)
{
//	Write_data('2');
    i2c_start();
//    Write_data('3');
	i2c_send_slave_address_with_write_req( 0x50 | ((address & 0x0700)>>8) );
//    i2c_send_slave_address_with_write_req( 0b10100000 );

	/*
	1010000

	0000000001100100 &
	0000011100000000

	0000000000000000		-00000000
	0000000001010000  |
	10100000
	*/
	i2c_write_byte((unsigned char)address);
//	Write_data('9');
	i2c_write_byte(data);
//	Write_data('A');
	i2c_stop();
//	Write_data('B');
    return;
}

unsigned char eeprom_read_byte(unsigned short address)
{
	unsigned char data;
	i2c_start();
	i2c_send_slave_address_with_write_req( 0x50 | ((address & 0x0700)>>8) );
//	i2c_send_slave_address_with_write_req( 0b10100000 );
    i2c_write_byte((unsigned char)address);
	i2c_repeated_start();
	i2c_send_slave_address_with_read_req( 0x50 | ((address & 0x0700)>>8) );
//	i2c_send_slave_address_with_read_req( 0b10100001 );
	data = i2c_read_byte();
	i2c_stop();
    return data;
}

