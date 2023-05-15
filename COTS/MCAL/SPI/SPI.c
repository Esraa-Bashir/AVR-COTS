/*
 * SPI.c
 *
 * Created: 4/7/2023 9:22:14 PM
 *  Author: Esraa Beshir
 */ 
#include "../../LIB/STD_TYPES.h"
#include "SPI.h"
#include "SPI_Prv.h"
static u16 TimeOut = 5000;
static u8 DummyData = 0xFF;
static u8* Recieved ;
static u8 TxOnly=0;

SPI_CBF_t SPI_cbf;

void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
	if( SPI_cbf != NULL)
	{   if (TxOnly!=1)
		{
				*Recieved = SPDR;
		
		}

		SPI_cbf();
	}
	else
	{
	}
}

void SPI_voidEnable	 (void){
	SPCR |= (1<<SPE_PIN);
}

void SPI_voidDisable (void){
	SPCR &= ~(1<<SPE_PIN);
}

SPI_enuErrorStatus_t SPI_enuInit(SPI_strConfg_t Spi_configuration){
	
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	/*if ((Spi_configuration.InterruptStatus != SPI_InterruptEnable && Spi_configuration.InterruptStatus != SPI_InterruptDisable)
		|| (Spi_configuration.DataOrder != SPI_LSB_First && Spi_configuration.DataOrder != SPI_MSB_First) 
		|| (Spi_configuration.Mode != SPI_Master && Spi_configuration.Mode != SPI_Slave ) 
		|| (Spi_configuration.ClkPolarity != SPI_SCK_Idle_High && Spi_configuration.ClkPolarity != SPI_SCK_Idle_Low )
		|| (Spi_configuration.ClkPhase != SPI_Sample_on_Trailing && Spi_configuration.ClkPhase != SPI_Sample_on_Leading )
		|| (Spi_configuration.ClkRate > SPI_Fosc_Div128_SpeedNormal )
		|| (Spi_configuration.Speed != SPI_SpeedNormal ||Spi_configuration.Speed != SPI_Speed2x ))
		{
			Loc_ErrorStatus = SPI_enuNotOK;
		}
		else*/ {
			 SPCR = Spi_configuration.InterruptStatus | Spi_configuration.DataOrder | Spi_configuration.Mode | Spi_configuration.ClkPhase
					| Spi_configuration.ClkPolarity | Spi_configuration.ClkRate ;
			 SPSR |= Spi_configuration.Speed;
			 /* Enable SPI */ 
			 SPCR |= (1<< SPE_PIN);
			
		}
	
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuSendSyncByte(u8 data){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
    u16 Loc_TimeOut = TimeOut;
	SPDR = data;
	while ((!((SPSR>>SPIF_PIN)&1))&& Loc_TimeOut--);
	if (Loc_TimeOut == 0)
	{
		Loc_ErrorStatus = SPI_enuNotOK;
	}
	else {
		
	}	
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuRecieveSyncByte (u8 * data){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	if (data == NULL)
	{
		Loc_ErrorStatus = SPI_enuNullPtr;
	}
	else {
	u16 Loc_TimeOut = TimeOut;
	SPDR = DummyData;
	while ((!((SPSR>>SPIF_PIN)&1))&& Loc_TimeOut--);
	if (Loc_TimeOut == 0)
	{
		Loc_ErrorStatus = SPI_enuNotOK;
	}
	else {
		*data = SPDR;
	}
	}
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuTransmitRecieveSyncByte (u8 TxData, u8 * RxData){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	if (RxData == NULL)
	{
		Loc_ErrorStatus = SPI_enuNullPtr;
	}
	else {
		u16 Loc_TimeOut = TimeOut;
		SPDR = TxData;
		while ((!((SPSR>>SPIF_PIN)&1))&& Loc_TimeOut--);
		if (Loc_TimeOut == 0)
		{
			Loc_ErrorStatus = SPI_enuNotOK;
		}
		else {
			*RxData = SPDR;
		}
	}
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuSetCallBack (SPI_CBF_t cbf){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	if (cbf == NULL)
	{
		Loc_ErrorStatus = SPI_enuNullPtr;
	}
	else {
		SPI_cbf = cbf;
	}
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuSendAsyncByte(u8 data){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;

	SPDR = data;
	TxOnly =1;

	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuRecieveAsyncByte (u8 * data){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	if (data == NULL)
	{
		Loc_ErrorStatus = SPI_enuNullPtr;
	}
	else {

		SPDR = DummyData;
		Recieved =data;
		TxOnly=0;

	}
	return Loc_ErrorStatus;
}

SPI_enuErrorStatus_t SPI_enuTransmitRecieveAsyncByte (u8 TxData, u8 * RxData){
	SPI_enuErrorStatus_t Loc_ErrorStatus = SPI_enuOK;
	if (RxData == NULL)
	{
		Loc_ErrorStatus = SPI_enuNullPtr;
	}
	else {

		SPDR = TxData;
		Recieved =RxData;
		TxOnly=0;

	}
	return Loc_ErrorStatus;
}