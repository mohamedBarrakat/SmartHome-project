
#define F_CPU 8000000UL
#include "stdtypes.h"
#include "utils.h"
#include "util/delay.h"
#include "ATMega32_Reg.h"
#include "DIO_int.h"
#include "LCD_int.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "I2C_interface.h"
#include "EEPROM_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_interface.h"
#include "TIMER0_config.h"
#include "GI_interface.h"
#include "ADC_int.h"

/* Global Variables */
u8 Temperature,Desired_Temp,TimeOut_Counter,Delete_User_Global_Return=0;

/* Global-Purpose Functions*/
void ASCII_Conversion(u8 *Data);
void Admin_Mode(void);
void User_Mode(void);
void Recovering_Addresses_Location(void);
void Recovering_Users_Status(void);
void Right_Arrow(void);
void Left_Arrow(void);
void Celsius_Sym(void);
void User_ADC_ISR(u16 temp);
void Time_Out_Function(void);
/* Admin's Functions */
//void Admin_Add_User(void);
//void Admin_Delete_User(void);
void Add_User(void);
void Delete_User(void);
void Save_User_Password(u8 User_index);
void Delete_Registered_User(u8 User_index);
u8 Enter_Admin_Pass(void);
/* User's Functions */
u8 User_Validation(u8 User_ID);
void User_DoorControl(void);
void User_AC_Control(void);
void User_Light_Control(void);



/* Global Addresses Array */
u8 Array_Of_Addresses_Location[10]={0};
u8 Array_Of_User_Status[10]={0};


void main(void)
{
	LCD_init();
	UART_init();
	eeprom_init();
	/* Light Pin Output */
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);
	/* LCD BackLight Controlable PIN */
	DIO_u8SetPinDir(DIO_PORTC,DIO_PIN6,DIO_OUTPUT);
	DIO_u8SetPinDir(DIO_PORTB,DIO_PIN3,DIO_OUTPUT);//PWM output for Timer0
	/* Door Control PWM TIMER1 */
	DIO_u8SetPinDir(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);//OCR1 Pin Output
	TIMER1_FAST_PWM_ICR1_Val(19999);//Top Limit 20000 ms for servo pulse
	TIMER1_int();
	TIMER0_int();
	/* Initializing arrays value */
	Recovering_Addresses_Location();
	Recovering_Users_Status();
	u8 User_Choice,exit_flag=0,Connect_DC_ExitFlag=0,Connect_DC_input;
	while(1)
	{
		/* LCD's Back Light Turned off */
		DIO_u8SetPinVal(DIO_PORTC,DIO_PIN6,DIO_LOW);
		while(Connect_DC_ExitFlag==0)
		{
			LCD_CLR();
			Connect_DC_input = UART_u8Receiver();
			if(Connect_DC_input=='x')
			{
				LCD_CLR();
				Connect_DC_ExitFlag=1;
				DIO_u8SetPinVal(DIO_PORTC,DIO_PIN6,DIO_HIGH);
//				 Bluetooth_SendString("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Connected To your House");
				LCD_WriteString("Connected!");
				_delay_ms(1000);
			}
		}
		/* Restting Connecting Flag */
		Connect_DC_ExitFlag=0;
		while(exit_flag==0)
		{
			Bluetooth_SendString("\n--------------------\n");
			Bluetooth_SendString("1)Admin Mode\n2)User Mode\n3)Disconnect");
			LCD_CLR();
			LCD_WriteString("1)Admin 2)User");
			LCD_goto(0,1);
			LCD_WriteString("3)Disconnect");
			User_Choice=UART_u8Receiver();
			ASCII_Conversion(&User_Choice);
					switch (User_Choice)
					{
						case 1:LCD_CLR();
							   Admin_Mode();
							   Delete_User_Global_Return=0;
							   break;
						case 2:LCD_CLR();
							   User_Mode();
							   break;

						case 3:LCD_CLR();
							   exit_flag=1;
							   Bluetooth_SendString("\n--------------------\n");
							   Bluetooth_SendString("Disconnected!");
							   LCD_WriteString("Disconnected!");
							   _delay_ms(1000);
							   break;
					}
		}
		/* Resetting main application menue flag */
		exit_flag=0;
	}
}
void ASCII_Conversion(u8 *Data)
{
	*Data-=48;
}

void Admin_Mode(void)
{
		 u8 Admin_input,Admin_Pass[4]={1,2,3,4},User_Pass_Input[4]={0},counter=0,i,flag=0;
		 u8 Admin_Menu_Exit_Flag=1;//TimeOut_Counter;
		 u8 Admin_Max_Trial_counter=0;//for maximum trial of password of3 times
		 Bluetooth_SendString("\nEnter Admin Password\n");
		 LCD_WriteString("Enter Admin Pass");
		 LCD_goto(5,1);
		 /* Add a loop for time out 5 seconds */
		 while(Admin_Max_Trial_counter<=3)
		 {
			 while(counter<=3)
			 {

				 Admin_input = UART_u8Receiver();
				 ASCII_Conversion(&Admin_input);
				if(Admin_input !=0)
				{
					if( (Admin_input<10) && (counter <=3) )
						{
							User_Pass_Input[counter]=Admin_input;
							Write_data('0'+User_Pass_Input[counter] );
							counter++;
							Admin_input=0;
						}
				}
			 }
			 _delay_ms(500);
			 if(counter == 4)
			 {
				 for(i=0;i<=3;i++)
				 {
					 if (Admin_Pass[i]==User_Pass_Input[i])
					 {
						 continue;
					 }
					 else
					 {
						 flag=1;
					 }
				 }
			 }
			 if(flag==1)
			 {
				 LCD_CLR();
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Wrong Pass");
				 LCD_WriteString("Wrong Pass");
				 flag=0;
				 counter=0;//to reset the array
				 Admin_Max_Trial_counter++;
				 _delay_ms(2500);
				 LCD_CLR();
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Enter Your Pass");
				 LCD_WriteString("Enter Your Pass");
				 LCD_goto(5,1);

			 }
			 else
			 {
				 Admin_Max_Trial_counter=4;
			 }
			 if (Admin_Max_Trial_counter==3)
			 {
				 /* for loop i=60;i>=0;i-- with delay 1 second */
				 LCD_CLR();
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Time out");
				 LCD_WriteString("Time Out");
				 _delay_ms(1000);
				 Time_Out_Function();
				 Admin_Menu_Exit_Flag=0;
				 Admin_Max_Trial_counter=4;
			 }
		 }
	LCD_CLR();
	while(Admin_Menu_Exit_Flag==1)
	{
		if(Delete_User_Global_Return==1)
		{
			break;
		}
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("1)Add User\n2)Delete User\n3)Back");
		LCD_WriteString("In Admin Mode");
		_delay_ms(1000);
		LCD_CLR();
		LCD_WriteString("1)Add User");
		LCD_goto(0,1);
		LCD_WriteString("2)Delete User");
		Admin_input = UART_u8Receiver();
		ASCII_Conversion(&Admin_input);
		//Add while loop here
		switch(Admin_input)
			{
				case 1:Add_User();
					break;
				case 2:Delete_User();
					break;
				case 3:Admin_Menu_Exit_Flag=0;
					break;
			}
	}
}

void User_Mode(void)
{
	u8 User_Input,User_Index,User_ID_ExitFlag=0,Validation_State;//1 registered 0 non registered
	u8 Wrong_Entry_Flag=0,User_MainMenu_ExitFlag=0,User_MainMenu_Input,For_Counter,List_Counter=0;
	for(For_Counter=0;For_Counter<10;For_Counter++)
	{
		if(Array_Of_User_Status[For_Counter]==1)
		{
			List_Counter++;
		}
	}
	if(List_Counter==10)
	{
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("No Users Registered");
		LCD_WriteString("No Users");
		_delay_ms(1000);
	}
	if(List_Counter!=10)
	{
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("In User Mode");
		LCD_WriteString("In User Mode");
		_delay_ms(1000);
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("Choose User\n From 1 to 10\nEnter ID\n3)Enter");
		LCD_WriteString("Choose User");
		LCD_goto(0,1);
		LCD_WriteString("From 1 to 10");
		_delay_ms(1000);
		while(User_ID_ExitFlag==0)
		{
			LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Your ID:");
			LCD_WriteString("Your ID:");
			User_Input = UART_u8Receiver();
			ASCII_Conversion(&User_Input);
			Bluetooth_SendNumber(User_Input);
			LCD_PrintNum(User_Input);
			if(User_Input == 1)
			{
				User_Input = UART_u8Receiver();
				ASCII_Conversion(&User_Input);
				if(User_Input == 0)
				{
					Bluetooth_SendNumber(User_Input);
					LCD_PrintNum(User_Input);
					User_Index = 10;
					while(Wrong_Entry_Flag==0)
					{
						User_Input = UART_u8Receiver();
						ASCII_Conversion(&User_Input);
						if(User_Input==3)
						{
							User_ID_ExitFlag=1;
							Wrong_Entry_Flag=1;
	//						break;
						}
						else
						{
							LCD_CLR();
							 Bluetooth_SendString("\n--------------------\n");
							 Bluetooth_SendString("Wrong Entry");
							LCD_WriteString("Wrong Entry");
							_delay_ms(1000);
							LCD_CLR();
							 Bluetooth_SendString("\n--------------------\n");
							 Bluetooth_SendString("Your ID:");
							LCD_WriteString("Your ID:");
							LCD_PrintNum(User_Index);
						}
					}
					break;
				}
				else if(User_Input == 3)
				{
					User_Index = 1;
					User_ID_ExitFlag=1;
					break;
				}

			}


			User_Index = User_Input;
			User_Input = UART_u8Receiver();
			ASCII_Conversion(&User_Input);
			if(User_Input==3)
			{
				User_ID_ExitFlag=1;
				break;
			}
			else
			{
				while(Wrong_Entry_Flag==0)
				{
					LCD_CLR();
					 Bluetooth_SendString("\n--------------------\n");
					 Bluetooth_SendString("Wrong Entry");
					LCD_WriteString("Wrong Entry");
					_delay_ms(1000);
					LCD_CLR();
					 Bluetooth_SendString("\n--------------------\n");
					 Bluetooth_SendString("Your ID:");
					LCD_WriteString("Your ID:");
					Bluetooth_SendNumber(User_Index);
					LCD_PrintNum(User_Index);
					User_Input = UART_u8Receiver();
					ASCII_Conversion(&User_Input);
					if(User_Input==3)
					{
						Wrong_Entry_Flag=1;
						User_ID_ExitFlag=1;
					}
		//			break;
				}
				break;
			}
		}
		if(User_ID_ExitFlag==1)
		{
			/* USER VALIDATION */
			Validation_State=User_Validation(User_Index);
			if(Validation_State == 1)
			{
				LCD_CLR();
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Welcome!");
				LCD_WriteString("Welcome!");
				_delay_ms(1000);

				while(User_MainMenu_ExitFlag==0)
				{
					LCD_CLR();
					 Bluetooth_SendString("\n--------------------\n");
					 Bluetooth_SendString("1)Door Control\n2)A/C Control\n3)Light\n4)Back");
					LCD_WriteString("1)Door 2)A/C");
					LCD_goto(0,1);
					LCD_WriteString("3)Light");
					User_MainMenu_Input = UART_u8Receiver();
					ASCII_Conversion(&User_MainMenu_Input);
					switch(User_MainMenu_Input)
						{
						case 1:User_DoorControl();
							break;
						case 2:User_AC_Control();
							break;
						case 3:User_Light_Control();
							break;
						case 4:User_MainMenu_ExitFlag=1;
							break;
						}
					/* User Main Menu */
				}
			}

		}
	}
}
void Time_Out_Function(void)
{
	LCD_CLR();
	LCD_WriteString("Time Out For:");
	for (TimeOut_Counter=5;TimeOut_Counter>0;TimeOut_Counter--)
	{

		LCD_goto(14,0);
		LCD_PrintNum(TimeOut_Counter);
		Bluetooth_SendString("\n--------------------\n");
		Bluetooth_SendString("Time Out For:");
		Bluetooth_SendNumber(TimeOut_Counter);
		_delay_ms(1000);
	}
}
u8 User_Validation(u8 User_ID)
{
	LCD_CLR();
	//u8 TimeOut_Counter;
	u8 User_Pass_Location_Reader,User_Pass_Input[4]={0},Counter=0,Local_input,i;
	u8 Correct_Pass_Counter=0,Login_Success=0,Maximum_Trial=0,Local_EEPROM_Reader;

	User_Pass_Location_Reader = Array_Of_Addresses_Location[User_ID-1];

	if(Array_Of_User_Status[User_ID-1]==2)//registered user
	{
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("User Found");
		LCD_WriteString("User Found");
		_delay_ms(1000);
			/* WHILE LOOP FOR MAXIMUM TRIAL */
		while(Maximum_Trial<3)
		{
			LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Enter Your Password");
			LCD_WriteString("Enter Your Pass");
			LCD_goto(5,1);//to wrtie in the center
			while(Counter<=3)
				 {
					Local_input = UART_u8Receiver();
					ASCII_Conversion(&Local_input);
					User_Pass_Input[Counter]=Local_input;
					LCD_PrintNum(User_Pass_Input[Counter]);
					Counter++;
				 }
			_delay_ms(1000);
			for(i=0;i<4;i++)
				{
					Local_EEPROM_Reader = eeprom_read_byte(User_Pass_Location_Reader+i);
					_delay_ms(50);
					if (User_Pass_Input[i]==Local_EEPROM_Reader)
					{
						Correct_Pass_Counter++;//=4 means you entered a correct password
					}
				}
			if(Correct_Pass_Counter==4)
			{
				Login_Success=1;
				break;
			}
			else
			{
				Login_Success=0;
				Correct_Pass_Counter=0;
				Counter=0;
				Maximum_Trial++;
				LCD_CLR();
				 Bluetooth_SendString("\n--------------------\n");
				 Bluetooth_SendString("Wrong Pass");
				LCD_WriteString("Wrong Pass");
				LCD_goto(5,1);
				LCD_PrintNum(Maximum_Trial);
				 Bluetooth_SendString("\n--------------------\n");
				Bluetooth_SendNumber(Maximum_Trial);
				 Bluetooth_SendString("/3");
				LCD_WriteString("/3");
				_delay_ms(1000);
			}
		}
		if(Login_Success==1)
		{
			LCD_CLR();
			/* ADD HERE USER TASKS*/
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Loging Success");
			LCD_WriteString("Login Success");
			_delay_ms(1000);
			return 1;
		}
		else if (Login_Success==0 && Maximum_Trial==3)
		{
			LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Timed Out");
			LCD_WriteString("Timed Out");
			_delay_ms(1000);
	        Time_Out_Function();
			return 0;
		}
	}
	else//unregistered user
	{
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("User Not Found");
		LCD_WriteString("User not Found");
		_delay_ms(1000);
		return 0;
	}
}
/* Graduation Project Door Open/Close */
void User_DoorControl(void)
{
	u8 User_DoorInput,User_Door_ExitFlag=0;
	LCD_CLR();
	 Bluetooth_SendString("\n--------------------\n");
	 Bluetooth_SendString("1)Open\n2)Close\n3)Back");
	LCD_WriteString("1)Open");
	LCD_goto(0,1);
	LCD_WriteString("2)Close");
	/* While here*/
	while(User_Door_ExitFlag==0)
	{
		User_DoorInput = UART_u8Receiver();
		ASCII_Conversion(&User_DoorInput);
		if(User_DoorInput==1)
		{
			TIMER1_Start();
			OCR1A=2600;//180 angle
			_delay_ms(1000);
			TIMER1_Stop();
		}
		else if(User_DoorInput==2)
		{
			TIMER1_Start();
			OCR1A=580;//0 angle
			_delay_ms(1000);
			TIMER1_Stop();
		}
		else if(User_DoorInput==3)
		{
			User_Door_ExitFlag=1;
		}
	}
}
void User_Light_Control(void)
{
	u8 User_Ligh_Input,User_Light_ExitFlag=0;
	LCD_CLR();
	Bluetooth_SendString("\n--------------------\n");
	Bluetooth_SendString("1)Turn on Light\n2)Turn off Light\n3)Back");
	LCD_WriteString("1)Turn on");
	LCD_goto(0,1);
	LCD_WriteString("2)Turn off");
	while(User_Light_ExitFlag==0)
	{
		User_Ligh_Input=UART_u8Receiver();
		ASCII_Conversion(&User_Ligh_Input);
		if(User_Ligh_Input==1)
		{
			DIO_u8SetPinVal(DIO_PORTC,DIO_PIN7,DIO_HIGH);
		}
		else if(User_Ligh_Input==2)
		{
			DIO_u8SetPinVal(DIO_PORTC,DIO_PIN7,DIO_LOW);
		}
		else if(User_Ligh_Input==3)
		{
			User_Light_ExitFlag=1;
		}
	}

}
void User_AC_Control(void)
{
	static u8 User_AC_State_Flag=0;/*0 Off - 1 On*/
	u8 User_AC_Exit_Flag=0;
	u8 User_AC_Input,User_Edit_Temp=23,User_Edit_Looper=0;
	u16 User_Ac_Current_Temp;
	while(User_AC_Exit_Flag==0)
	{
		if (User_AC_State_Flag==0)//ac is off flag = 0
		{
			LCD_CLR();
			Bluetooth_SendString("\n--------------------\n");
			Bluetooth_SendString("1)Turn on AC\n2)Back");
			LCD_WriteString("1)Turn on AC");
			LCD_goto(0,1);
			LCD_WriteString("2)Back");
			User_AC_Input = UART_u8Receiver();
			ASCII_Conversion(&User_AC_Input);
			switch(User_AC_Input)
			{
				case 1:LCD_CLR();
					   ADC_Init();
					   Bluetooth_SendString("\n--------------------\n");
					   Bluetooth_SendString("Room Temp:");
					   LCD_WriteString("Room Temp:");
					   ADC_StartConversion_SingleMode(ADC_Chann0,&User_Ac_Current_Temp);
					   Bluetooth_SendNumber(User_Ac_Current_Temp);
					   LCD_PrintNum(User_Ac_Current_Temp);
					   Celsius_Sym();
					   Bluetooth_SendString("\n--------------------\n");
					   Bluetooth_SendString("Edit Temperature\n1)Increase temp\n2)Decrease temp\n3)Enter");
					   //while for edit temp until enter is pressed
					   while(User_Edit_Looper==0)
					   {
						   LCD_goto(0,1);
							 Bluetooth_SendString("\n--------------------\n");
							 Bluetooth_SendString("Desired Temp:<");
							 Bluetooth_SendNumber(User_Edit_Temp);
							 Bluetooth_SendString(">");
						   LCD_WriteString("Edit Temp:");
						   Left_Arrow();
						   LCD_PrintNum(User_Edit_Temp);
						   Right_Arrow();
						   Celsius_Sym();
						   User_AC_Input = UART_u8Receiver();
						   ASCII_Conversion(&User_AC_Input);
						   if(User_AC_Input==1)//-temp
						   {
							   if(User_Edit_Temp<=27)
							   {
								   User_Edit_Temp++;
								   Desired_Temp = User_Edit_Temp;
							   }
						   }
						   else if(User_AC_Input==2)//+temp
						   {
							   if(User_Edit_Temp>=18)
							   {
								   User_Edit_Temp--;
								   Desired_Temp = User_Edit_Temp;
							   }
						   }
						   else if(User_AC_Input==3)//enter
						   {
							   //start ADC here and Exit edit looper flag
								ADC_FreeRunningSetCallBack(User_ADC_ISR);
								GI_voidGlobalIntEnable();
								ADC_Init_FreeRunning_Mode();
								ADC_ChannelSelect_FreeRunning_Mode(ADC_Chann0);
								//send isr by setcallback function
								TIMER0_Start();
								ADC_Enable();
								User_Edit_Looper = 1;
								User_AC_State_Flag = 1;
						   }
					   }
					   User_Edit_Looper = 0;
						break;
				case 2:User_AC_Exit_Flag=1;
					break;
			}

		}
		else//ac is on flag = 1
		{
			LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("1)Turn off AC\n2)Edit temp\n3)Back");
			LCD_WriteString("1)Turn off AC");
			LCD_goto(0,1);
			LCD_WriteString("2)Edit    3)Back");
			User_AC_Input = UART_u8Receiver();
			ASCII_Conversion(&User_AC_Input);
			switch(User_AC_Input)
			{
			case 1:_delay_ms(50);
					ADC_Dsiable();
					TIMER0_FAST_PWM_DutyCycle(0);
					_delay_ms(50);
				   TIMER0_Stop();
				   LCD_CLR();
					 Bluetooth_SendString("\n--------------------\n");
					 Bluetooth_SendString("AC Turned Off");
				   LCD_WriteString("AC Turned Off");
				   _delay_ms(1000);
				   User_AC_State_Flag = 0;
				break;
			case 2:LCD_CLR();
				   Bluetooth_SendString("\n--------------------\n");
				   Bluetooth_SendString("Room Temp:");
				   Bluetooth_SendNumber(Temperature);
			       LCD_WriteString("Room Temp:");
			       LCD_PrintNum(Temperature);
			       Celsius_Sym();
				   Bluetooth_SendString("\n--------------------\n");
				   Bluetooth_SendString("Edit temp\n1)Increase temp\n2)Decrease temp\n3)Enter");
				   while(User_Edit_Looper==0)
				   {
					   LCD_goto(0,1);
					   LCD_WriteString("Edit Temp:<");
					   Bluetooth_SendString("\n--------------------\n");
					   Bluetooth_SendNumber(User_Edit_Temp);
					   Bluetooth_SendString(">");
					   Left_Arrow();
					   LCD_PrintNum(User_Edit_Temp);
					   Right_Arrow();
					   Celsius_Sym();
					   User_AC_Input = UART_u8Receiver();
					   ASCII_Conversion(&User_AC_Input);
					   if(User_AC_Input==1)//-temp
					   {
						   if(User_Edit_Temp<=27)
						   {
							   User_Edit_Temp++;
							   Desired_Temp = User_Edit_Temp;
						   }
					   }
					   else if(User_AC_Input==2)//+temp
					   {
						   if(User_Edit_Temp>=18)
						   {
							   User_Edit_Temp--;
							   Desired_Temp = User_Edit_Temp;
						   }
					   }
					   else if(User_AC_Input==3)//enter
					   {
						   //start ADC here and Exit edit looper flag
//							GI_voidGlobalIntEnable();
//							ADC_Init_FreeRunning_Mode();
//							ADC_ChannelSelect_FreeRunning_Mode(ADC_Chann0);
							//send isr by setcallback function
//							ADC_FreeRunningSetCallBack(User_ADC_ISR);
//							ADC_Enable();
//							TIMER0_Start();
							User_Edit_Looper = 1;
//							User_AC_State_Flag = 1;
					   }
				   }
				   User_Edit_Looper = 0;
				break;
			case 3:User_AC_Exit_Flag=1;
				break;
			}
		}
	}
}
void User_ADC_ISR(u16 temp)
{
//	static u8 Temperature_Prev=0;

//	temp=temp*19;//Val=PTR*5/256  5-> ref volt and 5/256 is the step
//	temp=(temp/10);
//	Temperature = temp;
	Temperature = 25;
//	if(Temperature!=Temperature_Prev)
//	{
		if((Temperature-Desired_Temp)==0)
		{
			TIMER0_FAST_PWM_DutyCycle(0);//el moshkla kant hna 3shan bya5od w2t fel casting lel float
		}
		else if((Temperature-Desired_Temp)>3)
		{
			TIMER0_FAST_PWM_DutyCycle(100);
		}
		else if((Temperature-Desired_Temp)<=3)
		{
			TIMER0_FAST_PWM_DutyCycle(50);
		}
//	}
//	Temperature_Prev = Temperature;
}
void Recovering_Addresses_Location(void)
{
	u8 i;
	for(i=1;i<11;i++)
	{
		Array_Of_Addresses_Location[i-1]=eeprom_read_byte(i);
	}
}

void Recovering_Users_Status(void)
{
	u8 i;
	for(i=0;i<10;i++)
		{
			Array_Of_User_Status[i]=eeprom_read_byte((55+i));//EEPROM location 55 to 64 for status check
		}
}

void Add_User(void)
{
	u8 User_Index,Add_User_Input,Add_User_Looper_ExitFlag=1,User_List_Full_Flag=0;
	u8 User_Index_Prev_val,Add_User_Guard_Looper=0;
	u8 User_Full_List_Counter=0;
	LCD_CLR();
	Bluetooth_SendString("\n--------------------\n");
	Bluetooth_SendString("1)Move to LEFT\n2)Move to RIGHT\n3)Enter\n4)Back");
	LCD_WriteString("Available Users");
	LCD_goto(7,1);
	for(User_Index=0;User_Index<10;User_Index++)
	{
		if(Array_Of_User_Status[User_Index]==1)
		{
			User_Index++;//to match the switch cases (start from 1 and end at 10)
			break;
		}
		User_Full_List_Counter++;
	}
	if(User_Full_List_Counter==10)
	{
		User_List_Full_Flag=1;
	}
		//add while loop with an exit flag
		while( (Add_User_Looper_ExitFlag==1) && (User_List_Full_Flag==0) )
		{
			/* Start Of GUARD */
			while(Add_User_Guard_Looper==0)
			{
				if( (Array_Of_User_Status[User_Index-1]!=1) && (User_List_Full_Flag!=1) )
				{
					if(User_Index<User_Index_Prev_val)
					{
						if (User_Index==1)
						{
							User_Index_Prev_val=11;
							User_Index=10;
						}
						else
						{
							User_Index_Prev_val=User_Index;
							User_Index--;
						}
					}
					else if(User_Index>User_Index_Prev_val)
					{
						if (User_Index==10)
						{
							User_Index_Prev_val=0;
							User_Index=1;
						}
						else
						{
							User_Index_Prev_val=User_Index;
							User_Index++;
						}
					}
				}
				else
				{
					Add_User_Guard_Looper=1;
				}
			}
			/*Resetting Add user guard looper flag*/
			Add_User_Guard_Looper=0;
					/* Start of Printing*/
			if(User_Index == 1)
			{
				Bluetooth_SendString("\n--------------------\n");
				UART_SendByteSynchronous((User_Index+48));
				Bluetooth_SendString(">");
				LCD_goto(6,1);
				LCD_WriteString("      ");
				LCD_goto(8,1);
				LCD_PrintNum(User_Index);
				Right_Arrow();
			}
			else if(User_Index>1 && User_Index<10)
			{
				Bluetooth_SendString("\n--------------------\n");
				Bluetooth_SendString("<");
				UART_SendByteSynchronous((User_Index+48));
				Bluetooth_SendString(">");
				LCD_goto(6,1);
				LCD_WriteString("      ");
				LCD_goto(7,1);
				Left_Arrow();
				LCD_PrintNum(User_Index);
				Right_Arrow();
			}
			else if(User_Index == 10)
			{
				Bluetooth_SendString("\n--------------------\n");
				Bluetooth_SendString("<");
				Bluetooth_SendNumber(User_Index);
				LCD_goto(6,1);
				LCD_WriteString("      ");
				LCD_goto(7,1);
				Left_Arrow();
				LCD_PrintNum(User_Index);
			}

				/* Start of Recieving	*/
			Add_User_Input=UART_u8Receiver();
			ASCII_Conversion(&Add_User_Input);
						   /* Start of ACTION */
			if( (Add_User_Input==1) && (User_Index!=1) ) // 1 Move to Left  //2 Move to Right //3 IS ENTER
			{
				User_Index_Prev_val=User_Index;
				User_Index--;
			}
			else if( (Add_User_Input==2)  && (User_Index!=10) )
			{
				User_Index_Prev_val=User_Index;
				User_Index++;
			}
			else if(Add_User_Input==3)
			{
				//getting pass and saving it into eeprom code
			    Bluetooth_SendString("\n--------------------\n");
				Bluetooth_SendString("Enter a Password");
				Save_User_Password(User_Index);
				Add_User_Looper_ExitFlag=0;//need to change flag to Add_user_Looper_ExitFlag
			}
			else if(Add_User_Input==4)
			{
				Add_User_Looper_ExitFlag=0;
			}
		}
	if (User_List_Full_Flag==1)
	{
		LCD_CLR();
		Bluetooth_SendString("\n--------------------\n");
		Bluetooth_SendString("List Is Full");
		LCD_WriteString("List Is Full");
		_delay_ms(2000);
	}
}

void Delete_User(void)
{
	u8 User_Index,Delete_User_Input,Delete_User_Looper_ExitFlag=1,User_List_Empty_Flag=0;
	u8 User_Index_Prev_val,User_Empty_List_Counter=0,Delete_User_Guard_Looper=0;
	LCD_CLR();
	Bluetooth_SendString("\n--------------------\n");
	Bluetooth_SendString("1)Move to LEFT\n2)Move to RIGHT\n3)Enter\n4)Back");
	LCD_WriteString("Registered Users");
	LCD_goto(7,1);
	for(User_Index=0;User_Index<10;User_Index++)
	{
		if(Array_Of_User_Status[User_Index]==2)
		{
			User_Index++;//to match the switch cases (start from 1 and end at 10)
			break;
		}
		User_Empty_List_Counter++;
	}
	if(User_Empty_List_Counter==10)
	{
		User_List_Empty_Flag=1;
	}
		//add while loop with an exit flag
		while( (Delete_User_Looper_ExitFlag==1) && (User_List_Empty_Flag==0) )
		{
			while(Delete_User_Guard_Looper==0)
			{
				if( (Array_Of_User_Status[User_Index-1]==1)/*User Registerd*/ && (User_List_Empty_Flag!=1) )
				{
					if(User_Index<User_Index_Prev_val)
					{
						if (User_Index==1)
						{
							User_Index_Prev_val=11;
							User_Index=10;
						}
						else
						{
							User_Index_Prev_val=User_Index;
							User_Index--;
						}
					}
					else if(User_Index>User_Index_Prev_val)
					{
						if (User_Index==10)
						{
							User_Index_Prev_val=0;
							User_Index=1;
						}
						else
						{
							User_Index_Prev_val=User_Index;
							User_Index++;
						}
					}
				}
				else
				{
					Delete_User_Guard_Looper=1;
				}
			}
			/*Resetting Add user guard looper flag*/
			Delete_User_Guard_Looper=0;
					/* Start of Printing*/
				if(User_Index == 1)
				{
					 Bluetooth_SendString("\n--------------------\n");
					 UART_SendByteSynchronous((User_Index+48));
					 Bluetooth_SendString(">");
					LCD_goto(6,1);
					LCD_WriteString("      ");
					LCD_goto(8,1);
					LCD_PrintNum(User_Index);
					Right_Arrow();
				}
				else if(User_Index>1 && User_Index<10)
				{
					Bluetooth_SendString("\n--------------------\n");
					Bluetooth_SendString("<");
					UART_SendByteSynchronous((User_Index+48));
					Bluetooth_SendString(">");
					LCD_goto(6,1);
					LCD_WriteString("      ");
					LCD_goto(7,1);
					Left_Arrow();
					LCD_PrintNum(User_Index);
					Right_Arrow();
				}
				else if(User_Index == 10)
				{
					Bluetooth_SendString("\n--------------------\n");
					Bluetooth_SendString("<");
					Bluetooth_SendNumber(User_Index);
					LCD_goto(6,1);
					LCD_WriteString("      ");
					LCD_goto(7,1);
					Left_Arrow();
					LCD_PrintNum(User_Index);
				}
				   Delete_User_Input=UART_u8Receiver();
				   ASCII_Conversion(&Delete_User_Input);
				   if( (Delete_User_Input==1) && (User_Index !=1) ) // 1 Move to Left  //2 Move to Right //3 IS ENTER
				   {
					   User_Index_Prev_val=User_Index;
					   User_Index--;
				   }
				   else if(Delete_User_Input==2 && (User_Index !=10) )
				   {
					   User_Index_Prev_val=User_Index;
					   User_Index++;
				   }
				   else if(Delete_User_Input==3)
				   {
					   //getting pass and saving it into eeprom code
					   Delete_Registered_User(User_Index);
					   Delete_User_Looper_ExitFlag=0;//replace with Delete_user_Looper_exitflag
				   }
				   else if(Delete_User_Input==4)
				   {
					   Delete_User_Looper_ExitFlag=0;
				   }
		}
	if (User_List_Empty_Flag==1)
	{
		LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("No Useres");
		LCD_WriteString("No Users");
		_delay_ms(2000);
	}

}
void Right_Arrow(void)
{
	Write_data(0b01111110);
}
void Left_Arrow(void)
{
	Write_data(0b01111111);
}
void Celsius_Sym(void)
{
	Write_data(0b11011111);//degree symbol
	Write_data('C');
}

void Save_User_Password(u8 User_index)
{
	LCD_CLR();
	u8 i,Local_User_Password[4]={0},Counter=0,Local_input;
	u8 Local_Address_Reader,test;

	Local_Address_Reader=Array_Of_Addresses_Location[User_index-1];
	LCD_WriteString("Enter Password");
	LCD_goto(5,1);//to wrtie in the center
	 while(Counter<=3)
				 {
					Local_input = UART_u8Receiver();
					ASCII_Conversion(&Local_input);
					Local_User_Password[Counter]=Local_input;
					LCD_PrintNum(Local_User_Password[Counter]);
					Counter++;
				 }
	 _delay_ms(1000);
	 for(i=0;i<4;i++)
	 {
		 eeprom_write_byte(Local_Address_Reader,Local_User_Password[i]);
		 Local_Address_Reader++;
		 _delay_ms(50);
	 }
	 /* For Testing Purposes */
	 Local_Address_Reader=Array_Of_Addresses_Location[User_index-1];
	 LCD_CLR();
	 for(i=0;i<4;i++)
		 {
			 test=eeprom_read_byte(Local_Address_Reader);
			 LCD_PrintNum(test);
			 Local_Address_Reader++;
			 _delay_ms(1000);
		 }
	 LCD_CLR();
	 Bluetooth_SendString("\n--------------------\n");
	 Bluetooth_SendString("Saved");
	 LCD_WriteString("Saved");
	 _delay_ms(1000);
	 eeprom_write_byte(55+(User_index-1),2);
	 _delay_ms(50);
	 Recovering_Users_Status();
}

void Delete_Registered_User(u8 User_index)
{
	u8 Admin_Pass_State;
	LCD_CLR();
//	LCD_WriteString("Enter Admin Pass");
//	LCD_goto(5,1);//to wrtie in the center
	/* Admin Pass Algorithm */
	Admin_Pass_State=Enter_Admin_Pass();
	 _delay_ms(1000);
	 if(Admin_Pass_State==1)
	 {
		 eeprom_write_byte(55+(User_index-1),1);
		 _delay_ms(50);
		 LCD_CLR();
		 Bluetooth_SendString("\n--------------------\n");
		 Bluetooth_SendString("User Deleted");
		 LCD_WriteString("User Deleted");
		 _delay_ms(1000);
		 Recovering_Users_Status();
	 }
}

u8 Enter_Admin_Pass(void)
{
	 u8 Admin_input,Admin_Pass[4]={1,2,3,4},User_Pass_Input[4]={0},counter=0,i,flag=0;
//	 u8 Admin_Menu_Exit_Flag=1;
//	 u8 TimeOut_Counter;
	 u8 Admin_Max_Trial_counter=0;//for maximum trial of password of3 times
	 Bluetooth_SendString("\n--------------------\n");
	 Bluetooth_SendString("Enter Admin Pass");
	 LCD_WriteString("Enter Admin Pass");
	 LCD_goto(5,1);
	 while(Admin_Max_Trial_counter<=3)
	 {
		 while(counter<=3)
		 {

			 Admin_input = UART_u8Receiver();
			 ASCII_Conversion(&Admin_input);
			if(Admin_input !=0)
			{
				if( (Admin_input<10) && (counter <=3) )
					{
						User_Pass_Input[counter]=Admin_input;
						Write_data('0'+User_Pass_Input[counter] );
						counter++;
						Admin_input=0;
					}
			}
		 }
		 _delay_ms(500);
		 if(counter == 4)
		 {
			 for(i=0;i<=3;i++)
			 {
				 if (Admin_Pass[i]==User_Pass_Input[i])
				 {
					 continue;
				 }
				 else
				 {
					 flag=1;
				 }
			 }
		 }
		 if(flag==1)
		 {
			 LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Wrong Password");
			 LCD_WriteString("Wrong Pass");
			 flag=0;
			 counter=0;//to reset the array
			 Admin_Max_Trial_counter++;
			 _delay_ms(2500);
			 LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Enter Admin Password");
			 LCD_WriteString("Enter Admin Pass");
			 LCD_goto(5,1);

		 }
		 else
		 {
			 Admin_Max_Trial_counter=4;
			 return 1;
		 }
		 if (Admin_Max_Trial_counter==3)
		 {
			 LCD_CLR();
			 Bluetooth_SendString("\n--------------------\n");
			 Bluetooth_SendString("Timed Out");
			 LCD_WriteString("Time Out");
			 _delay_ms(1000);
			 Time_Out_Function();
			 Delete_User_Global_Return=1;
				return 0;
		 }
	 }
}
