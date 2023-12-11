/*
 * AT24C16A_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "AT24C16A_Interface.h"
#include "LED_Interface.h"
#include "LCD_Interface.h"

void H_AT24C16A_Void_EEPROMInit(void)
{
	M_I2C_Void_I2CInit();
	_delay_ms(1000);
}
void H_AT24C16A_Void_EEPROMWrite(u8 Copy_U8_Page,u8 Copy_U8_Byte,u8 Copy_U8_Data)
{
	M_I2C_Void_I2CStartCondition();
	M_I2C_Void_I2CSendSlaveAddressWrite(0x50 | Copy_U8_Page);
	M_I2C_Void_I2CSendByte(Copy_U8_Byte);
	M_I2C_Void_I2CSendByte(Copy_U8_Data);
	M_I2C_Void_I2CStopCondition();
}
u8   H_AT24C16A_Void_EEPROMRead(u8 Copy_U8_Page,u8 Copy_U8_Byte)
{
	u8 Local_U8_Reading = 0;
	M_I2C_Void_I2CStartCondition();
	M_I2C_Void_I2CSendSlaveAddressWrite(0x50 | Copy_U8_Page);
	M_I2C_Void_I2CSendByte(Copy_U8_Byte);
	M_I2C_Void_I2CRepeatedStart();
	M_I2C_Void_I2CSendSlaveAddressRead(0x50 | Copy_U8_Page);
	Local_U8_Reading = M_I2C_Void_I2CReadByte();
	M_I2C_Void_I2CStopCondition();
	return Local_U8_Reading;
}

u8 *H_AT24C16A_Void_EEPROMSequentialRead(u8 Copy_U8_Page,u8 Copy_U8_Byte)
{
	static u8 Local_U8_Reading[8];
	u8 Local_U8_Counter=0;
	M_I2C_Void_I2CStartCondition();
	M_I2C_Void_I2CSendSlaveAddressWrite(0x50 | Copy_U8_Page);
	M_I2C_Void_I2CSendByte(Copy_U8_Byte);
	M_I2C_Void_I2CRepeatedStart();
	M_I2C_Void_I2CSendSlaveAddressRead(0x50 | Copy_U8_Page);
	for(Local_U8_Counter=0;Local_U8_Counter<=7;Local_U8_Counter++)
		Local_U8_Reading[Local_U8_Counter] = M_I2C_Void_I2CReadByte();
	M_I2C_Void_I2CStopCondition();
	return Local_U8_Reading;
}

u8  H_AT24C16A_U8_EEPROMUserCheck(u8*Copy_U8_ArrPtr)
{
	u8 *Local_U8_ArrPtr;
	u8 Local_U8_Counter=9;
	u8 Local_U8_Counter2=0;
	u8 Local_U8_Counter3=0;
	while(1)
	{
		Local_U8_Counter3=0;
		M_I2C_Void_I2CReInit();
		Local_U8_ArrPtr = H_AT24C16A_Void_EEPROMSequentialRead(0,Local_U8_Counter);
		M_I2C_Void_I2CReInit();
		for(Local_U8_Counter2=0;Local_U8_Counter2<=7;Local_U8_Counter2++)
		{
			if(*(Copy_U8_ArrPtr+Local_U8_Counter2) == *(Local_U8_ArrPtr+Local_U8_Counter2))
				Local_U8_Counter3++;
		}
		if(Local_U8_Counter3==8)
		{
			return(H_AT24C16A_Void_EEPROMRead(0,Local_U8_Counter-1));
		}
		else if(H_AT24C16A_Void_EEPROMRead(0,Local_U8_Counter-1)==255)
		{
			M_I2C_Void_I2CReInit();
			return 0;
		}
		Local_U8_Counter+=9;
	}
}

u8  H_AT24C16A_U8_EEPROMAdminCheck(u8*Copy_U8_ArrPtr)
{
	u8 *Local_U8_ArrPtr;
	u8 Local_U8_Counter2=0;
	u8 Local_U8_Counter3=0;

	Local_U8_ArrPtr = H_AT24C16A_Void_EEPROMSequentialRead(0,0);
	M_I2C_Void_I2CReInit();
	for(Local_U8_Counter2=0;Local_U8_Counter2<=7;Local_U8_Counter2++)
	{
		if(*(Copy_U8_ArrPtr+Local_U8_Counter2) == *(Local_U8_ArrPtr+Local_U8_Counter2))
			Local_U8_Counter3++;
	}
	if(Local_U8_Counter3==8)
	{
		return 1;
	}
}

void H_AT24C16A_U8_EEPROMNewUser(u8 Copy_U8_Status,u8* Copy_U8_User)
{
	u8 Local_U8_Counter=8;
	u8 Local_U8_Counter2=0;
	while(1)
	{
		M_I2C_Void_I2CReInit();
		if(H_AT24C16A_Void_EEPROMRead(0,Local_U8_Counter)==255)
		{
			H_AT24C16A_Void_EEPROMWrite(0,Local_U8_Counter,Copy_U8_Status);
			_delay_ms(1000);
			Local_U8_Counter++;
			for(Local_U8_Counter2=0;Local_U8_Counter2<=7;Local_U8_Counter2++)
			{
				H_AT24C16A_Void_EEPROMWrite(0,Local_U8_Counter,*(Copy_U8_User+Local_U8_Counter2));
				Local_U8_Counter++;
				_delay_ms(1000);
			}
			break;
		}
		M_I2C_Void_I2CReInit();
		Local_U8_Counter+=9;
	}

}

u8  H_AT24C16A_U8_EEPROMDeleteUser(u8*Copy_U8_ArrPtr)
{
	u8 *Local_U8_ArrPtr;
	u8 Local_U8_Counter=9;
	u8 Local_U8_Counter2=0;
	u8 Local_U8_Counter3=0;
	while(1)
	{
		Local_U8_Counter3=0;
		M_I2C_Void_I2CReInit();
		Local_U8_ArrPtr = H_AT24C16A_Void_EEPROMSequentialRead(0,Local_U8_Counter);
		M_I2C_Void_I2CReInit();
		for(Local_U8_Counter2=0;Local_U8_Counter2<=3;Local_U8_Counter2++)
		{
			if(*(Copy_U8_ArrPtr+Local_U8_Counter2) == *(Local_U8_ArrPtr+Local_U8_Counter2))
				Local_U8_Counter3++;
		}
		if(Local_U8_Counter3==4)
		{
			for(Local_U8_Counter2=0;Local_U8_Counter2<=8;Local_U8_Counter2++)
			{
				H_AT24C16A_Void_EEPROMWrite(0,Local_U8_Counter-1,0);
				Local_U8_Counter++;
			}
			return 1;
		}
		else if(H_AT24C16A_Void_EEPROMRead(0,Local_U8_Counter-1)==255)
		{
			M_I2C_Void_I2CReInit();
			return 0;
		}
		Local_U8_Counter+=9;
	}
}










