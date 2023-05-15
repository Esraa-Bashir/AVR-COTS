/*
 * ADC.c
 *
 * Created: 2/8/2023 4:31:46 PM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "ADC.h"
#include "ADC_Cfg.h"
#include "ADC_Prv.h"
static ADC_tenuDataAdj_t  ADC_enugetDataAdj(void);

void ADC_Enable (void){
	SET_BIT(ADCSRA_REG,ADEN_PIN);
}

void ADC_Disable (void){
	CLR_BIT(ADCSRA_REG,ADEN_PIN);
}

ADC_tenuErrorStatus_t ADC_enuInit(void){
	ADC_Enable();
	ADC_tenuErrorStatus_t Loc_enuErrorStatus;
	Loc_enuErrorStatus = ADC_enusetReferenceVoltage(ADC_RefVolt);
	if (Loc_enuErrorStatus == ADC_enuOK)
	{
		Loc_enuErrorStatus = ADC_enusetDataAdj(ADC_DataAdjustment);
		if (Loc_enuErrorStatus == ADC_enuOK)
		{
			Loc_enuErrorStatus = ADC_enuclockConfiguration(ADC_Prescaler);
			if (Loc_enuErrorStatus == ADC_enuOK)
			{
				Loc_enuErrorStatus = ADC_enusetTriggerSource(ADC_Trigger);
				if (Loc_enuErrorStatus == ADC_enuOK)
				{
					Loc_enuErrorStatus = ADC_enuselectSingleEnddedChannel (ADC_InputChannel);
				}
				
			}
		}
	}
	return Loc_enuErrorStatus;
}

ADC_tenuErrorStatus_t ADC_enusetReferenceVoltage (ADC_tenuVRef_t cpy_enuReference)
{
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuNotOK;
	if (cpy_enuReference == ADC_enuInternal || cpy_enuReference == ADC_enuExternal || cpy_enuReference == ADC_enuAVCC )
	{
		u8 Loc_u8Reference = ADMUX_REG &  VRefSelection_Mask;
		Loc_u8Reference |= (cpy_enuReference << 6);
		ADMUX_REG = Loc_u8Reference;
		Loc_ErrorStatus = ADC_enuOK;
	}
	
	return Loc_ErrorStatus;
	
}

ADC_tenuErrorStatus_t ADC_enuselectSingleEnddedChannel (ADC_tenuSingleEnddedChannel_t cpy_enuchannel)
{
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuNotOK;
	if (cpy_enuchannel >= ADC_enuADC0 && cpy_enuchannel <= ADC_enuADC7 )
	{
		u8 Loc_u8channel= ADMUX_REG &  AnalogChannel_Mask;
		Loc_u8channel |= cpy_enuchannel ;
		ADMUX_REG = Loc_u8channel;
		Loc_ErrorStatus = ADC_enuOK;
	}
	
	return Loc_ErrorStatus;
	
}


ADC_tenuErrorStatus_t ADC_enuclockConfiguration (ADC_tenuPrescaler_t cpy_enuPrescaler)
{
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuNotOK;
	if (cpy_enuPrescaler >= ADC_enuPrescaler2 && cpy_enuPrescaler <= ADC_enuPrescaler128)
	{
		u8 Loc_Prescalermask = Prescaler_Mask & ADCSRA_REG;
		Loc_Prescalermask |=  cpy_enuPrescaler;
		ADCSRA_REG = Loc_Prescalermask;
		Loc_ErrorStatus = ADC_enuOK;
	}
	
	return Loc_ErrorStatus;
}
ADC_tenuErrorStatus_t ADC_enusetDataAdj (ADC_tenuDataAdj_t cpy_enuDataAdj )
{
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuOK;
	switch (cpy_enuDataAdj)
	{
		case ADC_enuLeft :
				SET_BIT(ADMUX_REG,ADLAR_PIN);
				break;
		case ADC_enuRight :
				CLR_BIT(ADMUX_REG,ADLAR_PIN);
				break;
		default:
			Loc_ErrorStatus = ADC_enuNotOK;
			
	}
	
	return Loc_ErrorStatus;
	
}

static ADC_tenuDataAdj_t  ADC_enugetDataAdj(void)
{
	u8 Loc_u8adjustment = GET_BIT(ADMUX_REG,ADLAR_PIN);
	ADC_tenuDataAdj_t  Loc_enuDataAdj;
	if (Loc_u8adjustment == 0)
	{
		Loc_enuDataAdj = ADC_enuRight;
	}
	else
	{
		Loc_enuDataAdj = ADC_enuLeft;
		
	}
	return Loc_enuDataAdj;
}


ADC_tenuErrorStatus_t ADC_enusetTriggerSource (ADC_tenuTriggerSource_t cpy_enuTriggerSource ){
	
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuNotOK;
	if (cpy_enuTriggerSource >= ADC_enuFreeRunning && cpy_enuTriggerSource <= ADC_enuTimer1CaptureEvent)
	{   SET_BIT(ADCSRA_REG,ADATE_PIN);
		u8 Loc_TriggerMask = TriggerSource_Mask & SFIOR_REG;
		Loc_TriggerMask |=  (cpy_enuTriggerSource<<5);
		SFIOR_REG= Loc_TriggerMask;
		Loc_ErrorStatus = ADC_enuOK;
	}
	else if (cpy_enuTriggerSource == ADC_enuSingleConversion)
	{
		CLR_BIT(ADCSRA_REG,ADATE_PIN);
		Loc_ErrorStatus = ADC_enuOK;
	}
	
	return Loc_ErrorStatus;
}

ADC_tenuErrorStatus_t ADC_enugetValue (ADC_tenuDataRes_t cpy_enuResolution , u16 * Add_u16ADCReadValue)
{
	ADC_tenuErrorStatus_t Loc_ErrorStatus = ADC_enuOK;
	ADC_tenuDataAdj_t Loc_enuDataAdj =   ADC_enugetDataAdj();
	u16 Loc_timeOut =30000;
	while((!GET_BIT(ADCSRA_REG,ADIF_PIN)) && (Loc_timeOut!=0))
	{
		Loc_timeOut--;
	}
	if (!Loc_timeOut)
	{
		 Loc_ErrorStatus = ADC_enuNotOK;
	}
	else
	{
	switch (cpy_enuResolution)
	{
		case ADC_enu8bit :
			
			if (Loc_enuDataAdj == ADC_enuLeft)
				{
					* Add_u16ADCReadValue = ADCH_REG;
				}
			else{
					* Add_u16ADCReadValue =((ADCDATA_REG & 0x3FF)>>2);
			}
			break;
		case ADC_enu10bit :
			
			if (Loc_enuDataAdj == ADC_enuLeft)
			{
				* Add_u16ADCReadValue = (ADCDATA_REG)>>6;
			}
			else{
				* Add_u16ADCReadValue =(ADCDATA_REG & 0x03FF);
			}
			break;
		default:
			Loc_ErrorStatus = ADC_enuNotOK;
	}
	}
	return Loc_ErrorStatus;
}

ADC_tenuErrorStatus_t ADC_enustartConversion (ADC_tenuSingleEnddedChannel_t cpy_enuchannel){
	ADC_tenuErrorStatus_t Loc_enuErrorStatus = ADC_enuselectSingleEnddedChannel(cpy_enuchannel);
	if (Loc_enuErrorStatus == ADC_enuOK)
	{
		SET_BIT(ADCSRA_REG,ADSC_PIN);
		CLR_BIT(ADCSRA_REG,ADIF_PIN);
	}
	return Loc_enuErrorStatus;
}