/*
 * ADC.h
 *
 * Created: 2/8/2023 4:32:08 PM
 *  Author: Esraa Beshir
 */ 


#ifndef ADC_H_
#define ADC_H_


typedef enum 
{
	ADC_enuPrescaler2=1,
	ADC_enuPrescaler4,
	ADC_enuPrescaler8,
	ADC_enuPrescaler16,
	ADC_enuPrescaler32,
	ADC_enuPrescaler64,
	ADC_enuPrescaler128
	}ADC_tenuPrescaler_t;
	
typedef enum {
	ADC_enuOK=0,
	ADC_enuNotOK,
	ADC_enuNULLPtr
	}ADC_tenuErrorStatus_t;
	
typedef enum {
	ADC_enu8bit=0,
	ADC_enu10bit
}ADC_tenuDataRes_t;

typedef enum {
	ADC_enuLeft=0,
	ADC_enuRight
}ADC_tenuDataAdj_t;

typedef enum {
	ADC_enuExternal=0,
	ADC_enuAVCC,
	ADC_enuInternal=3
}ADC_tenuVRef_t;
typedef enum {
	ADC_enuADC0=0,
	ADC_enuADC1,
	ADC_enuADC2,
	ADC_enuADC3,
	ADC_enuADC4,
	ADC_enuADC5,
	ADC_enuADC6,
	ADC_enuADC7
}ADC_tenuSingleEnddedChannel_t;

typedef enum {
	ADC_enuFreeRunning = 0,
	ADC_enuAnalogComparetor,
	ADC_enuExternalInterrupt0,
	ADC_enuTimer0CM,
	ADC_enuTimer0OF,
	ADC_enuTimer1CM,
	ADC_enuTimer1OF,
	ADC_enuTimer1CaptureEvent,
	ADC_enuSingleConversion
	}ADC_tenuTriggerSource_t;

void ADC_Enable (void);

void ADC_Disable (void);

ADC_tenuErrorStatus_t ADC_enuInit(void);

ADC_tenuErrorStatus_t ADC_enuclockConfiguration (ADC_tenuPrescaler_t cpy_enuPrescaler);

ADC_tenuErrorStatus_t ADC_enusetReferenceVoltage (ADC_tenuVRef_t cpy_enuReference);

ADC_tenuErrorStatus_t ADC_enuselectSingleEnddedChannel (ADC_tenuSingleEnddedChannel_t cpy_enuchannel);

ADC_tenuErrorStatus_t ADC_enustartConversion (ADC_tenuSingleEnddedChannel_t cpy_enuchannel);

ADC_tenuErrorStatus_t ADC_enusetDataAdj (ADC_tenuDataAdj_t cpy_enuDataAdj );

ADC_tenuErrorStatus_t ADC_enusetTriggerSource (ADC_tenuTriggerSource_t cpy_enuTriggerSource );

ADC_tenuErrorStatus_t ADC_enugetValue (ADC_tenuDataRes_t cpy_enuResolution , u16 * Add_u16ADCReadValue);


#endif /* ADC_H_ */