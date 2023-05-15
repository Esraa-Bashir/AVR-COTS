/*
 * ICU.c
 *
 * Created: 3/11/2023 6:46:27 PM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "TMR1.h"
#include "TMR1_Cfg.h"
#include "TMR1_Prv.h"


#define FCPU		8000000UL
#define TMR1_Counts	65536
#define TMR1_TickTime_us	1
static u64 OverFolws_No=0;
static ICUCBF_t ICU_CBF= NULL;

TMR1_enuErrorStatus TMR1_enuSetOC1Mode (u8 Cpy_OC1PinNo , u8 Cpy_OC1Mode){
	TMR1_enuErrorStatus Loc_enuErrorStatus = TMR1_enuOk;
	if (Cpy_OC1Mode > TMR1_OC1Set)
	{
		Loc_enuErrorStatus = TMR1_enuNotOk;
	}
	else {
		switch (Cpy_OC1PinNo){
			case (TMR1_OC1A):
				TCCR1A_REG &= (OC1_clear << OC1A_shift);
				TCCR1A_REG |= (Cpy_OC1Mode << OC1A_shift);
				break;
			case (TMR1_OC1B):
				TCCR1A_REG &= (OC1_clear << OC1B_shift);
				TCCR1A_REG |= (Cpy_OC1Mode << OC1B_shift);
				break;
			default:
				Loc_enuErrorStatus = TMR1_enuNotOk;
		}
	}
	return Loc_enuErrorStatus;
	}
	
	
TMR1_enuErrorStatus TMR1_enuSetTimerMode (u8 Cpy_Mode){
	TMR1_enuErrorStatus Loc_enuErrorStatus = TMR1_enuOk;
	if (Cpy_Mode > TMR1_FastPWM_OCR1A)
	{
		Loc_enuErrorStatus = TMR1_enuNotOk;
	}
	else {
		TCCR1A_REG &=  Mode1_clear;
		TCCR1B_REG &=  Mode2_clear;
		TCCR1A_REG |=  (Cpy_Mode & Mode_split);
		TCCR1B_REG |=  ((Cpy_Mode & (~Mode_split))<< Mode_shift);
			
	}
	return Loc_enuErrorStatus;
}
	
TMR1_enuErrorStatus TMR1_enuICUSelectEdge(u8 Cpy_u8Edge) {
	TMR1_enuErrorStatus Loc_enuErrorStatus = TMR1_enuOk;
	if (Cpy_u8Edge !=ICU_FallingEdge_Trigger && Cpy_u8Edge !=ICU_RisingEdge_Trigger ){
		Loc_enuErrorStatus = TMR1_enuNotOk;
	}
	else {
		TCCR1B_REG &= (1<< ICES1_Pin) ;
		TCCR1B_REG |= (Cpy_u8Edge<< ICES1_Pin) ;
	}
	return Loc_enuErrorStatus;
}

TMR1_enuErrorStatus TMR1_enuSetPrescaler (u8 Cpy_Prescaler){
	TMR1_enuErrorStatus Loc_enuErrorStatus = TMR1_enuOk;
	if (Cpy_Prescaler > TMR1_ExternalClk_RisingEdge ){
		Loc_enuErrorStatus = TMR1_enuNotOk;
	}
	else {
		TCCR1B_REG &= Clk_clear ;
		TCCR1B_REG |= Cpy_Prescaler ;
	}
	return Loc_enuErrorStatus;

}	

	
u16 TMR1_u16GetICRValue(void)
{
	return ICR1_REG;
}

void TMR1_vidSetPreloadValue(u16 Cpy_u16Prelaod)
{
	TCNT1_REG = Cpy_u16Prelaod;
}

void TMR1_vidSetCompareValueA(u16 Cpy_u16Compare)
{
	OCR1A_REG = Cpy_u16Compare;
}

void TMR1_vidSetCompareValueB(u16 Cpy_u16Compare)
{
	OCR1B_REG = Cpy_u16Compare;
}

TMR1_enuErrorStatus TMR1_enuControlInterruptState(TMR1_enuInterruptSources Cpy_InterruptSource, u8 Cpy_InterruptState){
	TMR1_enuErrorStatus Loc_enuErrorStatus = TMR1_enuOk;
	if (Cpy_InterruptSource > TMR1_OverFlow_Interrupt || Cpy_InterruptState > TMR1_Interrupt_Enable){
		Loc_enuErrorStatus = TMR1_enuNotOk;
	}
	else {
		/* clear previous state*/
		TIMSK_REG &= ~(1<<(Cpy_InterruptSource+Interrupt_Shift));
		/* set new state */
		TIMSK_REG |= (Cpy_InterruptState<<(Cpy_InterruptSource+Interrupt_Shift));
	}
	return Loc_enuErrorStatus;
}

void ICU_SetCallBack(ICUCBF_t cbf){
	ICU_CBF = cbf;
}

void ICU_voidInit(void) {
	TMR1_enuControlInterruptState(TMR1_InputCapture_Interrupt, TMR1_Interrupt_Enable);
	TMR1_enuControlInterruptState(TMR1_OverFlow_Interrupt, TMR1_Interrupt_Enable);
	TMR1_enuICUSelectEdge(ICU_RisingEdge_Trigger);
	TMR1_enuSetPrescaler (TMR1_Clk_Div8);
}


/*capture event ISR*/
/*void __vector_6 (void)	__attribute__((signal));
void __vector_6 (void){
	if (ICU_CBF!=NULL){
	static u16 start,count,end;
	static u64 period,OnTime;
	count ++;
	if (count == 1)
	{	OverFolws_No =0;
		TCNT1_REG =0;
		//start =  TMR1_u16GetICRValue();
		TMR1_enuICUSelectEdge(ICU_FallingEdge_Trigger);
	}
	else if (count ==2)
	{
		end =  TMR1_u16GetICRValue();
		OnTime= (OverFolws_No * TMR1_Counts + end);
		TMR1_enuICUSelectEdge(ICU_RisingEdge_Trigger);
		
	}
	else if(count==3){
		count=0;
		end =  TMR1_u16GetICRValue();
		period= (OverFolws_No * TMR1_Counts + end);
		OverFolws_No =0;
		ICU_CBF((100*OnTime)/period, (period*TMR1_TickTime_us))	;
		TMR1_enuControlInterruptState(TMR1_InputCapture_Interrupt, TMR1_Interrupt_Disable);
		//TMR1_enuControlInterruptState(TMR1_InputCapture_Interrupt, TMR1_Interrupt_Disable);
		ICU_CBF= NULL;
	}
	}
}
*/
void __vector_6 (void)	__attribute__((signal));
void __vector_6 (void){
	if (ICU_CBF!=NULL){
		static u16 start,count,end;
		static u64 period,OnTime;
		count ++;
		if (count == 1)
		{	OverFolws_No =0;
			TCNT1_REG =0;
			start =  ICR1_REG;
			//TMR1_enuICUSelectEdge(ICU_FallingEdge_Trigger);
		}
		else if (count == 2){
			end = ICR1_REG;
			period =  end -start;
		OverFolws_No =0;
		TMR1_enuControlInterruptState(TMR1_InputCapture_Interrupt, TMR1_Interrupt_Disable);
		TMR1_enuControlInterruptState(TMR1_InputCapture_Interrupt, TMR1_Interrupt_Disable);
		count=0;
		ICU_CBF(0, (period*TMR1_TickTime_us))	;	
		}
		
	}
}

/*timer1 overfolw ISR*/
void __vector_9 (void)	__attribute__((signal));
void __vector_9 (void){
	
	OverFolws_No ++;
}