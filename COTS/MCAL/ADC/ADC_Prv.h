/*
 * ADC_Prv.h
 *
 * Created: 2/8/2023 4:32:47 PM
 *  Author: Esraa Beshir
 */ 


#ifndef ADC_PRV_H_
#define ADC_PRV_H_


#define ADMUX_REG		(*(volatile u8 *) (0x27))
#define ADCSRA_REG		(*(volatile u8 *) (0x26))
#define ADCH_REG		(*(volatile u8 *) (0x25))
#define ADCL_REG		(*(volatile u8 *) (0x24))
#define ADCDATA_REG		(*(volatile u16 *) (0x24))
#define SFIOR_REG		(*(volatile u8 *) (0x50))



#define VRefSelection_Mask 0x3F
#define ADLAR_PIN		5
#define AnalogChannel_Mask	0xE0

#define ADEN_PIN		7
#define ADSC_PIN		6
#define ADATE_PIN		5
#define ADIF_PIN		4
#define ADIE_PIN		3

#define Prescaler_Mask		0xF8
#define TriggerSource_Mask		0x1F




#endif /* ADC_PRV_H_ */