/************************************************************/
/********************* Author : Karim Hassan ****************/
/********************* Data   : 26/6/2020    ****************/
/********************* Driver : Global Interrupt    *********/
/********************* Version: 1.0          ****************/
/************************************************************/
#include "stdtypes.h"
#include "utils.h"

#include "GI_interface.h"

#define SREG       *((volatile u8 *)0x5F)

void GI_voidGlobalIntEnable(void)
{
	set_bit(SREG,7);
}

void GI_voidGlobalIntDisable(void)
{
	clr_bit(SREG,7);
}