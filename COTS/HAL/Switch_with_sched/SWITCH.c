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


static u8 switch_state[SWC_enuNoOfSWCs];
SWITCH_tenuErrorStatus SWITCH_enuGetSwitchValue (SWC_tenuSWCNumber cpy_enuSWCNumber, u8* Add_pu8SwitchStatus){
	SWITCH_tenuErrorStatus Loc_enuErrorState = SWITCH_enuOK;
	if ( cpy_enuSWCNumber >= SWC_enuNoOfSWCs)
	{
		Loc_enuErrorState = SWITCH_enuNotOK;
	}
	else {
		* Add_pu8SwitchStatus = switch_state[cpy_enuSWCNumber] ^ SWC_strCfg [cpy_enuSWCNumber].SWC_InputType ;
	}
	return Loc_enuErrorState;
	
}


/* will be called each 5 msec */
void SWITCH_Task (void){
	static u8 counter[SWC_enuNoOfSWCs],previous[SWC_enuNoOfSWCs];
	u8 loc_u8current;
	for (u8 idx=0;idx<SWC_enuNoOfSWCs ;idx++){
		 DIO_enuGetPin(SWC_strCfg [idx].SWC_PinNumber,&loc_u8current);
		 if (loc_u8current == previous[idx]){
			 counter[idx]++;
		 }
		 else
		 {
			 counter[idx]=0;
		 }
		 if (counter[idx]==5){
			 switch_state[idx]=loc_u8current;
			 counter[idx]=0;
		 }
		 previous[idx]=loc_u8current;
	}
}