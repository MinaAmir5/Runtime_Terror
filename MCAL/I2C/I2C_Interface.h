/*
 * I2C_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_I2C_I2C_INTERFACE_H_
#define MCAL_I2C_I2C_INTERFACE_H_

#include "BitMath.h"
#include "STD.h"

void M_I2C_Void_I2CInit(void);
void M_I2C_Void_I2CStartCondition(void);
void M_I2C_Void_I2CStopCondition(void);
void M_I2C_Void_I2CRepeatedStart(void);
void M_I2C_Void_I2CSendSlaveAddressWrite(u8);
void M_I2C_Void_I2CSendSlaveAddressRead(u8);
void M_I2C_Void_I2CSendByte(u8);
u8   M_I2C_Void_I2CReadByte(void);
void M_I2C_Void_I2CReInit(void);

#endif /* MCAL_I2C_I2C_INTERFACE_H_ */
