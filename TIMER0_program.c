/* Libraries  */
#include "stdtypes.h"
#include "utils.h"

/* MCAL */
#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

/* Global Pointers To Function */
static void (*TIMER0_pf_OVERFLOW)(void)= NULL;
static void (*TIMER0_pf_CTC)(void)	   = NULL;
/* TIMER0 Global Variables */
 static u32 TIMER0_No_Of_OverFlows;
 static u32 TIMER0_Preload_Value;
/* TIMER0 State Flag
 Options
 Flag=1 Desired time=ovf time ~~ Flag=2 Desired time<ovf time ~~ Flag=3 Desired time > ovf time*/
static u8 TIMER0_State_Flag=0;
/* TIMER0 Init*/
#if (TIMER0_Control == TIMER0_Enable)
	void TIMER0_int(void)
	{
		u16 TIMER0_prescaler_switch;
		u16 TimeOVF0=256,TimeOVF1=2048,TimeOVF2=8192,TimeOVF3=32768;
		u32 Desired_TimeInMicroSeconds=0,Temp_PartOfOVF=0;
	/* TIMER0 Mode Selection */
	#if TIMER0_Mode == TIMER0_Normal_Mode
		clr_bit(TCCR0,3);
		clr_bit(TCCR0,6);
	#elif TIMER0_Mode == TIMER0_PWM_PhaseCorrect_Mode
		clr_bit(TCCR0,3);
		set_bit(TCCR0,6);
	#elif TIMER0_Mode == TIMER0_CTC_Mode
		set_bit(TCCR0,3);
		clr_bit(TCCR0,6);
	#elif TIMER0_Mode == TIMER0_FAST_PWM_Mode
		set_bit(TCCR0,3);
		set_bit(TCCR0,6);
		#if  (TIMER0_FAST_PWM_Mode_Selection == TIMER0_FAST_PWM_OC0_DC)
		clr_bit(TCCR0,4);
		clr_bit(TCCR0,5);
		#elif(TIMER0_FAST_PWM_Mode_Selection == TIMER0_FAST_PWM_Reversed)
		set_bit(TCCR0,4);
		clr_bit(TCCR0,5);
		#elif(TIMER0_FAST_PWM_Mode_Selection == TIMER0_FAST_PWM_CLR_OC0_On_Match)
		clr_bit(TCCR0,4);
		set_bit(TCCR0,5);
		#elif(TIMER0_FAST_PWM_Mode_Selection == TIMER0_FAST_PWM_SET_OC0_On_Match)
		set_bit(TCCR0,4);
		set_bit(TCCR0,5);
		#endif
	#endif


	/* Switch Index */
	#if (TIMER0_DesiredTime_State == TIMER0_Desired_Time_On)
		#if TIMER0_Prescaler == TIMER0_Prescale_8
			TIMER0_prescaler_switch=0;
		#elif TIMER0_Prescaler == TIMER0_Prescale_64
			TIMER0_prescaler_switch=1;
		#elif TIMER0_Prescaler == TIMER0_Prescale_256
			TIMER0_prescaler_switch=2;
		#elif TIMER0_Prescaler == TIMER0_Prescale_1024
			TIMER0_prescaler_switch=3;
		#endif

		switch(TIMER0_prescaler_switch)
			{
			case 0:if(Desired_TIME_0_ms!=0)//division by 8
					{
						//TimeOVF0=256;//microsecond
						Desired_TimeInMicroSeconds=Desired_TIME_0_ms*1000;
						if(Desired_TimeInMicroSeconds==TimeOVF0)
						{
							TIMER0_State_Flag=1;
							break;
						}else if (Desired_TimeInMicroSeconds<TimeOVF0)
						{
							TIMER0_Preload_Value=256-Desired_TimeInMicroSeconds;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=2;
						}else if(Desired_TimeInMicroSeconds>TimeOVF0)
						{
							TIMER0_No_Of_OverFlows=(Desired_TimeInMicroSeconds/TimeOVF0)+1;//3906.25
							Temp_PartOfOVF=((((Desired_TimeInMicroSeconds*100)/TimeOVF2)%100)*256)/100;
							TIMER0_Preload_Value=256-Temp_PartOfOVF;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=3;
						}
					}
				break;
			case 1:if(Desired_TIME_0_ms!=0)//division by 64
					{
						//TimeOVF0=256;//microsecond
						Desired_TimeInMicroSeconds=Desired_TIME_0_ms*1000;
						if(Desired_TimeInMicroSeconds==TimeOVF1)
						{
							TIMER0_State_Flag=1;
							break;
						}else if (Desired_TimeInMicroSeconds<TimeOVF1)
						{
							TIMER0_Preload_Value=256-Desired_TimeInMicroSeconds;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=2;
						}else if(Desired_TimeInMicroSeconds>TimeOVF1)
						{
							TIMER0_No_Of_OverFlows=(Desired_TimeInMicroSeconds/TimeOVF1)+1;
							Temp_PartOfOVF=((((Desired_TimeInMicroSeconds*100)/TimeOVF2)%100)*256)/100;
							TIMER0_Preload_Value=256-Temp_PartOfOVF;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=3;
						}
					}
				break;
			case 2:if(Desired_TIME_0_ms!=0)//division by 256
					{
						//TimeOVF0=256;//microsecond
						Desired_TimeInMicroSeconds=Desired_TIME_0_ms*1000;
						if(Desired_TimeInMicroSeconds==TimeOVF2)
						{
							TIMER0_State_Flag=1;
							break;
						}else if (Desired_TimeInMicroSeconds<TimeOVF2)
						{
							TIMER0_Preload_Value=256-Desired_TimeInMicroSeconds;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=2;
						}else if(Desired_TimeInMicroSeconds>TimeOVF2)
						{
							TIMER0_No_Of_OverFlows=(Desired_TimeInMicroSeconds/TimeOVF2)+1;
							Temp_PartOfOVF=((((Desired_TimeInMicroSeconds*100)/TimeOVF2)%100)*256)/100;
							TIMER0_Preload_Value=256-Temp_PartOfOVF;
							TCNT0=TIMER0_Preload_Value;
							TIMER0_State_Flag=3;
						}
					}
				break;
			case 3:if(Desired_TIME_0_ms!=0)//division by 1024
						{
							//TimeOVF0=256;//microsecond
							Desired_TimeInMicroSeconds=Desired_TIME_0_ms*1000;
							if(Desired_TimeInMicroSeconds==TimeOVF3)
							{
								TIMER0_State_Flag=1;
								break;
							}else if (Desired_TimeInMicroSeconds<TimeOVF3)
							{
								TIMER0_Preload_Value=256-Desired_TimeInMicroSeconds;
								TCNT0=TIMER0_Preload_Value;
								TIMER0_State_Flag=2;
							}else if(Desired_TimeInMicroSeconds>TimeOVF3)
							{
								TIMER0_No_Of_OverFlows=(Desired_TimeInMicroSeconds/TimeOVF3)+1;
								Temp_PartOfOVF=((((Desired_TimeInMicroSeconds*100)/TimeOVF2)%100)*256)/100;
								TIMER0_Preload_Value=256-Temp_PartOfOVF;
								TCNT0=TIMER0_Preload_Value;
								TIMER0_State_Flag=3;
							}
						}
				break;
			}
	#endif
		/* Enabling OverFlow Interrupt */
	#if TIMER0_OVF_INT == TIMER0_OVF_INT_ON
		set_bit(TIMSK,0);
	#elif TIMER0_OVF_INT == TIMER0_OVF_INT_OFF
		clr_bit(TIMSK,0);
	#endif
		/* Enabling CTC Interrupt */
	#if TIMER0_CTC_INT == TIMER0_CTC_INT_ON
		set_bit(TIMSK,1);
	#elif TIMER0_CTC_INT == TIMER0_CTC_INT_OFF
		clr_bit(TIMSK,1);
	#endif
	TCNT0=TIMER0_Preload_Value;
	/* Choosing Prescaler Value */
	/* Starting TIMER0 */
//	#if TIMER0_Prescaler == TIMER0_Prescale_8
//				clr_bit(TCCR0,0);
//				set_bit(TCCR0,1);
//				clr_bit(TCCR0,2);
//	#elif TIMER0_Prescaler == TIMER0_Prescale_64
//				set_bit(TCCR0,0);
//				set_bit(TCCR0,1);
//				clr_bit(TCCR0,2);
//	#elif TIMER0_Prescaler == TIMER0_Prescale_256
//				clr_bit(TCCR0,0);
//				clr_bit(TCCR0,1);
//				set_bit(TCCR0,2);
//	#elif TIMER0_Prescaler == TIMER0_Prescale_1024
//				set_bit(TCCR0,0);
//				set_bit(TCCR0,1);
//				clr_bit(TCCR0,2);
//	#endif
	}
#endif
void TIMER0_FAST_PWM_DutyCycle(u8 DutyCycle_Percentage)
{
	if(DutyCycle_Percentage==0)
	{
		OCR0=0;
	}
	else if(DutyCycle_Percentage==100)
	{
		OCR0=255;
	}
	else if(DutyCycle_Percentage==50)
	{
		OCR0 = 127;//2.55 is (10*255-TIMER0 resolution)/1000 wel 10 3shan nkbr el rkm ykon akbr mel > 1

	}
}
void TIMER0_Start(void)
{
	clr_bit(TCCR0,0);
	set_bit(TCCR0,1);
	clr_bit(TCCR0,2);
}
void TIMER0_Stop(void)
{
	clr_bit(TCCR0,0);
	clr_bit(TCCR0,1);
	clr_bit(TCCR0,2);
}
/* TIMER1 Init */
#if ( TIMER1_Control == TIMER1_Enable)
	void TIMER1_int(void)
	{
		/* TIMER1 Mode Selection */
	#if 	(TIMER1_Mode == TIMER1_Normal_Mode)//0
			clr_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_PWM_PhaseCorrect_8bit_Mode  )//1
			set_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_PWM_PhaseCorrect_9bit_Mode  )//2
			clr_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_PWM_PhaseCorrect_10bit_Mode  )//3
			set_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_CTC_Mode_OCR1A  )//4
			clr_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode ==  TIMER1_FAST_PWM_8bit_Mode )//5
			set_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode ==  TIMER1_FAST_PWM_9bit_Mode )//6
			clr_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode ==  TIMER1_FAST_PWM_10bit_Mode )//7
			set_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			clr_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode ==  TIMER1_PWM_PhaseAndFreqCorrect_Mode_ICR1 )//8
			clr_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_PWM_PhaseAndFreqCorrect_Mode_OCR1A  )//9
			set_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_PWM_PhaseCorrect_Mode_ICR1  )//10
			clr_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode ==  TIMER1_PWM_PhaseCorrect_Mode_OCR1A )//11
			set_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			clr_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_CTC_Mode_ICR1 )//12
			clr_bit(TCCR1A,0);
			clr_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
	#elif  	(TIMER1_Mode == TIMER1_FAST_PWM_Mode_ICR1 )//14
			clr_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			set_bit(TCCR1B,4);
		#if (TIMER1_Channel == TIMER1_Channel_A)
			#if  (TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_OC1_DC)
			clr_bit(TCCR1A,6);
			clr_bit(TCCR1A,7);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_Reversed)
			set_bit(TCCR1A,6);
			clr_bit(TCCR1A,7);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_CLR_OC1_On_Match)
			clr_bit(TCCR1A,6);
			set_bit(TCCR1A,7);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_SET_OC1_On_Match)
			set_bit(TCCR1A,6);
			set_bit(TCCR1A,7);
			#endif
		#elif (TIMER1_Channel == TIMER1_Channel_B)
			#if  (TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_OC1_DC)
			clr_bit(TCCR1A,4);
			clr_bit(TCCR1A,5);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_Reversed)
			set_bit(TCCR1A,4);
			clr_bit(TCCR1A,5);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_CLR_OC1_On_Match)
			clr_bit(TCCR1A,4);
			set_bit(TCCR1A,5);
			#elif(TIMER1_FAST_PWM_Mode_Selection == TIMER1_FAST_PWM_SET_OC1_On_Match)
			set_bit(TCCR1A,4);
			set_bit(TCCR1A,5);
			#endif
		#endif
	#elif  	(TIMER1_Mode == TIMER1_FAST_PWM_Mode_OCR1A )//15
			set_bit(TCCR1A,0);
			set_bit(TCCR1A,1);
			set_bit(TCCR1B,3);
			set_bit(TCCR1B,4);

	#endif

	/* Choosing Prescaler Value */
	/* Starting TIMER1 */
//	#if TIMER1_Prescaler == TIMER0_Prescale_8
//				clr_bit(TCCR1B,0);
//				set_bit(TCCR1B,1);
//				clr_bit(TCCR1B,2);
//	#elif TIMER1_Prescaler == TIMER0_Prescale_64
//				set_bit(TCCR1B,0);
//				set_bit(TCCR1B,1);
//				clr_bit(TCCR1B,2);
//	#elif TIMER1_Prescaler == TIMER0_Prescale_256
//				clr_bit(TCCR1B,0);
//				clr_bit(TCCR1B,1);
//				set_bit(TCCR1B,2);
//	#elif TIMER1_Prescaler == TIMER0_Prescale_1024
//				set_bit(TCCR1B,0);
//				clr_bit(TCCR1B,1);
//				set_bit(TCCR1B,2);
//	#endif

	}//End of TIMER1 INIT
#endif

void TIMER1_Stop(void)
{
	clr_bit(TCCR1B,0);
	clr_bit(TCCR1B,1);
	clr_bit(TCCR1B,2);
}
void TIMER1_Start(void)
{
	clr_bit(TCCR1B,0);
	set_bit(TCCR1B,1);
	clr_bit(TCCR1B,2);
}
void TIMER1_FAST_PWM_ICR1_Val (u16 Top_Value_ICR1)
{
	//Top_Value_ICR1  In Micro Seconds depends on Prescaler Value
	ICR1 = Top_Value_ICR1;
}

void TIMER0_OverFlowSetCallBack( void (*Action_CounterOverFlow)(void) )
{
	if(Action_CounterOverFlow!=NULL)
	{
		TIMER0_pf_OVERFLOW=Action_CounterOverFlow;
	}
}
void TIMER0_CTCSetCallBack( void (*Action_CounterCTC)(void) )
{
	if(Action_CounterCTC!=NULL)
	{
		TIMER0_pf_CTC=Action_CounterCTC;
	}
}

//void __vector_11(void)
//{
//	static u16 Local_u16_OVF_ISR_counter=0;
//	 // Local_u16_OVF_ISR_counter++;
//	if( (TIMER0_State_Flag==1) && (TIMER0_pf_OVERFLOW!=NULL) )
//	{
//		TIMER0_pf_OVERFLOW();
//	}
//	else if( (TIMER0_State_Flag==2) && (TIMER0_pf_OVERFLOW!=NULL) )
//	{
//		TCNT0=TIMER0_Preload_Value;
//		TIMER0_pf_OVERFLOW();
//	}
//	else if( (TIMER0_State_Flag==3) && (TIMER0_pf_OVERFLOW!=NULL) )
//	{
//		Local_u16_OVF_ISR_counter++;
//		if (Local_u16_OVF_ISR_counter==TIMER0_No_Of_OverFlows)
//		{
//			TCNT0=TIMER0_Preload_Value;
//			Local_u16_OVF_ISR_counter=0;
//			TIMER0_pf_OVERFLOW();
//		}
//
//	}
//}

//void __vector_10(void)
//{
//	if(TIMER0_pf_CTC!=NULL)
//	{
//		TIMER0_pf_CTC();
//	}
//}
