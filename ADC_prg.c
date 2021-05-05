/*
 * main.c
 *
 *  Created on: Feb 28, 2020
 *      Author: high tension
 */
#include "stdtypes.h"
#include "ATMega32_Reg.h"
#include "utils.h"
#include "DIO_int.h"
#include "ADC_int.h"

//void ADC_Init(void);
//void ADC_StartConversion(u8 ChannelNum,/*u8 Adjustment*/u16 *ptr);

static void (*ADC_pf_FreeRunning)(u16 input)= NULL;

void ADC_FreeRunningSetCallBack( void (*Action_FreeRunning)(u16 Variable_has_Adc_Val) )
{
	if(Action_FreeRunning!=NULL)
	{
		ADC_pf_FreeRunning=Action_FreeRunning;
	}
}

void ADC_Init(void)
{
	clr_bit(ADMUX,7);//vref source
	set_bit(ADMUX,6);//vref source
	set_bit(ADCSRA,7);//adc enable
#if Resolution==0//right adj
	clr_bit(ADMUX,5);
#elif Resolution==1//left adj
	set_bit(ADMUX,5);
#endif
}

void ADC_Init_FreeRunning_Mode(void)
{
	clr_bit(ADMUX,7);//vref source
	set_bit(ADMUX,6);//vref source
	set_bit(ADCSRA,5);//enable auto triggering
	set_bit(ADMUX,5);//Left adjustment
	ADC_Interrupt_Enable();//Enabling Interrupt
	/* Free Running Mode */
	clr_bit(SFIOR,5);
	clr_bit(SFIOR,6);
	clr_bit(SFIOR,7);
	/* Prescaler selection */
	set_bit(ADCSRA,0);
	set_bit(ADCSRA,1);
	set_bit(ADCSRA,2);
}
void ADC_Enable(void)
{
	/* Use it After selecting the ADC Channel */
	set_bit(ADCSRA,7);
	ADC_StartConversion();
}
void ADC_Dsiable(void)
{
	clr_bit(ADCSRA,7);
}
void ADC_StartConversion(void)
{
	set_bit(ADCSRA,6);
}

void ADC_Interrupt_Enable(void)
{
	/* Don't Forget Global interrupt Enable */
	set_bit(ADCSRA,3);
}
void ADC_Interrupt_Disable(void)
{
	clr_bit(ADCSRA,3);
}
void __vector_16(void)
{
	u16 Result = ADCH;//3shan 3mlna left adjustment
	/* ADC ISR */
	ADC_pf_FreeRunning(Result);
//	set_bit(ADCSRA,4);
}
void ADC_ChannelSelect_FreeRunning_Mode(u8 ChannelNum)
{
	switch (ChannelNum)
	{
			case ADC_Chann0:
				clr_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);


				break;
			case ADC_Chann1:
				set_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);

				break;
			case ADC_Chann2:
				clr_bit(ADMUX,0);
				set_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann3:
				set_bit(ADMUX,0);
				set_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);

				break;
			case ADC_Chann4:
				clr_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann5:
				set_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann6:
				clr_bit(ADMUX,0);
				set_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann7:
				set_bit(ADMUX,0);
				set_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
	}

}

void ADC_StartConversion_SingleMode(u8 ChannelNum,/*u8 Adjustment,*/u16 *ptr)
{
	switch (ChannelNum)
	{
			case ADC_Chann0:
				clr_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);


				break;
			case ADC_Chann1:
				set_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);

				break;
			case ADC_Chann2:
				clr_bit(ADMUX,0);
				set_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann3:
				set_bit(ADMUX,0);
				set_bit(ADMUX,1);
				clr_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);

				break;
			case ADC_Chann4:
				clr_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann5:
				set_bit(ADMUX,0);
				clr_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann6:
				clr_bit(ADMUX,0);
				set_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
			case ADC_Chann7:
				set_bit(ADMUX,0);
				set_bit(ADMUX,1);
				set_bit(ADMUX,2);
				clr_bit(ADMUX,3);
				clr_bit(ADMUX,4);
				break;
	}
/*	switch (Adjustment)
	{
		case AdjRight://10bit
			clr_bit(ADMUX,5);
			break;
		case AdjLeft://8bit
			set_bit(ADMUX,5);
			break;
	}
*/
	set_bit(ADCSRA,6);//starting conversion
	while(!get_bit(ADCSRA,4));
	set_bit(ADCSRA,4);
#if Resolution==0
	*ptr=ADCL;//10bit Resolution
#elif Resolution==1
	*ptr=ADCH;//8bit Resolution

#endif
}
