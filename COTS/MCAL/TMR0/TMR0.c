/*
 * TMR0.c
 *
 * Created: 2/27/2023 11:07:44 AM
 *  Author: Esraa Beshir
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TMR0.h"
#include "TMR0_Prv.h"
#include "TMR0_Cfg.h"

static u8 global_clkPrescaler;
static u8 global_TMRmode;
static u16 OverFlows_no =0;
static u8 preload_val=0;
TMR0cbf_t TMR0_CallBack = NULL;

void TMR0_vidInitPreCompile(void){
	/*set the timer mode*/
	TCCR0_REG &= Clear_Mode_Mask ;
	TCCR0_REG |= TMR0_Mode;
	global_TMRmode = TMR0_Mode;
	/*enable the interrupt*/
	#if (TMR0_Mode == TMR0_CTC_Mode)
		SET_BIT(TIMSK_REG,OCIE0_Pin);
		/*Set the compare value */
		OCR0_REG = TMR0_CompareMatchValue;
	#elif (TMR0_Mode == TMR0_Normal_Mode)
		SET_BIT(TIMSK_REG,TOIE0_Pin);
		TCNT0_REG = TMR0_PreLoadValue;
	#elif (TMR0_Mode == TMR0_PWMPhaseCorrect_Mode || TMR0_Mode == TMR0_FastPWM_Mode)
	SET_BIT(TIMSK_REG,TOIE0_Pin);
	SET_BIT(TIMSK_REG,OCIE0_Pin);
	OCR0_REG = TMR0_CompareMatchValue;
	#endif
	/*set OC0 PIN Mode */
	TCCR0_REG &= Clear_COM_Mode_Mask;
	TCCR0_REG |= OC0_PIN_Mode;
	/*set the CLK and Prescaler*/
	TCCR0_REG &= Clock_Reset_Mask;
	TCCR0_REG |= TMR0_NoClk	;
	global_clkPrescaler = TMR0_Clk;
	
}

void TMR0_vidInitPostCompile(TMR0Config_t Copy_strTMRCfg)
{
	TCCR0_REG &= Clear_TCCR0_RegMask;
	global_TMRmode = Copy_strTMRCfg.mode;
	if (Copy_strTMRCfg.mode == TMR0_Normal_Mode){
		SET_BIT(TIMSK_REG,TOIE0_Pin);
		TCCR0_REG |= TMR0_Normal_Mode;
		TCNT0_REG = Copy_strTMRCfg.PreLoadValue;
	}
	else if (Copy_strTMRCfg.mode == TMR0_CTC_Mode)
	{
		SET_BIT(TIMSK_REG,OCIE0_Pin);
		TCCR0_REG |= TMR0_CTC_Mode;
		/*Set the compare value */
	    OCR0_REG = Copy_strTMRCfg.compareValue;
	}
	else if (Copy_strTMRCfg.mode == TMR0_PWMPhaseCorrect_Mode || Copy_strTMRCfg.mode == TMR0_FastPWM_Mode){
		SET_BIT(TIMSK_REG,OCIE0_Pin);
		SET_BIT(TIMSK_REG,TOIE0_Pin);
		TCCR0_REG |= Copy_strTMRCfg.mode;
		/*Set the compare value */
	    OCR0_REG = Copy_strTMRCfg.compareValue;
	}
	TCCR0_REG |= Copy_strTMRCfg.OC0Mode;
	TCCR0_REG |= TMR0_NoClk	;
	global_clkPrescaler = Copy_strTMRCfg.clk;
}

TMR0_enuErrorStatus TMR0_enuStart(void){
	TCCR0_REG &= Clock_Reset_Mask;
	TCCR0_REG |= global_clkPrescaler	;
}


TMR0_enuErrorStatus TMR0_enuSetTickTimeMS( u32 Copy_u32DesiredTime,u64 Copy_sysClock){
	TMR0_enuErrorStatus  Loc_enuErrorStatus = TMR0_enuOk;
	f64 loc_prescaler=1;
	switch (global_clkPrescaler){
		case (TMR0_Clk_Div1):
			loc_prescaler=1;
			break;
		case (TMR0_Clk_Div8):
			loc_prescaler=8;
			break;
		case (TMR0_Clk_Div64):
			loc_prescaler=64;
			break;
		case (TMR0_Clk_Div256):
			loc_prescaler=256;
			break;
		case (TMR0_Clk_Div1024):
			loc_prescaler=1024;
			break;
		case (TMR0_ExternalClk_FallingEdge):
		case (TMR0_ExternalClk_RisingEdge):
			loc_prescaler=1;
			break;
		default :
			Loc_enuErrorStatus = TMR0_enuNotOk;	
	}
	if (Loc_enuErrorStatus == TMR0_enuOk){
		if (global_TMRmode  == TMR0_Normal_Mode){
			u32 timerfreq = (Copy_sysClock/1000)/loc_prescaler;
			f64 overflow = (Copy_u32DesiredTime)*(timerfreq/256.0);
			OverFlows_no = overflow ;
			preload_val = 256 *(1-(overflow - OverFlows_no));
			TCNT0_REG = preload_val;
			if (preload_val !=0){
				OverFlows_no ++;
			}
			else {
		
			}
		}else if (global_TMRmode  == TMR0_CTC_Mode){
			f64 timerfreq = (Copy_sysClock/1000)/loc_prescaler;
			u8 comparevalue = 255;
			while (comparevalue--){
				f64 overflow = (Copy_u32DesiredTime)*(timerfreq/comparevalue);
				if ((overflow - (u32)overflow)==0)
				{
					preload_val = 0;
					TCNT0_REG = preload_val;
					OverFlows_no = (Copy_u32DesiredTime)*(timerfreq/comparevalue);
					OCR0_REG = comparevalue;
					break;
				}
			}
		if (comparevalue==0){
			f64 overflow = (Copy_u32DesiredTime)*(timerfreq/256.0);
			OverFlows_no = overflow ;
			preload_val = 256 *(1-(overflow - OverFlows_no));
			TCNT0_REG = preload_val;
			if (preload_val !=0){
				OverFlows_no ++;
			}
			OCR0_REG = 255;
		}
		
		}	
	}
	else {
		
	}
	return Loc_enuErrorStatus;

}

TMR0_enuErrorStatus TMR0_enuSetDutyCycle( u32 Copy_u8Duty){
	TMR0_enuErrorStatus Loc_enuErrorStatus = TMR0_enuOk;
	u8 oc0_mode = TCCR0_REG & 0x30;
	u8 compare=0;
	if (global_TMRmode == TMR0_FastPWM_Mode ||global_TMRmode == TMR0_PWMPhaseCorrect_Mode  ){
		if (oc0_mode== TMR0_OC0SetonCompare){
			compare = 255 - (255 * Copy_u8Duty)/100;
			OCR0_REG = compare;
		}
		else if (oc0_mode== TMR0_OC0ClearonCompare){
			compare = (255 * Copy_u8Duty)/100;
			OCR0_REG = compare;
		}
		else {
			Loc_enuErrorStatus = TMR0_enuNotOk;
		}	
	}
	else{
		Loc_enuErrorStatus = TMR0_enuNotOk;
	}
	return Loc_enuErrorStatus;
}
void TMR0_vidSetPreloadValue(u8 Copy_u8Preload){
	TCNT0_REG = Copy_u8Preload;
	preload_val = Copy_u8Preload;
	
}
TMR0_enuErrorStatus TMR0_vidSetPrescaler(u8 Copy_u8Prescaler){
	TMR0_enuErrorStatus Loc_enuErrorStatus = TMR0_enuOk;
	if (Copy_u8Prescaler <= TMR0_ExternalClk_RisingEdge)
	{
		TCCR0_REG &= Clock_Reset_Mask;
		TCCR0_REG |= Copy_u8Prescaler;
		global_clkPrescaler = Copy_u8Prescaler;
	}
	else {
		Loc_enuErrorStatus = TMR0_enuNotOk;
	}
	return Loc_enuErrorStatus;
	
}
void TMR0_vidSetCompareValue(u8 Copy_u8compare){
	OCR0_REG = Copy_u8compare;
}
void TMR0_vidSetNoOfOverFlows(u8 Copy_u8noOverflow){
	OverFlows_no = Copy_u8noOverflow;
}

TMR0_enuErrorStatus TMR0_enuRegisterCallback(TMR0cbf_t CBF){
	
	TMR0_CallBack = CBF;
	return TMR0_enuOk;
}
static u16 COUNT=0;

void __vector_11 (void)	__attribute__((signal));
void __vector_11 (void)
{	SET_BIT(TIFR_REG,TOIE0_Pin);
	if(TMR0_CallBack != NULL)
	{   
		COUNT++;
		if (COUNT ==OverFlows_no )
		{
			TCNT0_REG = preload_val;
			TMR0_CallBack ();
			COUNT=0;
		}
		
	}
}

void __vector_10 (void)	__attribute__((signal));
void __vector_10 (void)
{	//SET_BIT(TIFR_REG,OCIE0_Pin);
	if(TMR0_CallBack != NULL)
	{
		COUNT++;
		if (COUNT ==OverFlows_no )
		{
			TCNT0_REG = preload_val;
			TMR0_CallBack ();
			COUNT=0;
		}
		
	}
}