/*
 * UART_Interface.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "DIO_Interface.h"
#include "UART_Config.h"
#include "BitMath.h"
#include "STD.h"

void M_UART_Void_UARTInit(void);
void M_UART_Void_UARTSetBaudRate(u32);
void M_UART_Void_UARTSend(u8);
u8   M_UART_Void_UARTRec(void);

#endif /* MCAL_UART_UART_INTERFACE_H_ */
