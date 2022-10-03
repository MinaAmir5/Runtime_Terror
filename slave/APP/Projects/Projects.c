/*
 * Projects.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#include "Projects.h"

void A_SSDProject(void)
{
	int x = 0;
	H_SSD_Void_SSDInit();
	while(1)
	{
		H_SSD_Void_SSDWriteNumber(x);
		_delay_ms(1000);
		x++;
	}
}
void A_HC05Project(void)
{
	H_LCD_Void_LCDInit();
	M_UART_Void_UARTInit();
	H_LCD_Void_LCDWriteCharacter('k');
	u8 x = 0;
	while(1)
	{
		x = M_UART_Void_UARTRec();
		if(x != 0)
		{
			H_LCD_Void_LCDWriteCharacter(x);
		}
	}
}

void A_EEPROM_Project(void)
{
	u8 x = 5;
	_delay_ms(1000);
	H_AT24C16A_Void_EEPROMInit();
	H_LCD_Void_LCDInit();
	x = H_AT24C16A_Void_EEPROMRead(1,12);
	while(1)
	{
		H_LCD_Void_LCDWriteNumber(x);
		_delay_ms(1000);
		x++;
		H_LCD_Void_LCDClear();
		H_AT24C16A_Void_EEPROMWrite(1,12,x);
	}
}
