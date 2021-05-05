#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

/* Enabling/Disabling TIMER0/TIMER1 Options
TIMER0_Enable
TIMER1_Enable
TIMER0_Disable
TIMER1_Disable
*/
#define TIMER0_Control		TIMER0_Enable
#define TIMER1_Control		TIMER1_Enable

/* TIMER0 Modes OPTS */
/* TIMER0_Normal_Mode
   TIMER0_CTC_Mode
   TIMER0_PWM_PhaseCorrect_Mode
   TIMER0_FAST_PWM_Mode
*/
#define TIMER0_Mode 		TIMER0_FAST_PWM_Mode

/* FAST PWM Modes
TIMER0_FAST_PWM_OC0_DC
TIMER0_FAST_PWM_Reversed
TIMER0_FAST_PWM_CLR_OC0_On_Match
TIMER0_FAST_PWM_SET_OC0_On_Match
*/
#define TIMER0_FAST_PWM_Mode_Selection   TIMER0_FAST_PWM_CLR_OC0_On_Match

/* TIMER0 Prescaler Value OPTS
TIMER0_Prescale_1
TIMER0_Prescale_8
TIMER0_Prescale_64
TIMER0_Prescale_256
TIMER0_Prescale_1024
*/
#define TIMER0_Prescaler 	TIMER0_Prescale_8

/* TIMER1 Prescaler Value OPTS
TIMER0_Prescale_1
TIMER0_Prescale_8
TIMER0_Prescale_64
TIMER0_Prescale_256
TIMER0_Prescale_1024
*/
#define TIMER1_Prescaler 	TIMER0_Prescale_8

/* Enable TIMER0 Interrupts
 * Options
 TIMER0_OVF_INT_OFF
 TIMER0_OVF_INT_ON
 TIMER0_CTC_INT_OFF
 TIMER0_CTC_INT_ON
 */
#define TIMER0_OVF_INT      TIMER0_OVF_INT_OFF
#define TIMER0_CTC_INT 		TIMER0_CTC_INT_OFF

/* TIMER0 Desired Time Options
 * TIMER0_Desired_Time_On
 * TIMER0_Desired_Time_Off
 */
#define TIMER0_DesiredTime_State TIMER0_Desired_Time_Off

/* TIMER1 Mode Selection Options
TIMER1_Normal_Mode
TIMER1_PWM_PhaseCorrect_8bit_Mode
TIMER1_PWM_PhaseCorrect_9bit_Mode
TIMER1_PWM_PhaseCorrect_10bit_Mode
TIMER1_CTC_Mode_OCR1A
TIMER1_FAST_PWM_8bit_Mode
TIMER1_FAST_PWM_9bit_Mode
TIMER1_FAST_PWM_10bit_Mode
TIMER1_PWM_PhaseAndFreqCorrect_Mode_ICR1
TIMER1_PWM_PhaseAndFreqCorrect_Mode_OCR1A
TIMER1_PWM_PhaseCorrect_Mode_ICR1
TIMER1_PWM_PhaseCorrect_Mode_OCR1A
TIMER1_CTC_Mode_ICR1
TIMER1_FAST_PWM_Mode_ICR1
TIMER1_FAST_PWM_Mode_OCR1A
*/
#define TIMER1_Mode 		TIMER1_FAST_PWM_Mode_ICR1

/* FAST PWM Modes
TIMER1_FAST_PWM_OC1_DC
TIMER1_FAST_PWM_Reversed
TIMER1_FAST_PWM_CLR_OC1_On_Match
TIMER1_FAST_PWM_SET_OC1_On_Match
*/
#define TIMER1_FAST_PWM_Mode_Selection   TIMER1_FAST_PWM_CLR_OC1_On_Match
/* TIMER1 Action - TIMER1 Channel Selection
TIMER1_Channel_A
TIMER1_Channel_B
*/
#define TIMER1_Channel						TIMER1_Channel_A

#endif /* TIMER0_CONFIG_H_ */
