/*
 * SPI_Private.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_SPI_SPI_PRIVATE_H_
#define MCAL_SPI_SPI_PRIVATE_H_

#define SPCR_REG                *(volatile u8*)0x2D
#define SPDR_REG                *(volatile u8*)0x2F
#define SPSR_REG                *(volatile u8*)0x2E

/* SPCR BITS */
#define SPE_BIT                        6
#define DORD_BIT                       5
#define MSTR_BIT                       4
#define SPR1_BIT                       1
#define SPR0_BIT                       0

/* SPSR BITS */
#define SPIF_BIT                       7

#define SPI_MASTER_MODE                1
#define SPI_SLAVE_MODE                 2

#define POLLING_TIME                   2000000
#define SPI_FINISHED_TRANSIVE          1

#endif /* MCAL_SPI_SPI_PRIVATE_H_ */
