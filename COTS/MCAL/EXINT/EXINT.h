/*
 * EXINT.h
 *
 * Created: 1/27/2023 8:27:34 AM
 *  Author: Esraa Beshir
 */ 


#ifndef EXINT_H_
#define EXINT_H_

#define EXINT_INT0	0
#define EXINT_INT1	1
#define EXINT_INT2	2

typedef enum
{
	EXINT_enuOK = 0,
	EXINT_enuNotOK ,
	EXINT_enuNullPtr
}EXINT_tenuErrorStatus;

/********************************/
/* EXTERNAL INTERRUPT INITIALIZATION function
	Input :void
	Output : EXINT_tenuErrorStatus to report errors */
/********************************/
EXINT_tenuErrorStatus EXINT_enuInit(void);
EXINT_tenuErrorStatus EXINT_enuEnable(u8 Copy_u8IntNo);
EXINT_tenuErrorStatus EXINT_enuDisable(u8 Copy_u8IntNo);
EXINT_tenuErrorStatus EXINT_enuSetCallBack(u8 Copy_u8IntNo,void (*Copy_Ptr) (void));

#endif /* EXINT_H_ */