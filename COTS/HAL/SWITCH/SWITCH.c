/*
 * SWITCH.c
 *
 * Created: 1/19/2023 11:49:26 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "SWITCH_Cfg.h"
#include "SWITCH.h"
#define F_CPU 8000000UL
#include <util/delay.h>


SWITCH_tenuErrorStatus SWITCH_enuGetSwitchValue (SWC_tenuSWCNumber cpy_enuSWCNumber, u8* Add_pu8SwitchStatus){
	SWITCH_tenuErrorStatus Loc_enuErrorState = SWITCH_enuOK;
	u8 Loc_u8SwitchInput;
	if ( cpy_enuSWCNumber >= SWC_enuNoOfSWCs)
	{
		Loc_enuErrorState = SWITCH_enuNotOK;
	}
	else {
	Loc_enuErrorState = DIO_enuGetPin(SWC_strCfg [cpy_enuSWCNumber].SWC_PinNumber,&Loc_u8SwitchInput);
	if (Loc_u8SwitchInput ==  DIO_enuLOW ){
		_delay_ms(50);
		 DIO_enuGetPin(SWC_strCfg [cpy_enuSWCNumber].SWC_PinNumber,&Loc_u8SwitchInput);
		 if (Loc_u8SwitchInput ==  DIO_enuLOW ){
			 switch (SWC_strCfg [cpy_enuSWCNumber].SWC_InputType)
			 {
				 case (DIO_INPUT_PULL_UP):
					* Add_pu8SwitchStatus = SWITCH_enuPressed;
					break;
				case (DIO_INPUT_PULL_DOWN):
					* Add_pu8SwitchStatus = SWITCH_enuNotPressed;
					break;
				default:
					Loc_enuErrorState =SWITCH_enuNotOK;
				 
			 }
		 }
		 else
			Loc_enuErrorState =SWITCH_enuNotOK;
		
	}
	else {
		_delay_ms(50);
		DIO_enuGetPin(SWC_strCfg [cpy_enuSWCNumber].SWC_PinNumber,&Loc_u8SwitchInput);
		if (Loc_u8SwitchInput ==  DIO_enuHIGH ){
			 switch (SWC_strCfg [cpy_enuSWCNumber].SWC_InputType)
			 {
				 case (DIO_INPUT_PULL_UP):
				 * Add_pu8SwitchStatus = SWITCH_enuNotPressed;
				 break;
				 case (DIO_INPUT_PULL_DOWN):
				 * Add_pu8SwitchStatus = SWITCH_enuPressed;
				 break;
				 default:
				 Loc_enuErrorState =SWITCH_enuNotOK;
				 
			 }
		}
		else
		Loc_enuErrorState =SWITCH_enuNotOK;
	}
	}
	return Loc_enuErrorState;
	
}