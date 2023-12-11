/*
 * SPI_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "SPI_Config.h"
#include "SPI_Interface.h"
#include "SPI_Private.h"

void M_SPI_Void_SPIInit(void)
{
#if   SPI_MODE   ==   SPI_MASTER_MODE
	/* TO SELECT MASTER MODE */
	SET_BIT(SPCR_REG,MSTR_BIT);
	/* TO SELECT DV -> 128 */
	SET_BIT(SPCR_REG,SPR0_BIT);
	SET_BIT(SPCR_REG,SPR1_BIT);
	M_DIO_Void_SetPinDirection(PB5_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(PB6_PIN,INPUT);
	M_DIO_Void_SetPinDirection(PB4_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(PB7_PIN,OUTPUT);
#elif SPI_MODE   ==   SPI_SLAVE_MODE
	CLR_BIT(SPCR_REG,MSTR_BIT);
	M_DIO_Void_SetPinDirection(PB5_PIN,INPUT);
	M_DIO_Void_SetPinDirection(PB6_PIN,OUTPUT);
	M_DIO_Void_SetPinDirection(PB4_PIN,INPUT);
	M_DIO_Void_SetPinDirection(PB7_PIN,INPUT);
#endif
	/* TO SELECT SENDING FROM LSB */
	SET_BIT(SPCR_REG,DORD_BIT);
	/* TO ENABLE SPI CIRCUIT */
	SET_BIT(SPCR_REG,SPE_BIT);
}
#include "LED_Interface.h"
u8   M_SPI_U8_SPITransive(u8 Copy_U8_DataSend)
{
	SPDR_REG = Copy_U8_DataSend;
	u32 Local_U32_Counter = 0;
	while(Local_U32_Counter < POLLING_TIME)
	{
		Local_U32_Counter++;
		if(GET_BIT(SPSR_REG,SPIF_BIT) == SPI_FINISHED_TRANSIVE)
		{
			//H_LED_Void_LedSetOn(LED0);
			break;
		}
	}
	return SPDR_REG;
}






