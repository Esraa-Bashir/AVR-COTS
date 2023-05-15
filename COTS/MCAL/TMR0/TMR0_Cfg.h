/*
 * TMR0_Cfg.h
 *
 * Created: 2/27/2023 3:08:16 PM
 *  Author: Esraa Beshir
 */ 


#ifndef TMR0_CFG_H_
#define TMR0_CFG_H_

/****************************************/
/*  options:							*/
/* 1- TMR0_Normal_Mode					*/	
/* 2- TMR0_CTC_Mode						*/	
/* 3- TMR0_PWMPhaseCorrect_Mode			*/	
/* 4- TMR0_FastPWM_Mode					*/	
/****************************************/
#define TMR0_Mode	TMR0_PWMPhaseCorrect_Mode	

/****************************************/
/*  options:							*/
/* 1- TMR0_Clk_Div1						*/
/* 2- TMR0_Clk_Div8						*/
/* 3- TMR0_Clk_Div64					*/
/* 4- TMR0_Clk_Div256					*/
/* 5- TMR0_Clk_Div1024					*/
/* 6- TMR0_ExternalClk_FallingEdge		*/
/* 7- TMR0_ExternalClk_RisingEdge		*/
/****************************************/
#define TMR0_Clk	TMR0_Clk_Div8

/****************************************/
/*  options:							*/
/* 1- TMR0_OC0Disconnect				*/
/* 2- TMR0_OC0Toggle					*/
/* 3- TMR0_OC0Clear						*/
/* 4- TMR0_OC0Set						*/
/****************************************/
#define OC0_PIN_Mode	TMR0_OC0ClearonCompare

#if (TMR0_Mode != TMR0_Normal_Mode )
	/*the compare value*/
	#define  TMR0_CompareMatchValue		0
#endif

#if (TMR0_Mode == TMR0_Normal_Mode)
/*the compare value*/
#define  TMR0_PreLoadValue		0
#endif

#endif /* TMR0_CFG_H_ */