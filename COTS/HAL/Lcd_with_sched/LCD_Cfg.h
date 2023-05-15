


#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#define RS_PIN			DIO_enuPin0
#define RW_PIN			DIO_enuPin1
#define E_PIN			DIO_enuPin2

#define DATA_PORT		DIO_PORTB



/*
choose the function set between 
 LCD_FunctionSet_8Bits_1Line_5x7
 LCD_FunctionSet_8Bits_2Line_5x7
 LCD_FunctionSet_8Bits_1Line_5x10
 LCD_FunctionSet_8Bits_2Line_5x10

*/
#define LCD_FunctionSet	LCD_FunctionSet_8Bits_2Line_5x7

/*
   choose the display control from 
	LCD_DisplayControl_ON_CON_CBLink		
	LCD_DisplayControl_ON_CON_CNotBlink		
	LCD_DisplayControl_ON_COFF				
	LCD_DisplayControl_OFF					

*/

#define  LCD_DisplayControl	LCD_DisplayControl_ON_CON_CBLink	

/*
	choose the entry mode from 
	 LCD_EntryMode_Increase			
	 LCD_EntryMode_Decrease			
*/

#define	LCD_EntryMode	LCD_EntryMode_Increase	

#endif /* LCD_CFG_H_ */