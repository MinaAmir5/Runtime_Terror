/*
 * Projects.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef APP_PROJECTS_PROJECTS_H_
#define APP_PROJECTS_PROJECTS_H_


#include "STD.h"
#include "BitMath.h"
#include "DIO_Interface.h"
#include "LED_Interface.h"
#include "Buzzer_Interface.h"
#include "PB_Interface.h"
#include "LCD_Interface.h"
#include "UART_Interface.h"
#include "SSD_Interface.h"
#include "AT24C16A_Interface.h"
#include <util/delay.h>

void A_SSDProject(void);
void A_HC05Project(void);
void A_EEPROM_Project(void);

#endif /* APP_PROJECTS_PROJECTS_H_ */
