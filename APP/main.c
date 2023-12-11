/*
 * main.c
 *
 *  Created on: 2/10/2022
 *      Author: RUNTIME_TERRROR
 *      		MINA AMIR GIRGIS
 *      		Ahmed Youssef Amer Youssef El Barbary
 *      		MAHMOUD MEDHAT SOBHY
 *      		Marwan Ashraf Moustafa Abdelaziz ElGamal
 *      		Nour Tarek Adel Mohamed Kamal Hammad
 *      		Merna Osama Talaat Mourad
 */
/*************************************************-INLUDED_DRIVERS-*************************************************/
#include "EXT_INT_Interface.h"
#include "KeyPad_Interface.h"
#include "LCD_Interface.h"
#include "LM35_Interface.h"
#include "Timer_Interface.h"
#include "GIE_Interface.h"
#include "DCMotor_Interface.h"
#include "Servo_Interface.h"
#include "ADC_Interface.h"
#include "WDT_Interface.h"
#include "AT24C16A_Interface.h"
#include "SPI_Interface.h"
#include "UART_Interface.h"
#include "LED_Interface.h"
#include "Buzzer_Interface.h"
#include "ADC_Interface.h"
#include "main_interface.h"
/*************************************************-FUNCTIONS_PROTOTYPES-********************************************/
void A_Timer0_Execution(void);
u8 A_LCD_Execution(void);
void A_UART_Void_UARTExecution(void);
void A_KeyPad_Execution(u8,u8,u8*);
/*************************************************-GLOBAL_VARIABLES-************************************************/
u32 Global_A_U32_Timer_s = INITIAL_VALUE;
static u8 Global_A_U8_UARTInput = INITIAL_VALUE;
u8 Global_A_U8_Status = INITIAL_VALUE;
u8 Global_U8_Trials = INITIAL_VALUE;
u8 Global_U8_AdminEnable = INITIAL_VALUE;
u8 Global_U8_DoorState = INITIAL_VALUE;
u8 Global_U8_DimLED = INITIAL_VALUE;
u8 Global_U8_ACState = INITIAL_VALUE;
/*************************************************-MAIN_FUNCTION-**************************************************/
int main()
{
/*************************************************-DRIVERS_INITILIZATION-******************************************/
	H_AT24C16A_Void_EEPROMInit();
	M_GIE_Void_GlobalInterruptEnable();
	M_Timer_Void_TimerInit(TIMER0_CHANNEL);
	H_KeyPad_Void_KeyPadInit();
	M_UART_Void_UARTInit();
	H_LCD_Void_LCDInit();
	H_LED_Void_LedInit(LED1);
	H_LED_Void_LedInit(LED2);
	H_LED_Void_LedInit(LED3);
	H_LED_Void_LedInit(LED4);
	H_LED_Void_LedInit(LED5);
	M_ADC_Void_ADCInit();
	H_Servo_Void_ServoInit();
	M_Timer_Void_PWMInit(TIMER1_CHANNEL);
	M_Timer_Void_PWMInit(TIMER2_CHANNEL);
	H_LCD_Void_SetCallBack(A_LCD_Execution);
	M_Timer_Void_TimerSetTime(TIMER0_CHANNEL,TIMER_INTERVAL);
	M_Timer_Void_TimerStart(TIMER0_CHANNEL);
	M_Timer_Void_SetCallBack(TIMER0_CHANNEL,A_Timer0_Execution);
	M_UART_Void_UARTSetCallBack(A_UART_Void_UARTExecution);
	H_KeyPad_Void_SetCallBack(A_KeyPad_Execution);
	H_DCMotor_Void_ACMotorInit();
	/*************************************************-MAIN_LOOP-*****************************************************/
	u8 Local_U8_Options = INITIAL_VALUE;
	u8 *Local_U8_ArrUserPtr;
	while(Global_U8_Trials <= ALLOWED_TRIALS)
	{
		Local_U8_Options = H_LCD_Void_LCDWelcome();
/*************************************************-kEYPAD_INTERRUPTION-*******************************************/
		H_LCD_Void_LCDClear();

		switch(Global_A_U8_Status)
		{
		case UNSIGNED_USER:
			Local_U8_ArrUserPtr = H_KeyPad_U8_KeyPadGetUser(Local_U8_Options);
			Global_A_U8_Status = H_AT24C16A_U8_EEPROMUserCheck(Local_U8_ArrUserPtr);
			H_LCD_Void_LCDUserCheck(Local_U8_ArrUserPtr);
			if(Global_A_U8_Status == INVALID_USER)
				Global_U8_Trials++;
			break;
		case KEYPAD_USER:

			switch(Local_U8_Options)
			{
			case KP_TOGGLE_LAMP1:
				H_LED_Void_LedTog(LED1); 				break;
			case KP_TOGGLE_LAMP2:
				H_LED_Void_LedTog(LED2); 				break;
			case KP_TOGGLE_LAMP3:
				H_LED_Void_LedTog(LED3); 				break;
			case KP_TOGGLE_LAMP4:
				H_LED_Void_LedTog(LED4); 				break;
			case KP_TOGGLE_LAMP5:
				H_LED_Void_LedTog(LED5); 				break;
			case KP_TOGGLE_DIMLAMP:
				if(Global_U8_DimLED == DIMMER_OFF)
				{
					M_Timer_Void_PWMStart(TIMER2_CHANNEL);
					Global_U8_DimLED = DIMMER_ON;
				}
				else
				{
					M_Timer_Void_PWMStop(TIMER2_CHANNEL);
					Global_U8_DimLED = DIMMER_OFF;
				}
				break;
			case KP_TOGGLE_AC:
				if(Global_U8_ACState == AC_OFF)
					Global_U8_ACState = AC_ON;
				else
					Global_U8_ACState = AC_OFF;
				break;
			case KP_SIGN_OUT:
				Global_A_U8_Status = UNSIGNED_USER;    break;
			}

			break;
			case UART_USER:
				H_LCD_Void_LCDAccessDenied();		   break;

			case ADMIN_USER:
				if(Local_U8_Options!=INITIAL_VALUE)
				{
					switch(Global_U8_AdminEnable)
					{
					case KEYPAD_ACCESS_ACCEPTED:
						switch(Local_U8_Options)
						{
						case KP_TOGGLE_LAMP1:
							H_LED_Void_LedTog(LED1); break;
						case KP_TOGGLE_LAMP2:
							H_LED_Void_LedTog(LED2); break;
						case KP_TOGGLE_LAMP3:
							H_LED_Void_LedTog(LED3); break;
						case KP_TOGGLE_LAMP4:
							H_LED_Void_LedTog(LED4); break;
						case KP_TOGGLE_LAMP5:
							H_LED_Void_LedTog(LED5); break;
						case KP_TOGGLE_DIMLAMP:
							if(Global_U8_DimLED == DIMMER_OFF)
							{
								M_Timer_Void_PWMStart(TIMER2_CHANNEL);
								Global_U8_DimLED = DIMMER_ON;
							}
							else
							{
								M_Timer_Void_PWMStop(TIMER2_CHANNEL);
								Global_U8_DimLED = DIMMER_OFF;
							}
							break;
						case KP_TOGGLE_AC:
							if(Global_U8_ACState == AC_OFF)
								Global_U8_ACState = AC_ON;
							else
								Global_U8_ACState = AC_OFF;
							break;
						case KP_TOGGLE_DOOR:
							if(Global_U8_DoorState == DOOR_CLOSED)
							{
								H_Servo_Void_ServoSetAngel(DOOR_OPEN_DEGREE);
								H_Servo_Void_ServoSetStart();
								Global_U8_DoorState = DOOR_OPEN;
							}
							else
							{
								H_Servo_Void_ServoSetAngel(DOOR_CLOSED_DEGREE);
								H_Servo_Void_ServoSetStart();
								Global_U8_DoorState = DOOR_CLOSED;
							}
							break;
						case KP_ALARM_ENABLE:

							break;
						case KP_SIGN_OUT:
							Global_A_U8_Status = UNSIGNED_USER;    break;
						}

						break;
						case KEYPAD_ACCESS_DENIED:
							H_LCD_Void_LCDAccessDenied(); break;
					}
				}
				break;
		}
	}
	M_UART_Void_UARTDeinit();
	H_Buzzer_Void_BuzzerAlarm();
}
/*************************************************-UART_INTERRUPTION-*********************************************/
void A_UART_Void_UARTExecution(void)
{
	Global_A_U8_UARTInput=UDR_REG;
	u8 Local_U8_UARTUser[USER_ARRAY_SIZE];
	H_Buzzer_Void_BuzzerOnce();
	switch(Global_A_U8_Status)
	{
/*************************************************-UNSIGNED_USER-*************************************************/
	case UNSIGNED_USER:
		switch(Global_A_U8_UARTInput)
		{
		case ADMIN_LOGIN:
			H_LCD_Void_LCDClear();
			H_LCD_Void_LCDGoTo(0,0);
			H_LCD_Void_LCDWriteString("UserName:");
			M_UART_Void_UARTSendString(UART_STRING_SIZE1,"Please, Enter your username: ");

			u8 Local_U8_UARTCounter = INITIAL_VALUE;
			while(Local_U8_UARTCounter <= (USER_ARRAY_SIZE-1))
			{
				Local_U8_UARTUser[Local_U8_UARTCounter]=M_UART_Void_UARTRec();
				if(Local_U8_UARTUser[Local_U8_UARTCounter] != INITIAL_VALUE)
				{
					if(Local_U8_UARTCounter < (USERNAME_SIZE-1))
						H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
					else if(Local_U8_UARTCounter == (USERNAME_SIZE-1))
					{
						H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
						M_UART_Void_UARTSendString(UART_STRING_SIZE1,"Please, Enter your password: ");
						H_LCD_Void_LCDGoTo(1,0);
						H_LCD_Void_LCDWriteString("Password: ");
					}
					else
					{
						H_LCD_Void_LCDWriteCharacter('*');
					}
					Local_U8_UARTCounter++;
				}
				_delay_ms(1);
			}
			_delay_ms(SECOND);
			if(H_AT24C16A_U8_EEPROMAdminCheck(Local_U8_UARTUser) == VALID_ADMIN_USER)
			{
				Global_A_U8_Status = ADMIN_USER;
				H_LCD_Void_LCDClear();
				H_LCD_Void_LCDGoTo(0,0);
				H_LCD_Void_LCDWriteString("Welcome Mina");
				_delay_ms(2000);
				H_LCD_Void_LCDClear();
				break;
			}
			else if(Global_U8_Trials> ALLOWED_TRIALS-1)
			{
				M_UART_Void_UARTDeinit();
				H_Buzzer_Void_BuzzerAlarm();
			}
			if(Global_A_U8_Status == INVALID_USER)
				Global_U8_Trials++;
			break;
		case USER_LOGIN:
			H_LCD_Void_LCDClear();
			H_LCD_Void_LCDGoTo(0,0);
			H_LCD_Void_LCDWriteString("UserName:");
			M_UART_Void_UARTSendString(UART_STRING_SIZE1,"Please, Enter your username: ");

			Local_U8_UARTCounter = INITIAL_VALUE;
			while(Local_U8_UARTCounter <= USER_ARRAY_SIZE-1)
			{
				Local_U8_UARTUser[Local_U8_UARTCounter] = M_UART_Void_UARTRec();
				if(Local_U8_UARTUser[Local_U8_UARTCounter] != INITIAL_VALUE)
				{
					if(Local_U8_UARTCounter < USERNAME_SIZE-1)
						H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
					else if(Local_U8_UARTCounter == USERNAME_SIZE-1)
					{
						H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
						M_UART_Void_UARTSendString(UART_STRING_SIZE1,"Please, Enter your password: ");
						H_LCD_Void_LCDGoTo(1,0);
						H_LCD_Void_LCDWriteString("Password: ");
					}
					else
					{
						H_LCD_Void_LCDWriteCharacter('*');
					}
					Local_U8_UARTCounter++;
				}
				_delay_ms(1);
			}
			if(H_AT24C16A_U8_EEPROMUserCheck(Local_U8_UARTUser) == VALID_UART_USER)
			{
				Global_A_U8_Status = UART_USER;
				M_UART_Void_UARTSendString(UART_STRING_SIZE2,"Welcome User");
				H_LCD_Void_LCDUserCheck(Local_U8_UARTUser);
				break;
			}
			else if(Global_U8_Trials > ALLOWED_TRIALS-1)
			{
				M_UART_Void_UARTDeinit();
				H_Buzzer_Void_BuzzerAlarm();
			}
			if(Global_A_U8_Status == INVALID_USER)
				Global_U8_Trials++;
			break;
		default:
			M_UART_Void_UARTSendString(UART_STRING_SIZE3,"U dont ve access");
			H_LCD_Void_LCDAccessDenied();
			break;
		}
		break;
/*************************************************-kEYPAD_USER-************************************************/
		case KEYPAD_USER:
			M_UART_Void_UARTSendString(UART_STRING_SIZE3,"U dont ve access");
			H_LCD_Void_LCDAccessDenied();
			break;
/*************************************************-UART_USER-**************************************************/
		case UART_USER:
			switch(Global_A_U8_UARTInput)
			{
			case ADMIN_LOGIN:
				M_UART_Void_UARTSendString(UART_STRING_SIZE4,"You have already signed in");
				H_LCD_Void_LCDClear();
				H_LCD_Void_LCDGoTo(0,0);
				H_LCD_Void_LCDWriteString("U are signed in");
				_delay_ms(SECOND);
				break;
			case USER_LOGIN:
				M_UART_Void_UARTSendString(UART_STRING_SIZE4,"You have already signed in");
				H_LCD_Void_LCDClear();
				H_LCD_Void_LCDGoTo(0,0);
				H_LCD_Void_LCDWriteString("U are signed in");
				_delay_ms(SECOND);
				break;
			case UART_TOGGLE_LAMP1:
				H_LED_Void_LedTog(LED1); break;
			case UART_TOGGLE_LAMP2:
				H_LED_Void_LedTog(LED2); break;
			case UART_TOGGLE_LAMP3:
				H_LED_Void_LedTog(LED3); break;
			case UART_TOGGLE_LAMP4:
				H_LED_Void_LedTog(LED4); break;
			case UART_TOGGLE_LAMP5:
				H_LED_Void_LedTog(LED5); break;
			case UART_TOGGLE_DIMLAMP:
				if(Global_U8_DimLED == DIMMER_OFF)
				{
					M_Timer_Void_PWMStart(TIMER2_CHANNEL);
					Global_U8_DimLED = DIMMER_ON;
				}
				else
				{
					M_Timer_Void_PWMStop(TIMER2_CHANNEL);
					Global_U8_DimLED = DIMMER_OFF;
				}
				break;
			case UART_TOGGLE_AC:
				if(Global_U8_ACState == AC_OFF)
					Global_U8_ACState = AC_ON;
				else
					Global_U8_ACState = AC_OFF;
				break;
			case UART_SIGN_OUT:
				Global_A_U8_Status = UNSIGNED_USER;
				break;
			default:
				M_UART_Void_UARTSendString(UART_STRING_SIZE3,"U dont ve access");
				H_LCD_Void_LCDAccessDenied();
				break;
			}
			break;
/*************************************************-ADMIN_USER-*************************************************/
			case ADMIN_USER:
				switch(Global_A_U8_UARTInput)
				{
				case ADMIN_LOGIN:
					M_UART_Void_UARTSendString(UART_STRING_SIZE4,"You have already signed in");
					H_LCD_Void_LCDClear();
					H_LCD_Void_LCDGoTo(0,0);
					H_LCD_Void_LCDWriteString("U are signed in");
					_delay_ms(SECOND);
					break;
				case USER_LOGIN:
					M_UART_Void_UARTSendString(UART_STRING_SIZE3,"You have already signed in");
					H_LCD_Void_LCDClear();
					H_LCD_Void_LCDGoTo(0,0);
					H_LCD_Void_LCDWriteString("U are signed in");
					_delay_ms(SECOND);
					break;
				case NEW_UART_USER:
					H_LCD_Void_LCDClear();
					H_LCD_Void_LCDGoTo(0,0);
					H_LCD_Void_LCDWriteString("UserName:");
					M_UART_Void_UARTSendString(UART_STRING_SIZE5,"Please, Enter new username: ");

					u8 Local_U8_UARTCounter = INITIAL_VALUE;
					while(Local_U8_UARTCounter <= USER_ARRAY_SIZE-1)
					{
						Local_U8_UARTUser[Local_U8_UARTCounter] = M_UART_Void_UARTRec();
						if(Local_U8_UARTUser[Local_U8_UARTCounter] != INITIAL_VALUE)
						{
							if(Local_U8_UARTCounter < USERNAME_SIZE-1)
								H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
							else if(Local_U8_UARTCounter == USERNAME_SIZE-1)
							{
								H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
								M_UART_Void_UARTSendString(UART_STRING_SIZE5,"Please, Enter new password: ");
								H_LCD_Void_LCDGoTo(1,0);
								H_LCD_Void_LCDWriteString("Password: ");
							}
							else
							{
								H_LCD_Void_LCDWriteCharacter("*");
							}
							Local_U8_UARTCounter++;
						}
						_delay_ms(1);
					}
					H_AT24C16A_U8_EEPROMNewUser(UART_USER,Local_U8_UARTUser);
					break;
				case NEW_KEYPAD_USER:
					H_LCD_Void_LCDClear();
					H_LCD_Void_LCDGoTo(0,0);
					H_LCD_Void_LCDWriteString("UserName:");
					M_UART_Void_UARTSendString(UART_STRING_SIZE5,"Please, Enter new username: ");
					Local_U8_UARTCounter = INITIAL_VALUE;
					while(Local_U8_UARTCounter <= USER_ARRAY_SIZE-1)
					{
						Local_U8_UARTUser[Local_U8_UARTCounter] = M_UART_Void_UARTRec();
						if(Local_U8_UARTUser[Local_U8_UARTCounter] != INITIAL_VALUE)
						{
							if(Local_U8_UARTCounter < USERNAME_SIZE-1)
								H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
							else if(Local_U8_UARTCounter == USERNAME_SIZE-1)
							{
								H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
								M_UART_Void_UARTSendString(UART_STRING_SIZE5,"Please, Enter new password: ");
								H_LCD_Void_LCDGoTo(1,0);
								H_LCD_Void_LCDWriteString("Password: ");
							}
							else
							{
								H_LCD_Void_LCDWriteCharacter("*");
							}
							Local_U8_UARTCounter++;
						}
						_delay_ms(1);
					}
					H_AT24C16A_U8_EEPROMNewUser(KEYPAD_USER,Local_U8_UARTUser);
					break;
				case UART_TOGGLE_LAMP1:
					H_LED_Void_LedTog(LED1); break;
				case UART_TOGGLE_LAMP2:
					H_LED_Void_LedTog(LED2); break;
				case UART_TOGGLE_LAMP3:
					H_LED_Void_LedTog(LED3); break;
				case UART_TOGGLE_LAMP4:
					H_LED_Void_LedTog(LED4); break;
				case UART_TOGGLE_LAMP5:
					H_LED_Void_LedTog(LED5); break;
				case UART_TOGGLE_DIMLAMP:
					if(Global_U8_DimLED == DIMMER_OFF)
					{
						M_Timer_Void_PWMStart(TIMER2_CHANNEL);
						Global_U8_DimLED = DIMMER_ON;
					}
					else
					{
						M_Timer_Void_PWMStop(TIMER2_CHANNEL);
						Global_U8_DimLED = DIMMER_OFF;
					}
					break;
				case UART_TOGGLE_AC:
					if(Global_U8_ACState == AC_OFF)
						Global_U8_ACState = AC_ON;
					else
						Global_U8_ACState = AC_OFF;
					break;
				case UART_TOGGLE_DOOR:
					if(Global_U8_DoorState == DOOR_CLOSED)
					{
						H_Servo_Void_ServoSetAngel(DOOR_OPEN_DEGREE);
						H_Servo_Void_ServoSetStart();
						Global_U8_DoorState = DOOR_OPEN;
					}
					else
					{
						H_Servo_Void_ServoSetAngel(DOOR_CLOSED_DEGREE);
						H_Servo_Void_ServoSetStart();
						Global_U8_DoorState = DOOR_CLOSED;
					}
					break;
				case ADMIN_KEYPAD_ENABLE:
					if(Global_U8_AdminEnable == KEYPAD_ACCESS_DENIED)
						Global_U8_AdminEnable = KEYPAD_ACCESS_ACCEPTED;
					else if(Global_U8_AdminEnable == KEYPAD_ACCESS_ACCEPTED)
						Global_U8_AdminEnable = KEYPAD_ACCESS_DENIED;
					break;
				case DELETE_USER:
					H_LCD_Void_LCDClear();
					H_LCD_Void_LCDGoTo(0,0);
					H_LCD_Void_LCDWriteString("UserName:");
					M_UART_Void_UARTSendString(UART_STRING_SIZE6,"Please, Enter username: ");
					Local_U8_UARTCounter = INITIAL_VALUE;
					while(Local_U8_UARTCounter <= USERNAME_SIZE-1)
					{
						Local_U8_UARTUser[Local_U8_UARTCounter] = M_UART_Void_UARTRec();
						if(Local_U8_UARTUser[Local_U8_UARTCounter] != INITIAL_VALUE)
						{
							H_LCD_Void_LCDWriteCharacter(Local_U8_UARTUser[Local_U8_UARTCounter]);
							Local_U8_UARTCounter++;
						}
						_delay_ms(1);
					}
					H_AT24C16A_U8_EEPROMDeleteUser(Local_U8_UARTUser);
					break;
				case UART_ALARM_ENABLE:
					M_UART_Void_UARTDeinit();
					H_Buzzer_Void_BuzzerAlarm();
					break;
				case UART_SIGN_OUT:
					Global_A_U8_Status=UNSIGNED_USER;
					break;
				}
				break;
	}
}
/*************************************************-CALLBACK_FUNCTIONS-*****************************************/
u8 A_LCD_Execution(void)
{
	u8 Local_U8_Read=0;
	M_Timer_Void_PWMSetDutyCycle(TIMER2_CHANNEL,(M_ADC_U16_ADCRead(ADC_CHANNEL_0)/9));
	Local_U8_Read = H_KeyPad_U8_KeyPadRead();
	return Local_U8_Read;
}

void A_KeyPad_Execution(u8 Copy_U8_Row,u8 Copy_U8_Col,u8* Copy_U8_LCDWrite)
{
	if(Copy_U8_Row == 1 && Copy_U8_Col >= 9)
	{
		H_LCD_Void_LCDGoTo(Copy_U8_Row,Copy_U8_Col);
		H_LCD_Void_LCDWriteString("*");
		H_Buzzer_Void_BuzzerOnce();
	}
	else
	{
		H_LCD_Void_LCDGoTo(Copy_U8_Row,Copy_U8_Col);
		H_LCD_Void_LCDWriteString(Copy_U8_LCDWrite);
		H_Buzzer_Void_BuzzerOnce();
	}
}
/*************************************************-TIMERS_ISR-*************************************************/
void A_Timer0_Execution(void)
{
	Global_A_U32_Timer_s++;

	if(Global_U8_ACState == AC_ON)
	{
		if(M_ADC_U16_ADCRead(ADC_CHANNEL_1) >= AC_ON_TEMP)
			H_DCMotor_Void_ACMotorStart();
		else
			H_DCMotor_Void_ACMotorStop();
	}
}
