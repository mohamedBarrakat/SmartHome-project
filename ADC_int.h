/*
 * ADC_int.h
 *
 *  Created on: Feb 28, 2020
 *      Author: high tension
 */

#ifndef ADC_INT_H_
#define ADC_INT_H_

#define ADC_Chann0 0
#define ADC_Chann1 1
#define ADC_Chann2 2
#define ADC_Chann3 3
#define ADC_Chann4 4
#define ADC_Chann5 5
#define ADC_Chann6 6
#define ADC_Chann7 7

/*0 for 10 bit 1 for 8bit*/
#define Resolution 1


void ADC_Init(void);
void ADC_StartConversion_SingleMode(u8 ChannelNum,/*u8 Adjustment,*/u16 *ptr);
void ADC_Init_FreeRunning_Mode(void);
void ADC_ChannelSelect_FreeRunning_Mode(u8 ChannelNum);
void ADC_Enable(void);
void ADC_Dsiable(void);
void ADC_StartConversion(void);
void ADC_Interrupt_Enable(void);
void ADC_Interrupt_Disable(void);
void ADC_FreeRunningSetCallBack( void (*Action_FreeRunning)(u16 Variable_has_Adc_Val) );

void __vector_16(void)     __attribute__((signal));





#endif /* ADC_INT_H_ */
