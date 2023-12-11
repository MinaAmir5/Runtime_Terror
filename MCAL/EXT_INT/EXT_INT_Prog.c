/*
 * EXT_INT_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "EXT_INT_Interface.h"
#include "EXT_INT_Private.h"


void (*EXT_INT_CallBack) (void);

void M_EXT_INT_Void_ExtIntInit(u8 Copy_U8_Num)
{
	switch(Copy_U8_Num)
	{
	case EXT_INT_0:
#if   SENSE_CONTROL0   ==   RISING_EDGE
		SET_BIT(MCUCR_REG,ISC00_BIT);
		SET_BIT(MCUCR_REG,ISC01_BIT);
#elif SENSE_CONTROL0   ==   FALLING_EDGE
		CLR_BIT(MCUCR_REG,ISC00_BIT);
		SET_BIT(MCUCR_REG,ISC01_BIT);
#elif SENSE_CONTROL0   ==   LOW_LEVEL
		CLR_BIT(MCUCR_REG,ISC00_BIT);
		CLR_BIT(MCUCR_REG,ISC01_BIT);
#elif SENSE_CONTROL0   ==   ANY_LOGICAL_CHANGE
		SET_BIT(MCUCR_REG,ISC00_BIT);
		CLR_BIT(MCUCR_REG,ISC01_BIT);
#endif
		// to enable local int
		SET_BIT(GICR_REG,INT0_BIT);
		break;
	case EXT_INT_1:
#if   SENSE_CONTROL1   ==   RISING_EDGE
		SET_BIT(MCUCR_REG,ISC10_BIT);
		SET_BIT(MCUCR_REG,ISC11_BIT);
#elif SENSE_CONTROL1   ==   FALLING_EDGE
		CLR_BIT(MCUCR_REG,ISC10_BIT);
		SET_BIT(MCUCR_REG,ISC11_BIT);
#elif SENSE_CONTROL1   ==   LOW_LEVEL
		CLR_BIT(MCUCR_REG,ISC10_BIT);
		CLR_BIT(MCUCR_REG,ISC11_BIT);
#elif SENSE_CONTROL1   ==   ANY_LOGICAL_CHANGE
		SET_BIT(MCUCR_REG,ISC10_BIT);
		CLR_BIT(MCUCR_REG,ISC11_BIT);
#endif
		// to enable local int
		SET_BIT(GICR_REG,INT1_BIT);
		break;
	case EXT_INT_2:
#if   SENSE_CONTROL2   ==   RISING_EDGE
		SET_BIT(MCUCSR_REG,ISC2_BIT);
#elif SENSE_CONTROL2   ==   FALLING_EDGE
		CLR_BIT(MCUCSR_REG,ISC2_BIT);
#endif
		// to enable local int
		SET_BIT(GICR_REG,INT2_BIT);
		break;
	default:  break;
	}
}

void M_EXT_INT_Void_SetCallBack(void(*Copy_Ptr)(void))
{
	EXT_INT_CallBack = Copy_Ptr;
}

ISR(INT0_vect)
{
	EXT_INT_CallBack();
}
ISR(INT1_vect)
{

}
ISR(INT2_vect)
{

}
