#ifndef DIO_H
#define DIO_H

#include "../../LIB/STD_TYPES.h"

#define DIO_NumberOfPortPins	8

#define DIO_INPUT_PULL_UP		0
#define DIO_INPUT_PULL_DOWN		1

typedef enum
{	DIO_enuINPUT =0,
	 DIO_enuOUTPUT
}DIO_tenuDirections;

typedef enum
{	DIO_PORTA =0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD,
	DIO_enuNumberOfPorts	
}DIO_tenuPorts;

typedef enum 
{
	DIO_enuOK = 0,
	DIO_enuNotOK ,
	DIO_enuNullPtr
}DIO_tenuErrorStatus;
	
typedef enum 
{
	DIO_enuPin0,
	DIO_enuPin1,
	DIO_enuPin2, 
	DIO_enuPin3 ,
	DIO_enuPin4 ,
	DIO_enuPin5 ,
	DIO_enuPin6 ,
	DIO_enuPin7 ,
	DIO_enuPin8,
	DIO_enuPin9,
	DIO_enuPin10,
	DIO_enuPin11,
	DIO_enuPin12,
	DIO_enuPin13,
	DIO_enuPin14,
	DIO_enuPin15,
	DIO_enuPin16,
	DIO_enuPin17,
	DIO_enuPin18,
	DIO_enuPin19,
	DIO_enuPin20,
	DIO_enuPin21,
	DIO_enuPin22,
	DIO_enuPin23,
	DIO_enuPin24,
	DIO_enuPin25,
	DIO_enuPin26,
	DIO_enuPin27,
	DIO_enuPin28,
	DIO_enuPin29,
	DIO_enuPin30,
	DIO_enuPin31,
	DIO_enuNumberOfPins
	
}DIO_tenuPins;

typedef enum {
	DIO_enuLOW=0,
	DIO_enuHIGH
}DIO_tenuPinValue;
/********************************/
/* DIO Init Function
	Input :void
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuInit(void);

/********************************/
/* DIO set pin  value
	Input :Pin number (range from 0 to 31)and pin value (DIO_enuHIGH or DIO_enuLOW)
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuSetValue(DIO_tenuPins cpy_enuPinNumber,DIO_tenuPinValue cpy_enuPinValue);

/********************************/
/* DIO set port  value
	Input :Port number (range from 0 to 3 --> PORTA PORTB PORTC PORTD)and port value
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuSetPortValue(DIO_tenuPorts cpy_enuPortNumber,u8 cpy_enuPortValue);

/********************************/
/* DIO Set pin direction
	Input :Pin number (range from 0 to 31) and pin direction (DIO_enuINPUT or DIO_enuOUTPUT)
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuSetDirection(DIO_tenuPins cpy_enuPinNumber,DIO_tenuDirections cpy_enuPinDir);

/********************************/
/* DIO get pin s
	Input :Pin number (range from 0 to 31) and pointer to store the get value 
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuGetPin(DIO_tenuPins cpy_enuPinNumber,DIO_tenuPinValue *Add_penuPinValue);


/********************************/
/* DIO Toggle Pin
	Input :Pin number (range from 0 to 31) 
	Output : DIO_tenuErrorStatus to report errors */
/********************************/
DIO_tenuErrorStatus DIO_enuTogPin(DIO_tenuPins cpy_enuPinNumber);

#endif  /*DIO_H*/