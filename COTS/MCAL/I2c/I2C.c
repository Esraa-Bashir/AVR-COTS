/*
 * I2C.c
 *
 * Created: 4/26/2023 10:42:37 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "I2C.h"
#include "I2C_Prev.h"

static enum {
	I2C_State_Ideal=0,
	I2C_state_Busy,
	}state= I2C_State_Ideal;

static enum {
	I2C_MasterSend=0,
	I2C_MasterReceive,
}Master_mode= I2C_MasterSend;
	
u8 *buffer = NULL;
u8 size=0;
u8 current_idx=0;
u8 address=0;

I2C_CBF_t CallBack_OK  = NULL;
I2C_CBF_t CallBack_NotOK  = NULL;

void I2C_voidDisable (void){
	TWCR &= ~(1<<TWEN);
}

I2C_enuErrorStatus_t I2C_enuInit(I2C_strConfg_t config){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	TWBR = config.BitRate;
	if (config.Prescaller > I2C_Prescaller_64)
	{
		Loc_Error =I2C_enuNotOK; 
	}
	else {
		TWSR |= config.Prescaller; 
	}
	
	if (config.GeneralCall != I2C_GeneralCall_Disable && config.GeneralCall != I2C_GeneralCall_Enable )
	{
		Loc_Error =I2C_enuNotOK; 
	}
	else {
		TWAR = (config.Address << 1) | config.GeneralCall;
	}
	
	
	return Loc_Error;
}
I2C_enuErrorStatus_t I2C_enuSetOkCallBack (I2C_CBF_t cbf){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (cbf ==NULL){
		Loc_Error =I2C_enuNullPtr;
	}
	else
	{
		CallBack_OK =cbf;
	}
	return Loc_Error;
}

I2C_enuErrorStatus_t I2C_enuSetNotOkCallBack (I2C_CBF_t cbf){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (cbf ==NULL){
		Loc_Error =I2C_enuNullPtr;
	}
	else
	{
		CallBack_NotOK =cbf;
	}
	return Loc_Error;
}

I2C_enuErrorStatus_t I2C_enuMasterSendBuffer (u8 * Cpy_buffer, u8 Cpy_size, u8 Cpy_address){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (state!= I2C_State_Ideal){
		Loc_Error =I2C_enuNotOK;
	}
	else if (buffer==NULL)
	{
		Loc_Error =I2C_enuNullPtr;
	}
	else{
		buffer= Cpy_buffer;
		size= Cpy_size;
		address = Cpy_address;
		current_idx =0;
		state = I2C_state_Busy;
		Master_mode = I2C_MasterSend;
		/* send start condition*/
		TWCR = I2C_SIGNAL_MW_START ;
	}

	return Loc_Error;
}
I2C_enuErrorStatus_t I2C_enuMasterReceiveBuffer (u8 * Cpy_buffer, u8 Cpy_size, u8 Cpy_address){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (state!= I2C_State_Ideal){
		Loc_Error =I2C_enuNotOK;
	}
	else if (buffer==NULL)
	{
		Loc_Error =I2C_enuNullPtr;
	}
	else{
		buffer= Cpy_buffer;
		size= Cpy_size;
		address = Cpy_address;
		current_idx =0;
		state = I2C_state_Busy;
		Master_mode = I2C_MasterReceive;
		/* send start condition*/
		TWCR = I2C_SIGNAL_MW_START ;
	}

	return Loc_Error;
}


I2C_enuErrorStatus_t I2C_enuSlaveSendBuffer (u8 * Cpy_buffer, u8 Cpy_size){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (state!= I2C_State_Ideal){
		Loc_Error =I2C_enuNotOK;
	}
	else if (buffer==NULL)
	{
		Loc_Error =I2C_enuNullPtr;
	}
	else{
		buffer= Cpy_buffer;
		size= Cpy_size;
		current_idx =0;
		state = I2C_state_Busy;
		/* enable interrupts*/
		TWCR = I2C_SIGNAL_SL_WRITE ;
	}

	return Loc_Error;
}
I2C_enuErrorStatus_t I2C_enuSlaveReceiveBuffer (u8 * Cpy_buffer, u8 Cpy_size){
	I2C_enuErrorStatus_t Loc_Error =I2C_enuOK;
	if (state!= I2C_State_Ideal){
		Loc_Error =I2C_enuNotOK;
	}
	else if (buffer==NULL)
	{
		Loc_Error =I2C_enuNullPtr;
	}
	else{
		buffer= Cpy_buffer;
		size= Cpy_size;
		current_idx =0;
		state = I2C_state_Busy;
		/* enable interrupts*/
		//TWCR = I2C_SIGNAL_SL_WRITE ;
	}

	return Loc_Error;
}
void __vector_19(void) __attribute__((signal));
void __vector_19(void)
{
	if (state == I2C_state_Busy){
		u8 Loc_state= TWSR & 0xF8;
		switch(Loc_state){
			case I2C_STATUS_MW_START_SEND  :
			case  I2C_STATUS_MW_REPETED_START:
				if(Master_mode == I2C_MasterSend){
					TWDR = (address <<1) ;
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_WRITE;
				}
				else if (Master_mode == I2C_MasterReceive){
					TWDR = (address <<1) | 0x01 ;
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_WRITE;
				}
				
				break;
			case I2C_STATUS_MW_SLA_W_ACK:
				TWDR = buffer[current_idx];
				current_idx++;
				/* clear flag*/
				TWCR = I2C_SIGNAL_MW_WRITE;
				break;
			case I2C_STATUS_MR_SLA_R_ACK:
				/* clear flag*/
				TWCR = I2C_SIGNAL_MW_WRITE;
				break;
			case I2C_STATUS_MW_DATA_ACK:
				if (current_idx== size)
				{   
					state = I2C_State_Ideal;
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_STOP ;
					if (CallBack_OK)
						CallBack_OK();
					
				}
				else {
					TWDR = buffer[current_idx];
					current_idx++;
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_WRITE;
				}
				break;
			case I2C_STATUS_MR_DATA_ACK:
				buffer[current_idx]=TWDR;
				current_idx ++;
				if (current_idx == size){
					state = I2C_State_Ideal;
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_STOP ;
					if (CallBack_OK)
					CallBack_OK();
				}
				else {
					/* clear flag*/
					TWCR = I2C_SIGNAL_MW_WRITE;
					
				}
				break;
			case I2C_STATUS_SR_SLA_W:
			case I2C_STATUS_SR_GEN_W :
				/* clear flag*/
				TWCR= I2C_SIGNAL_SL_WRITE;
				break;
			case I2C_STATUS_SR_SLA_DATA_RX_ACK:
			case I2C_STATUS_SR_GEN_DATA_RX_ACK:
				buffer[current_idx]= TWDR;
				current_idx ++;
				/* clear flag*/
				TWCR= I2C_SIGNAL_SL_WRITE;
				if (current_idx == size)
					{
						state = I2C_State_Ideal;
						if (CallBack_OK)
							CallBack_OK();
					}
				break;
			case I2C_STATUS_SW_SLA_R :
			case I2C_STATUS_SW_SLA_DATA_TX_ACK:
				TWDR = buffer[current_idx];
				current_idx++;
				/* clear flag*/
				TWCR= I2C_SIGNAL_SL_WRITE;
				if (current_idx==size){
					state = I2C_State_Ideal;
					if (CallBack_OK)
						CallBack_OK();
				}
			break;
			case I2C_STATUS_MW_SLA_W_NACK :
			case I2C_STATUS_MW_DATA_NACK:
			case I2C_STATUS_MR_SLA_R_NACK:
			case I2C_STATUS_MR_DATA_NACK:
			case I2C_STATUS_SR_SLA_DATA_RX_NACK:
			case I2C_STATUS_SR_GEN_DATA_RX_NACK:
			case I2C_STATUS_SW_SLA_DATA_TX_NACK:
			case I2C_STATUS_MW_ARBITRATION_LOST:
				/* clear flag*/
				TWCR = I2C_SIGNAL_MW_STOP ;
				if (CallBack_NotOK)
					CallBack_NotOK();
				break;	
		
		}
	}
	
}