#ifndef LED_H
#define LED_H

//#include "../DIO/DIO.h"
#include "LED_Cfg.h"
typedef enum {
	LED_enuActiveHigh=0,  /*LED ON when connecting 1 to the led */
	LED_enuActiveLow  /*LED ON when connecting 0 to the led */
}LED_tenuLedPolarity;

typedef enum
{
	LED_enuOK = 0,
	LED_enuNotOK ,
	LED_enuNullPtr
}LED_tenuErrorStatus;
/********************************/
/* LED Init Function
	Input :void
	Output : LED_tenuErrorStatus to report errors */
/********************************/
LED_tenuErrorStatus LED_enuInit(void);
/********************************/
/* LED turn on
	Input :led number
	Output : LED_tenuErrorStatus to report errors */
/********************************/
LED_tenuErrorStatus LED_enuLedOn(LED_tenuLedNumber cpy_enuLEDNumber);

/********************************/
/* LED turn off
	Input :led number
	Output : LED_tenuErrorStatus to report errors */
/********************************/
LED_tenuErrorStatus LED_enuLedOff(LED_tenuLedNumber cpy_enuLEDNumber);

/********************************/
/* Toggle LED  (if on turn it off and if led off turn it on )
	Input :led number 
	Output : LED_tenuErrorStatus to report errors */
/********************************/
LED_tenuErrorStatus LED_enuLedToggle(LED_tenuLedNumber cpy_enuLEDNumber);

#endif  /*LED_H*/