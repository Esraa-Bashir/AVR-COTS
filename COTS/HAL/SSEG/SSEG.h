/*
 * SSEG.h
 *
 * Created: 1/20/2023 3:25:17 PM
 *  Author: Esraa Beshir
 */ 


#ifndef SSEG_H_
#define SSEG_H_
#include "SSEG_Cfg.h"


typedef enum
{
	SSEG_enuOK = 0,
	SSEG_enuNotOK ,
	SSEG_enuNullPtr
}SSEG_tenuErrorStatus;

/* SSEG SET NUMBER
	Input :the value to be written on seven segment
	Output : SSEG_tenuErrorStatus to report errors */
/********************************/
SSEG_tenuErrorStatus SSEG_enuSetNumber(u8 cpy_u8Number);

/* SSEG SET NUMBER and specify the sseg number 
	Input :the value to be written on seven segment and the sseg number
	Output : SSEG_tenuErrorStatus to report errors */
/********************************/
SSEG_tenuErrorStatus SSEG_enuSetNumberToSSEG(SSEG_tenu_SSEG cpy_enuSSEGNumber , u8 cpy_u8Number);

#endif /* SSEG_H_ */