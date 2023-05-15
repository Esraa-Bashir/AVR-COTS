/*
 * KEYPAD.h
 *
 * Created: 1/29/2023 11:24:49 AM
 *  Author: Esraa Beshir
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEYPAD_No_Pressed_Key	0xff

typedef enum
{
	KEYPAD_enuOK = 0,
	KEYPAD_enuNotOK ,
	KEYPAD_enuNullPtr
}KEYPAD_tenuErrorStatus;


/********************************/
/* KEYPAD Init Function
	Input :void
	Output : KEYPAD_tenuErrorStatus to report errors */
/********************************/
KEYPAD_tenuErrorStatus KEYPAD_enuInit(void);

/********************************/
/* KEYPAD Get pressed key value function 
	Input :pointer to the variable to store the value of pressed key
	Output : KEYPAD_tenuErrorStatus to report errors */
/********************************/

KEYPAD_tenuErrorStatus KEYPAD_enuGetValue (u8* Add_pu8ReturnValue);


#endif /* KEYPAD_H_ */