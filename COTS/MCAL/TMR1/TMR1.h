/*
 * ICU.h
 *
 * Created: 3/11/2023 6:45:05 PM
 *  Author: Esraa Beshir
 */ 


#ifndef TMR1_H_
#define TMR1_H_

#define TMR1_OC1A						0
#define TMR1_OC1B						1

#define TMR1_Interrupt_Disable			0
#define TMR1_Interrupt_Enable			1

/*OC1A and OC1B avaliable modes*/
#define TMR1_OC1Disconnect				0
#define	TMR1_OC1Toggle					1
#define	TMR1_OC1Clear					2
#define	TMR1_OC1Set						3
#define	TMR1_OC1NonInverting			2
#define	TMR1_OC1Inverting				3

#define ICU_FallingEdge_Trigger			0
#define ICU_RisingEdge_Trigger			1

typedef void (*CBF_t) (void);
typedef void (*ICUCBF_t) (u64,u64);

typedef enum {
	TMR1_enuOk=0,
	TMR1_enuNotOk,
	TMR1_enuNullPtr,
}TMR1_enuErrorStatus;

typedef enum {
	TMR1_InputCapture_Interrupt=0,
	TMR1_CompareMatchA_Interrupt,
	TMR1_CompareMatchB_Interrupt,
	TMR1_OverFlow_Interrupt,
}TMR1_enuInterruptSources;

typedef enum {
	TMR1_NoClk=0,
	TMR1_Clk_Div1,
	TMR1_Clk_Div8,
	TMR1_Clk_Div64,
	TMR1_Clk_Div256,
	TMR1_Clk_Div1024,
	TMR1_ExternalClk_FallingEdge,
	TMR1_ExternalClk_RisingEdge,
}TMR1_enuClkPrescaler;

typedef enum {
	TMR1_Normal=0,
	TMR1_PWM_PhaseCorrect_8bit,
	TMR1_PWM_PhaseCorrect_9bit,
	TMR1_PWM_PhaseCorrect_10bit,
	TMR1_CTC_OCR1A_compare,
	TMR1_FastPWM_8bit,
	TMR1_FastPWM_9bit,
	TMR1_FastPWM_10bit,
	TMR1_PWM_PhaseFreqCorrect_ICR1,
	TMR1_PWM_PhaseFreqCorrect_OCR1A,
	TMR1_PWM_PhaseCorrect_ICR1,
	TMR1_PWM_PhaseCorrect_OCR1A,
	TMR1_CTC_ICR1_compare,
	TMR1_Reserved,
	TMR1_FastPWM_ICR1,
	TMR1_FastPWM_OCR1A,
}TMR1_enuModes;

TMR1_enuErrorStatus TMR1_enuSetOC1Mode (u8 Cpy_OC1PinNo , u8 Cpy_OC1Mode);
TMR1_enuErrorStatus TMR1_enuSetPrescaler (u8 Cpy_Prescaler);
TMR1_enuErrorStatus TMR1_enuSetTimerMode (u8 Cpy_Mode);
TMR1_enuErrorStatus TMR1_enuICUSelectEdge(u8 Cpy_u8Edge);
TMR1_enuErrorStatus TMR1_enuControlInterruptState(TMR1_enuInterruptSources Cpy_InterruptSource, u8 Cpy_InterruptState);
u16 TMR1_u16GetICRValue(void);
void TMR1_vidSetPreloadValue(u16 Cpy_u16Prelaod);
void TMR1_vidSetCompareValueA(u16 Cpy_u16Compare);
void TMR1_vidSetCompareValueB(u16 Cpy_u16Compare);
void ICU_SetCallBack(ICUCBF_t cbf);

#endif /* TMR1_H_ */