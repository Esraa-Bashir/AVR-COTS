/*
 * SWITCH_Cfg.c
 *
 * Created: 1/30/2023 9:09:06 AM
 *  Author: Esraa Beshir
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include "SWITCH_Cfg.h"


const SWC_strCfg_t SWC_strCfg [SWC_enuNoOfSWCs]
= {
	/*SWC_NUMBER*/ /*PIN NUMBER*/ /*SWC PULL-UP or PULL-DOWN*/
	/*SWC0*/{DIO_enuPin8,DIO_INPUT_PULL_UP	},
	/*SWC1*/{DIO_enuPin9,DIO_INPUT_PULL_UP	},
	/*SWC2*/{DIO_enuPin10,DIO_INPUT_PULL_UP	},

	
};