/*
 * Servo.c
 *
 * Created: 3/10/2023 2:37:43 PM
 *  Author: Esraa Beshir
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/TMR0/TMR0.h"
#define Max_duty	12.2
#define Min_duty	6.1


void Servo_voidInit(void){
	TMR0Config_t configuration;
	configuration.mode=TMR0_PWMPhaseCorrect_Mode;
	configuration.compareValue=64;
	configuration.PreLoadValue= 0;
	configuration.clk = TMR0_Clk_Div256;
	configuration.OC0Mode = TMR0_OC0ClearonCompare;
	TMR0_vidInitPostCompile(configuration);
	TMR0_enuStart();
}

void Servo_SetDegree(u8 Cpy_u8Degree){
	if (Cpy_u8Degree >=0 && Cpy_u8Degree<= 180){
		f64 duty = ((Cpy_u8Degree*(Max_duty-Min_duty))/180) + Min_duty;
		TMR0_enuSetDutyCycle(duty);
	}
}