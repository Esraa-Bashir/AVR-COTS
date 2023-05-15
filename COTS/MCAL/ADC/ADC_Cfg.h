/*
 * ADC_Cfg.h
 *
 * Created: 2/8/2023 4:33:07 PM
 *  Author: Esraa Beshir
 */ 


#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/*  choose the reference voltage between ADC_enuExternal or ADC_enuAVCC or ADC_enuInternal */
#define ADC_RefVolt ADC_enuAVCC


/*  choose the data adjustment between ADC_enuLeft  or ADC_enuRight */
#define ADC_DataAdjustment  ADC_enuLeft


/*  choose the data bit resolution between ADC_enu8bit or ADC_enu10bit */
#define ADC_BitResolution  ADC_enu10bit


/*  choose the prescaler value between 
	ADC_enuPrescaler2 
	ADC_enuPrescaler4 
	ADC_enuPrescaler8  
	ADC_enuPrescaler16 
	ADC_enuPrescaler32 
	ADC_enuPrescaler64 
	ADC_enuPrescaler128  
	
 */

#define ADC_Prescaler  ADC_enuPrescaler2


/*  choose the Input channel between 
	ADC_enuADC0 
	ADC_enuADC1 
	ADC_enuADC2 
	ADC_enuADC3 
	ADC_enuADC4 
	ADC_enuADC5 
	ADC_enuADC6 
	ADC_enuADC7 
	
*/
#define ADC_InputChannel  ADC_enuADC0



/*  choose the Trigger source  between
	 ADC_enuFreeRunning 
	ADC_enuAnalogComparetor
	ADC_enuExternalInterrupt0
	ADC_enuTimer0CM
	ADC_enuTimer0OF
	ADC_enuTimer1CM
	ADC_enuTimer1OF
	ADC_enuTimer1CaptureEvent
	ADC_enuSingleConversion
 */
#define ADC_Trigger  ADC_enuFreeRunning



#endif /* ADC_CFG_H_ */