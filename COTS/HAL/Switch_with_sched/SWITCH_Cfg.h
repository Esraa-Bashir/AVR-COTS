/*
 * SWITCH_Cfg.h
 *
 * Created: 1/30/2023 9:09:30 AM
 *  Author: Esraa Beshir
 */ 


#ifndef SWITCH_CFG_H_
#define SWITCH_CFG_H_

typedef struct {
	u8 SWC_PinNumber;
	u8 SWC_InputType;
	
}SWC_strCfg_t;

typedef enum {
	SWC_enuSWC0=0,
	SWC_enuSWC1,
	SWC_enuSWC2,
	SWC_enuNoOfSWCs
}SWC_tenuSWCNumber;

extern const SWC_strCfg_t SWC_strCfg [SWC_enuNoOfSWCs] ;



#endif /* SWITCH_CFG_H_ */