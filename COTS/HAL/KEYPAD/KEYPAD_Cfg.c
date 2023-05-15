/*
 * KEYPAD_Cfg.c
 *
 * Created: 1/29/2023 11:22:48 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "KEYPAD.h"
#include "KEYPAD_Cfg.h"

u8 KEYPAD_PINS[KEYPAD_Rows_No + KEYPAD_Cols_No]=
{
	/*ROW0 */ DIO_enuPin16,     
	/*ROW1*/ DIO_enuPin17,
	/*ROW2*/ DIO_enuPin18,
	/*ROW3*/ DIO_enuPin19,
	
	/*COL0*/DIO_enuPin20,
	/*COL1*/DIO_enuPin21,
	/*COL2*/DIO_enuPin22,
	/*COL3*/DIO_enuPin23,
};
u8 KEYPAD_Values[KEYPAD_Rows_No] [KEYPAD_Cols_No]=
{
	/*ROW0 VALUES*/ {7,8,9,10},
	/*ROW1 VALUES*/ {4,5,6,11},
	/*ROW2 VALUES*/ {1,2,3,12},
	/*ROW3 VALUES*/ {13,0,15,16}
		
};
