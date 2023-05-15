#ifndef LED_CFG_H
#define LED_CFG_H

//#include "../../LIB/STD_TYPES.h"


typedef struct {
	u8 LED_PinNumber;
	u8 LED_Polarity;
	
}LED_strCfg_t;

typedef enum {
	LED_enuLED0=0,  
	LED_enuLED1,
	LED_enuLED2,
	LED_enuLED3,
	LED_enuLED4,  
	LED_enuNoOfLeds
}LED_tenuLedNumber;

extern const LED_strCfg_t LED_strCfg [LED_enuNoOfLeds] ;

#endif /*LED_CFG_H*/
