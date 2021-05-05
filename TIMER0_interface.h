
#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

/* Desired Time(ms) OPTS
 0
 Any number of milliseconds
 */
#define Desired_TIME_0_ms  (u32)500

void TIMER0_int(void);
void TIMER1_int(void);
void TIMER0_OverFlowSetCallBack( void (*Action_CounterOverFlow)(void) );
void TIMER0_CTCSetCallBack( void (*Action_CounterCTC)(void) );
void TIMER0_FAST_PWM_DutyCycle(u8 DutyCycle_Percentage);
void TIMER0_Start(void);//8 prescaler value
void TIMER0_Stop(void);
void TIMER1_FAST_PWM_ICR1_Val (u16 Top_Value_ICR1);
void TIMER1_Stop(void);
void TIMER1_Start(void);//8 prescaler



#endif /* TIMER0_INTERFACE_H_ */
