/*
 * SSG_Cfg.h
 *
 * Created: 1/20/2023 3:34:56 PM
 *  Author: Esraa Beshir
 */ 


#ifndef SSEG_CFG_H_
#define SSEG_CFG_H_





#define  SSEG_NoOfCharacters	10
extern const u8 SSEG_LookUpTable[SSEG_NoOfCharacters];

typedef enum {
	SSEG_CommonAnode =0,
	SSEG_CommonCathode
}SSEG_tenu_SSEGType;

typedef enum {
	SSEG_enuNo0 =0,
	SSEG_enuNo1 ,
	SSEG_enuNumberOfSSEG	
	}SSEG_tenu_SSEG;

typedef struct {
	DIO_tenuPorts SSEG_PORT;
	SSEG_tenu_SSEGType SSEG_TYPE;
	
}SSEG_strCfg_t;



extern const SSEG_strCfg_t SSEG_strCfg [SSEG_enuNumberOfSSEG] ;



#endif /* SSG_CFG_H_ */