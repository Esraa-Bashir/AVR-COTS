/*
 * SPI_Prv.h
 *
 * Created: 4/7/2023 9:22:52 PM
 *  Author: Esraa Beshir
 */ 


#ifndef SPI_PRV_H_
#define SPI_PRV_H_

#define SPCR		(*((volatile u8*) 0x2D))
#define SPSR		(*((volatile u8*) 0x2E))
#define SPDR		(*((volatile u8*) 0x2F))


#define SPE_PIN			6

#define SPIF_PIN		7


#endif /* SPI_PRV_H_ */