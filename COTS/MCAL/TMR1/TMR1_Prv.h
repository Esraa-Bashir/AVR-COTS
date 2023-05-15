/*
 * ICU_Prv.h
 *
 * Created: 3/11/2023 6:46:03 PM
 *  Author: Esraa Beshir
 */ 


#ifndef TMR1_PRV_H_
#define TMR1_PRV_H_


#define TCCR1A_REG	(*(volatile u8*)0x4F)
#define TCCR1B_REG	(*(volatile u8*)0x4E)
#define TCNT1_REG	(*(volatile u16*)0x4C)
#define OCR1A_REG	(*(volatile u16*)0x4A)
#define OCR1B_REG	(*(volatile u16*)0x48)
#define ICR1_REG	(*(volatile u16*)0x46)
#define TIMSK_REG	(*(volatile u8*)0x59)

#define OC1_clear	(~(0x03))
#define OC1A_shift	6
#define OC1B_shift	4
#define Mode1_clear	(~(0x03))
#define Mode2_clear	(~(0x18))
#define Mode_split	(0x03)
#define Mode_shift	1
#define Clk_clear	(~(0x07))
#define ICES1_Pin	6
#define Interrupt_Shift	2

#endif /* ICU_PRV_H_ */