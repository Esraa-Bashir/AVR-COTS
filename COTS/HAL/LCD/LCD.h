/*
 * LCD.h
 *
 * Created: 2/10/2023 2:10:55 PM
 *  Author: Esraa Beshir
 */ 


#ifndef LCD_H_
#define LCD_H_


#define LCD_DisplayClearCommand				0x01
#define LCD_ReturnHomeCommand				0x02

#define LCD_EntryMode_Increase			0x06
#define LCD_EntryMode_Decrease			0x04

#define LCD_FunctionSet_8Bits_1Line_5x7		0x30
#define LCD_FunctionSet_8Bits_2Line_5x7		0x38
#define LCD_FunctionSet_4Bits_1Line_5x7		0x20
#define LCD_FunctionSet_4Bits_2Line_5x7		0x28
#define LCD_FunctionSet_8Bits_1Line_5x10	0x34
#define LCD_FunctionSet_8Bits_2Line_5x10	0x3C
#define LCD_FunctionSet_4Bits_1Line_5x10	0x24
#define LCD_FunctionSet_4Bits_2Line_5x10	0x2C

#define	LCD_DisplayControl_ON_CON_CBLink		0x0F
#define	LCD_DisplayControl_ON_CON_CNotBlink		0x0E
#define	LCD_DisplayControl_ON_COFF				0x0C
#define	LCD_DisplayControl_OFF					0x08


typedef enum{
	LCD_enuOK=0,
	LCD_enuNotOK,
	LCD_enuNullPtr
	}LCD_enuErrorStatus;


void               LCD_vidInit        ();
LCD_enuErrorStatus LCD_enuSendData    (u8 Copy_u8Data);
LCD_enuErrorStatus LCD_enuSendCommand (u8 Copy_u8Command);
LCD_enuErrorStatus LCD_enuClearScreen(void);
LCD_enuErrorStatus LCD_enuGotoXY      (u8 Copy_u8XPos, u8 Copy_u8YPos);
LCD_enuErrorStatus LCD_enuWriteSpecialPattern  (u8* Add_pu8Pattern, u8 Copy_u8BlockNum, u8 Copy_u8XPos, u8 Copy_u8YPos);

LCD_enuErrorStatus LCD_enuWriteString (char* Add_pchString);
LCD_enuErrorStatus LCD_enuWriteNumber (u16 Copy_u16Number);



#endif /* LCD_H_ */