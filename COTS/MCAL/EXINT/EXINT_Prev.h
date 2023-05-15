/*
 * EXINT_Prev.h
 *
 * Created: 1/27/2023 8:28:22 AM
 *  Author: Esraa Beshir
 */ 


#ifndef EXINT_PREV_H_
#define EXINT_PREV_H_

#define MCUCR_REG	 (*((volatile u8*) 0x55))
#define MCUCSR_REG	 (*((volatile u8*) 0x54))
#define GICR_REG	 (*((volatile u8*) 0x5B))
#define GIFR_REG	 (*((volatile u8*) 0x5A))

#define ISC11_PIN	3
#define ISC10_PIN	2
#define ISC01_PIN	1
#define ISC00_PIN	0

#define ISC2_PIN	6

#define INT1_PIN	7
#define INT0_PIN	6
#define INT2_PIN	5

#define INTF1_PIN	7
#define INTF0_PIN	6
#define INTF2_PIN	5



#endif /* EXINT_PREV_H_ */