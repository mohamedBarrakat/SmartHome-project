/*
 * EEPROM_interface.h
 *
 *  Created on: Aug 20, 2020
 *      Author: high tension
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

//void EEPROM_WriteDataByte(u16 ByteAdress, u8 Data);
//void EEPROM_ReadDataByte (u16 ByteAdress, u8* Data);

void eeprom_init(void);
void eeprom_write_byte(unsigned short address, unsigned char data);
unsigned char eeprom_read_byte(unsigned short address);

#endif /* EEPROM_INTERFACE_H_ */
