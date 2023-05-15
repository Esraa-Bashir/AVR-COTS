/*
 * SSEG_Cfg.c
 *
 * Created: 1/20/2023 3:40:22 PM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO.h"
#include "SSEG.h"
#include "SSEG_Cfg.h"


const SSEG_strCfg_t SSEG_strCfg [SSEG_enuNumberOfSSEG] =
{
		{DIO_PORTA, SSEG_CommonAnode},
		{DIO_PORTB, SSEG_CommonAnode}
};