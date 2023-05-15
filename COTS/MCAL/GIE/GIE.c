/*
 * GIE.c
 *
 * Created: 1/27/2023 7:52:59 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "GIE.h"
#include "GIE_Prev.h"

GIE_tenuErrorStatus GIE_enuEnable(void)
{
	GIE_tenuErrorStatus Loc_enuErrorStatus = GIE_enuOK;
	
	SET_BIT(SREG,GIE_PIN);
	u8 Loc_u8Check = GET_BIT(SREG,GIE_PIN);
	if (Loc_u8Check == 0)
		Loc_enuErrorStatus = GIE_enuNotOK;
	return Loc_enuErrorStatus;
}

GIE_tenuErrorStatus GIE_enuDisable(void)
{
	GIE_tenuErrorStatus Loc_enuErrorStatus = GIE_enuOK;
	
	CLR_BIT(SREG,GIE_PIN);
	u8 Loc_u8Check = GET_BIT(SREG,GIE_PIN);
	if (Loc_u8Check == 1)
	Loc_enuErrorStatus = GIE_enuNotOK;
	return Loc_enuErrorStatus;
}