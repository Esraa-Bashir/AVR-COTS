/*
 * SWITCH.h
 *
 * Created: 1/19/2023 11:49:42 AM
 *  Author: Esraa Beshir
 */ 


#ifndef SWITCH_H_
#define SWITCH_H_

#include "SWITCH_Cfg.h"

typedef enum
{
	SWITCH_enuPressed = 0,
	SWITCH_enuNotPressed
}SWITCH_tenuStatus;

typedef enum
{
	SWITCH_enuOK = 0,
	SWITCH_enuNotOK ,
	SWITCH_enuNullPtr
}SWITCH_tenuErrorStatus;

/********************************/
/* SWITCH GET STATUS (PRESSED OR NOT PRESSED)
	Input :Switch number and pointer to store the SWITCH STATUS
	Output : SWITCH_tenuErrorStatus to report errors */
/********************************/

SWITCH_tenuErrorStatus SWITCH_enuGetSwitchValue (SWC_tenuSWCNumber cpy_enuSWCNumber, u8* Add_pu8SwitchStatus); 

#endif /* SWITCH_H_ */