#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO_Prv.h"
#include "DIO.h"
#include "DIO_Cfg.h"

DIO_tenuErrorStatus DIO_enuInit(void){
	u8 Loc_Counter;
	u8 Loc_u8PortNumber =0;
	u8 LOc_u8PinNumber =0;
	for(Loc_Counter=0; Loc_Counter <DIO_enuNumberOfPins; Loc_Counter++){
		Loc_u8PortNumber = Loc_Counter/DIO_NumberOfPortPins;
		LOc_u8PinNumber = Loc_Counter%DIO_NumberOfPortPins;
		switch(Loc_u8PortNumber){
			case (DIO_PORTA):
				if (DIO_strPinCfg[Loc_Counter].DIO_PinDirection == DIO_enuOUTPUT)
				{
					SET_BIT(DDRA,LOc_u8PinNumber );
				}
				else{
					CLR_BIT(DDRA,LOc_u8PinNumber );
					if(DIO_strPinCfg[Loc_Counter].DIO_InputStatus == DIO_INPUT_PULL_UP )
					{ 
						SET_BIT(PORTA,LOc_u8PinNumber);
					}
					else{
						CLR_BIT(PORTA,LOc_u8PinNumber );
					}
				}
				break;
			case (DIO_PORTB):
				if (DIO_strPinCfg[Loc_Counter].DIO_PinDirection == DIO_enuOUTPUT)
				{
					SET_BIT(DDRB,LOc_u8PinNumber );
				}
				else{
					CLR_BIT(DDRB,LOc_u8PinNumber );
					if(DIO_strPinCfg[Loc_Counter].DIO_InputStatus == DIO_INPUT_PULL_UP )
					{
						SET_BIT(PORTB,LOc_u8PinNumber);
					}
					else{
						CLR_BIT(PORTB,LOc_u8PinNumber );
					}
				}
				break;
			case (DIO_PORTC):
				if (DIO_strPinCfg[Loc_Counter].DIO_PinDirection == DIO_enuOUTPUT)
				{
					SET_BIT(DDRC,LOc_u8PinNumber );
				}
				else{
					CLR_BIT(DDRC,LOc_u8PinNumber );
					if(DIO_strPinCfg[Loc_Counter].DIO_InputStatus == DIO_INPUT_PULL_UP )
					{
						SET_BIT(PORTC,LOc_u8PinNumber);
					}
					else{
						CLR_BIT(PORTC,LOc_u8PinNumber );
					}
				}
				break;
			case (DIO_PORTD):
				if (DIO_strPinCfg[Loc_Counter].DIO_PinDirection == DIO_enuOUTPUT)
				{
					SET_BIT(DDRD,LOc_u8PinNumber );
				}
				else{
					CLR_BIT(DDRD,LOc_u8PinNumber );
					if(DIO_strPinCfg[Loc_Counter].DIO_InputStatus == DIO_INPUT_PULL_UP )
					{
						SET_BIT(PORTD,LOc_u8PinNumber);
					}
					else{
						CLR_BIT(PORTD,LOc_u8PinNumber );
					}
				}
				break;
		}
	}
	return DIO_enuOK;
}


DIO_tenuErrorStatus DIO_enuSetPortValue(DIO_tenuPorts cpy_enuPortNumber,u8 cpy_enuPortValue)
{
	DIO_tenuErrorStatus Loc_enuErrorState =  DIO_enuOK;
	switch(cpy_enuPortNumber){
		case (DIO_PORTA):
			
			ASSIGN_REG(PORTA,cpy_enuPortValue);
		break;
		case (DIO_PORTB):
			ASSIGN_REG(PORTB,cpy_enuPortValue);
		break;
		case (DIO_PORTC):
			ASSIGN_REG(PORTC,cpy_enuPortValue);
		break;
		case (DIO_PORTD):
			ASSIGN_REG(PORTD,cpy_enuPortValue);
		break;
		default:
		Loc_enuErrorState =  DIO_enuNotOK;
		
	}
	return Loc_enuErrorState;
}



DIO_tenuErrorStatus DIO_enuSetValue(DIO_tenuPins cpy_enuPinNumber,DIO_tenuPinValue cpy_enuPinValue){
	u8 Loc_u8PortNumber = cpy_enuPinNumber/DIO_NumberOfPortPins;
	u8 LOc_u8PinNumber = cpy_enuPinNumber%DIO_NumberOfPortPins;
	DIO_tenuErrorStatus Loc_enuErrorState =  DIO_enuOK;
	switch(Loc_u8PortNumber){
		case (DIO_PORTA):
				switch(cpy_enuPinValue){
					case (DIO_enuHIGH):
						SET_BIT(PORTA,LOc_u8PinNumber);
						break;
					case (DIO_enuLOW):
						CLR_BIT(PORTA,LOc_u8PinNumber);
						break;
					default:
						Loc_enuErrorState =  DIO_enuNotOK;
						
				}
			break;
		case (DIO_PORTB):
			switch(cpy_enuPinValue){
				case (DIO_enuHIGH):
					SET_BIT(PORTB,LOc_u8PinNumber);
					break;
				case (DIO_enuLOW):
					CLR_BIT(PORTB,LOc_u8PinNumber);
					break;
				default:
					Loc_enuErrorState =  DIO_enuNotOK;
			}
			break;
		case (DIO_PORTC):
			switch(cpy_enuPinValue){
				case (DIO_enuHIGH):
					SET_BIT(PORTC,LOc_u8PinNumber);
					break;
				case (DIO_enuLOW):
					CLR_BIT(PORTC,LOc_u8PinNumber);
					break;
				default:
					Loc_enuErrorState =  DIO_enuNotOK;
			}
			break;
		case (DIO_PORTD):
			switch(cpy_enuPinValue){
				case (DIO_enuHIGH):
					SET_BIT(PORTD,LOc_u8PinNumber);
					break;
				case (DIO_enuLOW):
					CLR_BIT(PORTD,LOc_u8PinNumber);
					break;
				default:
					Loc_enuErrorState =  DIO_enuNotOK;
			}
			break;
		default:
			Loc_enuErrorState =  DIO_enuNotOK;
		
	}
	return Loc_enuErrorState;
}


DIO_tenuErrorStatus DIO_enuSetDirection(DIO_tenuPins cpy_enuPinNumber,DIO_tenuDirections cpy_enuPinDir){
	u8 Loc_u8PortNumber = cpy_enuPinNumber/DIO_NumberOfPortPins;
	u8 LOc_u8PinNumber = cpy_enuPinNumber%DIO_NumberOfPortPins;
	DIO_tenuErrorStatus Loc_enuErrorState = DIO_enuOK;
	switch(Loc_u8PortNumber){
		case (DIO_PORTA):
		switch(cpy_enuPinDir){
			case (DIO_enuOUTPUT):
			SET_BIT(DDRA,LOc_u8PinNumber);
			break;
			case (DIO_enuINPUT):
			CLR_BIT(DDRA,LOc_u8PinNumber);
			break;
			default:
				Loc_enuErrorState =  DIO_enuNotOK;
			
		}
		break;
		case (DIO_PORTB):
		switch(cpy_enuPinDir){
			case (DIO_enuOUTPUT):
				SET_BIT(DDRB,LOc_u8PinNumber);
				break;
			case (DIO_enuINPUT):
				CLR_BIT(DDRB,LOc_u8PinNumber);
				break;
			default:
				Loc_enuErrorState =  DIO_enuNotOK;
			
		}
		break;
		case (DIO_PORTC):
		switch(cpy_enuPinDir){
			case (DIO_enuOUTPUT):
				SET_BIT(DDRC,LOc_u8PinNumber);
				break;
			case (DIO_enuINPUT):
				CLR_BIT(DDRC,LOc_u8PinNumber);
				break;
			default:
				Loc_enuErrorState =  DIO_enuNotOK;
			
		}
		break;
		
		case (DIO_PORTD):
		
			switch(cpy_enuPinDir){
				case (DIO_enuOUTPUT):
					SET_BIT(DDRD,LOc_u8PinNumber);
					break;
				case (DIO_enuINPUT):
					CLR_BIT(DDRD,LOc_u8PinNumber);
					break;
				default:
					Loc_enuErrorState =  DIO_enuNotOK;
			
			}
			break;
		default:
			Loc_enuErrorState =  DIO_enuNotOK;
		
	}
	return Loc_enuErrorState;
}


DIO_tenuErrorStatus DIO_enuGetPin(DIO_tenuPins cpy_enuPinNumber,DIO_tenuPinValue *Add_penuPinValue){
	u8 Loc_u8PortNumber = cpy_enuPinNumber/DIO_NumberOfPortPins;
	u8 LOc_u8PinNumber = cpy_enuPinNumber%DIO_NumberOfPortPins;
	DIO_tenuErrorStatus Loc_enuErrorState = DIO_enuOK;
	if(DIO_strPinCfg [cpy_enuPinNumber].DIO_PinDirection == DIO_enuINPUT && cpy_enuPinNumber>=0 && cpy_enuPinNumber<=31 )
	switch(Loc_u8PortNumber){
		case (DIO_PORTA):
			*Add_penuPinValue = GET_BIT(PINA,LOc_u8PinNumber);
			break;
		case (DIO_PORTB):
		
			*Add_penuPinValue = GET_BIT(PINB,LOc_u8PinNumber);
			break;
		case (DIO_PORTC):
		
			*Add_penuPinValue =GET_BIT(PINC,LOc_u8PinNumber);
			break;
		case (DIO_PORTD):
		
			*Add_penuPinValue =GET_BIT(PIND,LOc_u8PinNumber);
			break;
		default:
			Loc_enuErrorState =  DIO_enuNotOK;
		
	}
	else{
		Loc_enuErrorState =  DIO_enuNotOK;
	}
	return Loc_enuErrorState;
}


DIO_tenuErrorStatus DIO_enuTogPin(DIO_tenuPins cpy_enuPinNumber)
{
	u8 Loc_u8PortNumber = cpy_enuPinNumber/DIO_NumberOfPortPins;
	u8 LOc_u8PinNumber = cpy_enuPinNumber%DIO_NumberOfPortPins;
	DIO_tenuErrorStatus Loc_enuErrorState = DIO_enuOK;
	if(DIO_strPinCfg [cpy_enuPinNumber].DIO_PinDirection == DIO_enuOUTPUT)
	switch(Loc_u8PortNumber){
		case (DIO_PORTA):
			TGL_BIT(PORTA,LOc_u8PinNumber);
			break;
		case (DIO_PORTB):
		
			 TGL_BIT(PORTB,LOc_u8PinNumber);
			break;
		case (DIO_PORTC):
		
			TGL_BIT(PORTC,LOc_u8PinNumber);
			break;
		case (DIO_PORTD):
		
			TGL_BIT(PORTD,LOc_u8PinNumber);
			break;
		default:
		Loc_enuErrorState =  DIO_enuNotOK;
		
	}
	else{
		Loc_enuErrorState =  DIO_enuNotOK;
	}
	return Loc_enuErrorState;
}