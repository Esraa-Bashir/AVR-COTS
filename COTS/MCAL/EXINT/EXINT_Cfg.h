/*
 * EXINT_Cfg.h
 *
 * Created: 1/27/2023 8:27:58 AM
 *  Author: Esraa Beshir
 */ 


#ifndef EXINT_CFG_H_
#define EXINT_CFG_H_

/* Sense control moods for external interrupts */
#define EXINT_LowLevel 	0
#define EXINT_AnyChange 1
#define EXINT_FallingEdge 2
#define EXINT_RisingEdge 3

/* state for external interrupt enable or disable */

#define EXINT_Enable 	 0
#define EXINT_Disable 	 1

/* configuration */

#define INT0_Sense_Control		EXINT_FallingEdge 
#define INT1_Sense_Control		EXINT_FallingEdge
/* Sense Control for INT2 Could be EXINT_RisingEdge or EXINT_FallingEdge only */
#define INT2_Sense_Control		EXINT_RisingEdge


#define INT0_EnableState		EXINT_Enable
#define INT1_EnableState		EXINT_Enable
#define INT2_EnableState		EXINT_Disable


#endif /* EXINT_CFG_H_ */