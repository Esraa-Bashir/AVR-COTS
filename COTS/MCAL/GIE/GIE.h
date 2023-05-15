/*
 * GIE.h
 *
 * Created: 1/27/2023 7:54:53 AM
 *  Author: Esraa Beshir
 */ 


#ifndef GIE_H_
#define GIE_H_

typedef enum
{
	GIE_enuOK = 0,
	GIE_enuNotOK ,
	GIE_enuNullPtr
}GIE_tenuErrorStatus;


/********************************/
/* GIE Enable function
	Input :void
	Output : GIE_tenuErrorStatus to report errors */
/********************************/
GIE_tenuErrorStatus GIE_enuEnable(void);

/********************************/
/* GIE Disable function
	Input :void
	Output : GIE_tenuErrorStatus to report errors */
/********************************/
GIE_tenuErrorStatus GIE_enuDisable(void);



#endif /* GIE_H_ */