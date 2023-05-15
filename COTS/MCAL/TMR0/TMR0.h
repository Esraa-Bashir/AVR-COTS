/*
 * TMR0.h
 *
 * Created: 2/27/2023 11:07:29 AM
 *  Author: Esraa Beshir
 */ 


#ifndef TMR0_H_
#define TMR0_H_

#define TMR0_Normal_Mode				0
#define TMR0_PWMPhaseCorrect_Mode		0x40
#define TMR0_CTC_Mode					0x08
#define TMR0_FastPWM_Mode				0x48
	
#define	TMR0_NoClk						0
#define	TMR0_Clk_Div1					1
#define	TMR0_Clk_Div8					2
#define	TMR0_Clk_Div64					3
#define	TMR0_Clk_Div256					4
#define	TMR0_Clk_Div1024				5
#define	TMR0_ExternalClk_FallingEdge	6
#define	TMR0_ExternalClk_RisingEdge		7
	
#define TMR0_OC0Disconnect				0
#define	TMR0_OC0Toggle					0x10
#define	TMR0_OC0Clear					0x20
#define	TMR0_OC0Set						0x30

#define	TMR0_OC0ClearonCompare			0x20
#define	TMR0_OC0SetonCompare			0x30

typedef void (*TMR0cbf_t) (void);

typedef enum {
	TMR0_enuOk=0,
	TMR0_enuNotOk,
	TMR0_enuNullPtr,
	}TMR0_enuErrorStatus;

typedef struct {
	u8 mode;
	u8 clk;
	u8 compareValue;
	u8 PreLoadValue;
	u8 OC0Mode;
}TMR0Config_t;
void TMR0_vidInitPreCompile(void);
void TMR0_vidInitPostCompile(TMR0Config_t);
TMR0_enuErrorStatus TMR0_enuSetTickTimeMS( u32 Copy_u32DesiredTime,u64 Copy_sysClock);
TMR0_enuErrorStatus TMR0_enuStart(void);
TMR0_enuErrorStatus TMR0_enuRegisterCallback(TMR0cbf_t);
TMR0_enuErrorStatus TMR0_enuSetDutyCycle( u32 Copy_u8Duty);
TMR0_enuErrorStatus TMR0_vidSetPrescaler(u8 Copy_u8Prescaler);
void TMR0_vidSetPreloadValue(u8 Copy_u8Preload);
void TMR0_vidSetCompareValue(u8 Copy_u8compare);
void TMR0_vidSetNoOfOverFlows(u8 Copy_u8noOverflow);

#endif /* TMR0_H_ */
