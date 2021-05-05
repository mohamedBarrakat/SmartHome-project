#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* TIMER0 Registers */
#define TCCR0			*((volatile u8*)0x53)
#define TCNT0			*((volatile u8*)0x52)
#define OCR0			*((volatile u8*)0x5C)
#define TIMSK			*((volatile u8*)0x59)
#define TIFR			*((volatile u8*)0x58)

/* TIMER1 Registers */
#define TCCR1A			*((volatile u8*)0x4f)
#define TCCR1B			*((volatile u8*)0x4E)
#define TCNT1L			*((volatile u8*)0x4C)
#define TCNT1H			*((volatile u8*)0x4D)
#define TCNT1			*((volatile u16*)0x4C)
#define OCR1AL			*((volatile u8*)0x4A)
#define OCR1AH			*((volatile u8*)0x4B)
#define OCR1A			*((volatile u16*)0x4A)
#define OCR1BL			*((volatile u8*)0x48)
#define OCR1BH			*((volatile u8*)0x49)
#define OCR1B			*((volatile u16*)0x48)
#define ICR1L			*((volatile u8*)0x46)
#define ICR1H			*((volatile u8*)0x47)
#define ICR1			*((volatile u16*)0x46)

/* Enabling/Disabling TIMERS */
#define TIMER0_Enable						 1
#define TIMER1_Enable						 1
#define TIMER0_Disable						 0
#define TIMER1_Disable						 0

/* TIMER0 Modes */
#define TIMER0_Normal_Mode  				 0
#define TIMER0_CTC_Mode     				 1
#define TIMER0_PWM_PhaseCorrect_Mode		 2
#define TIMER0_FAST_PWM_Mode				 3

/* TIMER0 Fast PWM Modes */
#define TIMER0_FAST_PWM_OC0_DC 				 0
#define TIMER0_FAST_PWM_Reversed			 1
#define TIMER0_FAST_PWM_CLR_OC0_On_Match	 2
#define TIMER0_FAST_PWM_SET_OC0_On_Match	 3

/* TIMER1 Modes */
#define TIMER1_Normal_Mode					           0
#define TIMER1_PWM_PhaseCorrect_8bit_Mode	           1
#define TIMER1_PWM_PhaseCorrect_9bit_Mode              2
#define TIMER1_PWM_PhaseCorrect_10bit_Mode             3
#define TIMER1_CTC_Mode_OCR1A					 	   4
#define TIMER1_FAST_PWM_8bit_Mode	                   5
#define TIMER1_FAST_PWM_9bit_Mode	                   6
#define TIMER1_FAST_PWM_10bit_Mode	                   7
#define TIMER1_PWM_PhaseAndFreqCorrect_Mode_ICR1	   8
#define TIMER1_PWM_PhaseAndFreqCorrect_Mode_OCR1A      9
#define TIMER1_PWM_PhaseCorrect_Mode_ICR1             10
#define TIMER1_PWM_PhaseCorrect_Mode_OCR1A            11
#define TIMER1_CTC_Mode_ICR1					 	  12
#define TIMER1_FAST_PWM_Mode_ICR1					  14
#define TIMER1_FAST_PWM_Mode_OCR1A					  15

/* TIMER1 Fast PWM Modes */
#define TIMER1_FAST_PWM_OC1_DC 				 0
#define TIMER1_FAST_PWM_Reversed			 1
#define TIMER1_FAST_PWM_CLR_OC1_On_Match	 2
#define TIMER1_FAST_PWM_SET_OC1_On_Match	 3
/* TIMER1 Channel Selection */
#define TIMER1_Channel_A			     0
#define TIMER1_Channel_B		         1

/* TIMER0 Prescaler Value */
//#define TIMER0_Prescale_1	 	  1
#define TIMER0_Prescale_8	 	  1
#define TIMER0_Prescale_64	 	  2
#define TIMER0_Prescale_256	 	  3
#define TIMER0_Prescale_1024 	  4

/* TIMER1 Prescaler Value */
#define TIMER1_Prescale_8	 	  1
#define TIMER1_Prescale_64	 	  2
#define TIMER1_Prescale_256	 	  3
#define TIMER1_Prescale_1024 	  4

/* TIMER0 Interrupts */
#define TIMER0_OVF_INT_OFF  0
#define TIMER0_OVF_INT_ON   1
#define TIMER0_CTC_INT_OFF  0
#define TIMER0_CTC_INT_ON   1

/* TIMER0 Desired Time Options  */
#define TIMER0_Desired_Time_On		1
#define TIMER0_Desired_Time_Off    	0


/* TIMER0 ISR */
//void __vector_10(void)     __attribute__((signal));//CTC
//void __vector_11(void)     __attribute__((signal));//OVF
/* TIMER1 ISR */
void __vector_9(void)     __attribute__((signal));//TIMER1 OVF


#endif /* TIMER0_PRIVATE_H_ */
