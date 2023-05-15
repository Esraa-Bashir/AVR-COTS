/*
 * EXINT.c
 *
 * Created: 1/27/2023 8:26:59 AM
 *  Author: Esraa Beshir
 */ 
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "EXINT.h"
#include "EXINT_Cfg.h"
#include "EXINT_Prev.h"
#include "../GIE/GIE.h"

static void (*CBF [3])(void)={NULL,NULL,NULL};

EXINT_tenuErrorStatus EXINT_enuInit(void)
{	
	EXINT_tenuErrorStatus Loc_enuErrorState = EXINT_enuOK;
	Loc_enuErrorState = GIE_enuEnable();
	
	#if (INT0_EnableState==EXINT_Enable)
		SET_BIT(GICR_REG,INT0_PIN);
		#if (INT0_Sense_Control == EXINT_LowLevel )
			CLR_BIT(MCUCR_REG,ISC00_PIN);
			CLR_BIT(MCUCR_REG,ISC01_PIN);
		#elif (INT0_Sense_Control == EXINT_AnyChange )
			SET_BIT(MCUCR_REG,ISC00_PIN);
			CLR_BIT(MCUCR_REG,ISC01_PIN);
		#elif (INT0_Sense_Control == EXINT_FallingEdge )
			CLR_BIT(MCUCR_REG,ISC00_PIN);
			SET_BIT(MCUCR_REG,ISC01_PIN);
		#elif (INT0_Sense_Control == EXINT_RisingEdge )
			SET_BIT(MCUCR_REG,ISC00_PIN);
			SET_BIT(MCUCR_REG,ISC01_PIN);
		#else
			Loc_enuErrorState = EXINT_enuNotOK;
		#endif
	
	#elif (INT0_EnableState==EXINT_Disable)
		CLR_BIT(GICR_REG,INT0_PIN);
	#else
		Loc_enuErrorState = EXINT_enuNotOK;
	#endif
	
	
	#if (INT1_EnableState==EXINT_Enable)
		SET_BIT(GICR_REG,INT1_PIN);
		#if (INT1_Sense_Control == EXINT_LowLevel )
			CLR_BIT(MCUCR_REG,ISC10_PIN);
			CLR_BIT(MCUCR_REG,ISC11_PIN);
		#elif (INT1_Sense_Control == EXINT_AnyChange )
			SET_BIT(MCUCR_REG,ISC10_PIN);
			CLR_BIT(MCUCR_REG,ISC11_PIN);
		#elif (INT1_Sense_Control == EXINT_FallingEdge )
			CLR_BIT(MCUCR_REG,ISC10_PIN);
			SET_BIT(MCUCR_REG,ISC11_PIN);
		#elif (INT1_Sense_Control == EXINT_RisingEdge )
			SET_BIT(MCUCR_REG,ISC10_PIN);
			SET_BIT(MCUCR_REG,ISC11_PIN);
		#else
			Loc_enuErrorState = EXINT_enuNotOK;
		#endif
	
	#elif (INT1_EnableState==EXINT_Disable)
		CLR_BIT(GICR_REG,INT1_PIN);
	#else
		Loc_enuErrorState = EXINT_enuNotOK;
	#endif
	
	#if (INT2_EnableState==EXINT_Enable)
		SET_BIT(GICR_REG,INT2_PIN);
		#if (INT2_Sense_Control == EXINT_FallingEdge )
			CLR_BIT(MCUCSR_REG,ISC2_PIN);
		#elif (INT2_Sense_Control == EXINT_RisingEdge )
			SET_BIT(MCUCSR_REG,ISC2_PIN);
		#else
			Loc_enuErrorState = EXINT_enuNotOK;
		#endif
	
	#elif (INT2_EnableState==EXINT_Disable)
		CLR_BIT(GICR_REG,INT2_PIN);
	#else
		Loc_enuErrorState = EXINT_enuNotOK;
	#endif
	return Loc_enuErrorState;
	
}

EXINT_tenuErrorStatus EXINT_enuEnable(u8 Copy_u8IntNo){
	EXINT_tenuErrorStatus Loc_enuErrorState = EXINT_enuOK;
	switch (Copy_u8IntNo){
		case (EXINT_INT0):
			SET_BIT(GICR_REG,INT0_PIN);
			break;
		case (EXINT_INT1):
			SET_BIT(GICR_REG,INT1_PIN);
			break;
		case (EXINT_INT2):
			SET_BIT(GICR_REG,INT2_PIN);
			break;
		default:
			Loc_enuErrorState = EXINT_enuNotOK;
	}
	return Loc_enuErrorState;
}
EXINT_tenuErrorStatus EXINT_enuDisable(u8 Copy_u8IntNo){
	EXINT_tenuErrorStatus Loc_enuErrorState = EXINT_enuOK;
	switch (Copy_u8IntNo){
		case (EXINT_INT0):
			CLR_BIT(GICR_REG,INT0_PIN);
			break;
		case (EXINT_INT1):
			CLR_BIT(GICR_REG,INT1_PIN);
			break;
		case (EXINT_INT2):
			CLR_BIT(GICR_REG,INT2_PIN);
			break;
		default:
			Loc_enuErrorState = EXINT_enuNotOK;
	}
	return Loc_enuErrorState;
}
EXINT_tenuErrorStatus EXINT_enuSetCallBack(u8 Copy_u8IntNo,void (*Copy_Ptr) (void)){
	EXINT_tenuErrorStatus Loc_enuErrorState = EXINT_enuOK;
	if (Copy_u8IntNo > EXINT_INT2 || Copy_Ptr == NULL){
		Loc_enuErrorState = EXINT_enuNotOK;
	}
	else{
		CBF[Copy_u8IntNo]=Copy_Ptr;
	}
	return Loc_enuErrorState;
}

void __vector_1 (void)__attribute__((signal));
void __vector_1 (void)
{
	
	if(CBF[EXINT_INT0]!=NULL)
	{
		CBF[EXINT_INT0]();
	}
	
	
}
void __vector_2 (void)__attribute__((signal));
void __vector_2 (void)
{
	if(CBF[EXINT_INT1]!=NULL)
	{
		CBF[EXINT_INT1]();
	}
}
void __vector_3 (void)__attribute__((signal));
void __vector_3 (void)
{
	if(CBF[EXINT_INT2]!=NULL)
	{
		CBF[EXINT_INT2]();
	}
}