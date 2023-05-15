/*
 * TMR0_Prv.h
 *
 * Created: 2/27/2023 11:17:32 AM
 *  Author: Esraa Beshir
 */ 


#ifndef TMR0_PRV_H_
#define TMR0_PRV_H_


#define TCCR0_REG		(*(volatile u8*)0x53)
#define TCNT0_REG		(*(volatile u8*)0x52)
#define OCR0_REG		(*(volatile u8*)0x5C)
#define TIMSK_REG		(*(volatile u8*)0x59)
#define TIFR_REG		(*(volatile u8*)0x58)

#define FOC0_Pin	7
#define OCIE0_Pin	1
#define TOIE0_Pin	0

#define Clock_Reset_Mask		0xF8
#define Clear_Mode_Mask			(~0x48)
#define Clear_COM_Mode_Mask		(~0x30)
#define Clear_TCCR0_RegMask		0x80

#endif /* TMR0_PRV_H_ */