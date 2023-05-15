/*
 * KEYPAD.c
 *
 * Created: 1/29/2023 11:22:22 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"

/* First initiallize the DIO then set the value of all cols to HIGH*/

KEYPAD_tenuErrorStatus KEYPAD_enuInit(void)
{
	KEYPAD_tenuErrorStatus  Loc_enuErrorStatus = KEYPAD_enuOK;
	Loc_enuErrorStatus =DIO_enuInit();
	u8 Loc_u8Counter ;
	for (Loc_u8Counter = KEYPAD_Rows_No; Loc_u8Counter <( KEYPAD_Rows_No + KEYPAD_Cols_No ); Loc_u8Counter++)
	{
		Loc_enuErrorStatus = DIO_enuSetValue(KEYPAD_PINS[Loc_u8Counter],DIO_enuHIGH);
	}
	return Loc_enuErrorStatus;
}

KEYPAD_tenuErrorStatus KEYPAD_enuGetValue (u8* Add_pu8ReturnValue)
{
	KEYPAD_tenuErrorStatus  Loc_enuErrorStatus = KEYPAD_enuOK;
	* Add_pu8ReturnValue = KEYPAD_No_Pressed_Key;
	u8 Loc_u8Value,Loc_u8Counter,Loc_u8Counter2;
	for (Loc_u8Counter = 0; Loc_u8Counter < KEYPAD_Cols_No;Loc_u8Counter++)
	{
		Loc_enuErrorStatus = DIO_enuSetValue(KEYPAD_PINS[Loc_u8Counter+KEYPAD_Rows_No],DIO_enuLOW);
		for (Loc_u8Counter2= 0; Loc_u8Counter2< KEYPAD_Rows_No;Loc_u8Counter2++)
		{
			DIO_enuGetPin(KEYPAD_PINS[Loc_u8Counter2],&Loc_u8Value);
			if (Loc_u8Value == DIO_enuLOW)
			{
				* Add_pu8ReturnValue = KEYPAD_Values[Loc_u8Counter2][Loc_u8Counter];
				/* wait untill the key is released */ 
				while (Loc_u8Value == DIO_enuLOW)
				{
					DIO_enuGetPin(KEYPAD_PINS[Loc_u8Counter2],&Loc_u8Value);
				}
			}
			
		}
		Loc_enuErrorStatus = DIO_enuSetValue(KEYPAD_PINS[Loc_u8Counter+KEYPAD_Rows_No],DIO_enuHIGH);
	}
	
	return Loc_enuErrorStatus;
}