/*
 * SSEG.c
 *
 * Created: 1/20/2023 3:24:59 PM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "SSEG_Cfg.h"
#include "SSEG.h"

#include <math.h>

const u8  SSEG_LookUpTable[SSEG_NoOfCharacters] = {
	
	[0] = 0b0111111,
	[1] = 0b0000110,
	[2] = 0b1011011,
	[3] = 0b1001111,
	[4] = 0b1100110,
	[5] = 0b1101101,
	[6] = 0b1111101,
	[7] = 0b0000111,
	[8] = 0b1111111,
	[9] = 0b1101111
	
};

SSEG_tenuErrorStatus SSEG_enuSetNumber(u8 cpy_u8Number)
{
	SSEG_tenuErrorStatus Loc_enuErrorStatus = SSEG_enuOK;
	/* check the number can be written on the number of 7 segements in the system */
	if (cpy_u8Number >=  pow(SSEG_NoOfCharacters ,SSEG_enuNumberOfSSEG))
	{
		Loc_enuErrorStatus = SSEG_enuNotOK;
	}
	else 
	{	u8	Loc_u8TempValToSSEGG ;
		u8 Loc_u8SSEGNumber =0;
		for(Loc_u8SSEGNumber =0; Loc_u8SSEGNumber <SSEG_enuNumberOfSSEG;Loc_u8SSEGNumber ++){
			if (SSEG_strCfg [Loc_u8SSEGNumber].SSEG_TYPE == SSEG_CommonAnode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [Loc_u8SSEGNumber].SSEG_PORT,(~SSEG_LookUpTable[0]) );
			}
			else if (SSEG_strCfg [Loc_u8SSEGNumber].SSEG_TYPE == SSEG_CommonCathode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [Loc_u8SSEGNumber].SSEG_PORT,SSEG_LookUpTable[0] );
			}
		}
		Loc_u8SSEGNumber =0;
		do {
			Loc_u8TempValToSSEGG = cpy_u8Number %10;
			
			if (SSEG_strCfg [Loc_u8SSEGNumber].SSEG_TYPE == SSEG_CommonAnode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [Loc_u8SSEGNumber].SSEG_PORT,(~SSEG_LookUpTable[Loc_u8TempValToSSEGG]) );
			}
			else if (SSEG_strCfg [Loc_u8SSEGNumber].SSEG_TYPE == SSEG_CommonCathode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [Loc_u8SSEGNumber].SSEG_PORT,SSEG_LookUpTable[Loc_u8TempValToSSEGG] );
			}
			else
			 {
					Loc_enuErrorStatus = SSEG_enuNotOK;
					break;
			}
			cpy_u8Number /=10;
			Loc_u8SSEGNumber ++;
		}	while(cpy_u8Number > 0);
	}
	return Loc_enuErrorStatus;
}


SSEG_tenuErrorStatus SSEG_enuSetNumberToSSEG(SSEG_tenu_SSEG cpy_enuSSEGNumber , u8 cpy_u8Number)
{
	SSEG_tenuErrorStatus Loc_enuErrorStatus = SSEG_enuOK;
	/* check the number can be written on the number of 7 segements in the system */
	if (cpy_u8Number >=  SSEG_NoOfCharacters || cpy_enuSSEGNumber >=SSEG_enuNumberOfSSEG )
	{
		Loc_enuErrorStatus = SSEG_enuNotOK;
	}
	else
	{	
			if (SSEG_strCfg [cpy_enuSSEGNumber].SSEG_TYPE == SSEG_CommonAnode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [cpy_enuSSEGNumber].SSEG_PORT,(~SSEG_LookUpTable[cpy_u8Number]) );
			}
			else if (SSEG_strCfg [cpy_enuSSEGNumber].SSEG_TYPE == SSEG_CommonCathode)
			{
				Loc_enuErrorStatus = DIO_enuSetPortValue(SSEG_strCfg [cpy_enuSSEGNumber].SSEG_PORT,SSEG_LookUpTable[cpy_u8Number] );
			}

	}
	return Loc_enuErrorStatus;
}