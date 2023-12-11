/*
 * AT24C16A_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef HAL_AT24C16A_AT24C16A_INTERFACE_H_
#define HAL_AT24C16A_AT24C16A_INTERFACE_H_

#include "I2C_Interface.h"
#include <util/delay.h>

void H_AT24C16A_Void_EEPROMInit(void);
void H_AT24C16A_Void_EEPROMWrite(u8,u8,u8);
u8   H_AT24C16A_Void_EEPROMRead(u8,u8);
u8   H_AT24C16A_U8_EEPROMUserCheck(u8*);
u8 *H_AT24C16A_Void_EEPROMSequentialRead(u8,u8);
u8  H_AT24C16A_U8_EEPROMAdminCheck(u8*);
void H_AT24C16A_U8_EEPROMNewUser(u8,u8*);
u8 H_AT24C16A_U8_EEPROMDeleteUser(u8*);


#endif /* HAL_AT24C16A_AT24C16A_INTERFACE_H_ */
