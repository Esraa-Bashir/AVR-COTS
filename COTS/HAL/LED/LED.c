#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "LED_Cfg.h"
#include "LED.h"
#include "LED_Prv.h"


LED_tenuErrorStatus LED_enuInit(void){
	LED_tenuErrorStatus Loc_enuErrorState = DIO_enuInit();
	return Loc_enuErrorState ;
}

LED_tenuErrorStatus LED_enuLedOn(LED_tenuLedNumber cpy_enuLEDNumber){
	LED_tenuErrorStatus Loc_enuErrorState = LED_enuOK;
	if(cpy_enuLEDNumber >= LED_enuNoOfLeds)
	{
		Loc_enuErrorState = LED_enuNotOK;
	}
	else{
		switch(LED_strCfg[cpy_enuLEDNumber].LED_Polarity){
			case (LED_enuActiveHigh):
				 Loc_enuErrorState = DIO_enuSetValue( LED_strCfg[cpy_enuLEDNumber].LED_PinNumber,DIO_enuHIGH);
				 break;
			case (LED_enuActiveLow):
				Loc_enuErrorState = DIO_enuSetValue( LED_strCfg[cpy_enuLEDNumber].LED_PinNumber,DIO_enuLOW);
				break;
			default:
				Loc_enuErrorState = LED_enuNotOK;
	 }
	}
	return Loc_enuErrorState;
}

LED_tenuErrorStatus LED_enuLedOff(LED_tenuLedNumber cpy_enuLEDNumber){
	LED_tenuErrorStatus Loc_enuErrorState = LED_enuOK;
	if(cpy_enuLEDNumber >=  LED_enuNoOfLeds)
	{
		Loc_enuErrorState = LED_enuNotOK;
	}
	else{
		switch(LED_strCfg[cpy_enuLEDNumber].LED_Polarity){
			case (LED_enuActiveHigh):
			Loc_enuErrorState = DIO_enuSetValue( LED_strCfg[cpy_enuLEDNumber].LED_PinNumber,DIO_enuLOW);
			break;
			case (LED_enuActiveLow):
			Loc_enuErrorState = DIO_enuSetValue( LED_strCfg[cpy_enuLEDNumber].LED_PinNumber,DIO_enuHIGH);
			break;
			default:
			Loc_enuErrorState = LED_enuNotOK;
		}
	}
	return Loc_enuErrorState;
}

LED_tenuErrorStatus LED_enuLedToggle(LED_tenuLedNumber cpy_enuLEDNumber){
	LED_tenuErrorStatus Loc_enuErrorState = LED_enuOK;
	if(cpy_enuLEDNumber >=  LED_enuNoOfLeds)
	{
		Loc_enuErrorState = LED_enuNotOK;
	}
	else{
		Loc_enuErrorState = DIO_enuTogPin( LED_strCfg[cpy_enuLEDNumber].LED_PinNumber);
	}
	return Loc_enuErrorState;
}