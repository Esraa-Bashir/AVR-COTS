/*
 * UART.c
 *
 * Created: 3/26/2023 9:39:18 PM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "UART_Prv.h"
#include "UART.h"
#include "UART_Cfg.h"

static u8 Transmit_Byte;
static u8 *Receive_Byte ;
UART_CBF_t TXC_CBF=NULL;
UART_CBF_t RXC_CBF=NULL;

/* RX complete ISR*/
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if( RXC_CBF != NULL)
	{   *Receive_Byte = UDR;
		RXC_CBF();
	}
	else
	{
	}
}



/* TX complete ISR*/
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if( TXC_CBF != NULL)
	{   
		TXC_CBF();
	}
	else
	{
	}
}


void UART_enuInit(void){
/* Enable the interrupts*/
	UCSRB = UART_Interrupts ;
	/* set the character size , number of stop bits , Parity mode , operation mode*/
	UCSRC &= ClearRegSelect;
	UCSRC |= Select_UCSRC_Reg;
	UCSRC |= UART_CharSize | UART_StopBits |UART_Parity | UART_OpertationMode;
	/*set UBRR value according to BAUD rate*/
	if (UBRR_Value < 256){
		UBRRL = UBRR_Value;
	}
	else {
		UBRRL = UBRR_Value & 0xFF;
		UCSRC &= ClearRegSelect;
		UCSRC |= Select_UBRRH_Reg;
		UCSRC |= (UBRR_Value)>>8;
	}
	
}

void UART_enuSendSyncByte(u8 data){
	u64 timeout =5000;
	/* wait until the transmit buffer is empty*/
	while (!(UCSRA&(1<<UDRE_Pin)) && timeout--);
	/* write the data to transmit to the buffer*/
	UDR = data;
	UCSRA &= ~(1<<UDRE_Pin);
}

void UART_enuRecieveSyncByte (u8 * data){
	u64 timeout =5000;
	/* wait until the receiving is complete */
	while (!(UCSRA&(1<<RXC_Pin))&& timeout--);
	/* write received data to the variable*/
	*data = UDR;
	UCSRA &= ~(1<<RXC_Pin);
}

void UART_enuSendAsyncByte(u8 *data , UART_CBF_t cbf){
	UDR =*data;
	TXC_CBF =cbf;
}

void UART_enuRecieveAsyncByte(u8 * data, UART_CBF_t cbf){
	Receive_Byte=data;
	RXC_CBF= cbf;
}
