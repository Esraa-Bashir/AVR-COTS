/*
 * LCD.c
 *
 * Created: 2/10/2023 2:10:39 PM
 *  Author: Esraa Beshir
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include "LCD_Cfg.h"
#include <avr/delay.h>

void  LCD_vidInit  (){
	DIO_enuInit();
	_delay_ms(30);
	
	#if (LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x10 ||LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x10 || LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x7 || LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x7 )
		DIO_enuSetValue(RS_PIN, DIO_enuLOW);
		DIO_enuSetValue(RW_PIN, DIO_enuLOW);
		
		DIO_enuSetHalfPortValue(DATA_PORT,DATA_NIBBLE,LCD_FunctionSet >> 4);
		//DIO_enuSetPortValue(DATA_PORT,LCD_FunctionSet >> 4);
		DIO_enuSetValue(E_PIN, DIO_enuHIGH);
		 DIO_enuSetValue(E_PIN, DIO_enuLOW);
		_delay_ms(2);
	#endif
	LCD_enuSendCommand(LCD_FunctionSet);
	_delay_ms(1);
	LCD_enuSendCommand(LCD_DisplayControl);
	_delay_ms(1);
	LCD_enuSendCommand(LCD_DisplayClearCommand);
	_delay_ms(2);
	LCD_enuSendCommand(LCD_EntryMode);
}
LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command){
	LCD_enuErrorStatus Loc_enuErrorStatus;
	Loc_enuErrorStatus = DIO_enuSetValue(RS_PIN, DIO_enuLOW);
	Loc_enuErrorStatus = DIO_enuSetValue(RW_PIN, DIO_enuLOW);
	#if (LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x10 ||LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x10 || LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x7 || LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x7 )
	{
		Loc_enuErrorStatus = DIO_enuSetHalfPortValue(DATA_PORT,DATA_NIBBLE,Copy_u8Command>>4);
		Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuHIGH);
		Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuLOW);
		_delay_ms(2);
		Loc_enuErrorStatus = DIO_enuSetHalfPortValue(DATA_PORT,DATA_NIBBLE,Copy_u8Command & 0x0F);
		
	}
	#elif (LCD_FunctionSet == LCD_FunctionSet_8Bits_1Line_5x10 ||LCD_FunctionSet == LCD_FunctionSet_8Bits_2Line_5x10 || LCD_FunctionSet == LCD_FunctionSet_8Bits_1Line_5x7 || LCD_FunctionSet == LCD_FunctionSet_8Bits_2Line_5x7 )
	{
		Loc_enuErrorStatus = DIO_enuSetPortValue(DATA_PORT,Copy_u8Command);
	}
	#endif
	Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuHIGH);
	Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuLOW);
	_delay_ms(2);
	return Loc_enuErrorStatus;
}

LCD_enuErrorStatus LCD_enuClearScreen(void){
	
	LCD_enuErrorStatus Loc_enuErrorStatus= LCD_enuSendCommand(LCD_DisplayClearCommand);
	return Loc_enuErrorStatus;
}

LCD_enuErrorStatus LCD_enuSendData    (u8 Copy_u8Data){
	LCD_enuErrorStatus Loc_enuErrorStatus;
	Loc_enuErrorStatus = DIO_enuSetValue(RS_PIN, DIO_enuHIGH);
	Loc_enuErrorStatus = DIO_enuSetValue(RW_PIN, DIO_enuLOW);
	#if (LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x10 ||LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x10 || LCD_FunctionSet == LCD_FunctionSet_4Bits_1Line_5x7 || LCD_FunctionSet == LCD_FunctionSet_4Bits_2Line_5x7 )
	{
		Loc_enuErrorStatus = DIO_enuSetHalfPortValue(DATA_PORT,DATA_NIBBLE,Copy_u8Data>>4);
		Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuHIGH);
		Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuLOW);
		_delay_ms(2);
		Loc_enuErrorStatus = DIO_enuSetHalfPortValue(DATA_PORT,DATA_NIBBLE,Copy_u8Data & 0x0F);
		
	}
	#elif (LCD_FunctionSet == LCD_FunctionSet_8Bits_1Line_5x10 ||LCD_FunctionSet == LCD_FunctionSet_8Bits_2Line_5x10 || LCD_FunctionSet == LCD_FunctionSet_8Bits_1Line_5x7 || LCD_FunctionSet == LCD_FunctionSet_8Bits_2Line_5x7 )
	{
		Loc_enuErrorStatus = DIO_enuSetPortValue(DATA_PORT,Copy_u8Data);
	}
	#endif
	Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuHIGH);
	Loc_enuErrorStatus = DIO_enuSetValue(E_PIN, DIO_enuLOW);
	_delay_ms(2);
	return Loc_enuErrorStatus;
}

LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString){
	
	LCD_enuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
	u8 Loc_u8Iter=0;
	while (Add_pchString[Loc_u8Iter]!= '\0' && Loc_enuErrorStatus == LCD_enuOK  ){
		Loc_enuErrorStatus = LCD_enuSendData    (Add_pchString[Loc_u8Iter]);
		Loc_u8Iter ++;
	}
	return Loc_enuErrorStatus;
}

LCD_enuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number){
	LCD_enuErrorStatus Loc_enuErrorStatus = LCD_enuOK;
	u8 Loc_Au8Number[7];
	u8 Loc_u8Index =1,Loc_u8Iter;
	while (Copy_u16Number && Loc_enuErrorStatus == LCD_enuOK  ){
		Loc_Au8Number[Loc_u8Index]=(Copy_u16Number%10);
		Loc_u8Index ++ ;
		Copy_u16Number /= 10 ;
	}
	for(Loc_u8Iter = Loc_u8Index -1 ; Loc_u8Iter >0; Loc_u8Iter --){
		
		Loc_enuErrorStatus = LCD_enuSendData    (Loc_Au8Number[Loc_u8Iter]+'0' );
	}
	return Loc_enuErrorStatus;
	
}


LCD_enuErrorStatus LCD_enuGotoXY      (u8 Copy_u8XPos, u8 Copy_u8YPos){
	
	LCD_enuErrorStatus Loc_enuErrorStatus = LCD_enuNotOK;
	
	if ((Copy_u8XPos == 0 || Copy_u8XPos ==1) && (Copy_u8YPos >= 0 && Copy_u8YPos <=15 ) )
	{	u8 Loc_u8Command = (Copy_u8XPos * (0x40) + Copy_u8YPos )+128;
		LCD_enuSendCommand(Loc_u8Command );
		Loc_enuErrorStatus = LCD_enuOK;
	}
	
	return Loc_enuErrorStatus;
}

LCD_enuErrorStatus LCD_enuWriteSpecialPattern  (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos){
	
	LCD_enuErrorStatus Loc_enuErrorStatus = LCD_enuSendCommand (Copy_u8BlockNum*8 + 64)	;
	u8 Loc_u8Iter;
	for (Loc_u8Iter=0;Loc_u8Iter<8;Loc_u8Iter++){
		LCD_enuSendData(Add_pu8Pattern[Loc_u8Iter]);
	}
	LCD_enuGotoXY(Copy_u8XPos,Copy_u8YPos);
	LCD_enuSendData(Copy_u8BlockNum);
	return Loc_enuErrorStatus;
}