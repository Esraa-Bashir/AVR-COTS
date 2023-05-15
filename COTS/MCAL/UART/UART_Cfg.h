/*
 * UART_Cfg.h
 *
 * Created: 3/26/2023 11:30:17 PM
 *  Author: Esraa Beshir
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_

#include <math.h>
#define FCPU			8000000UL
/****************************************************************************/
/* available BUAD rates:													*/
/* 2400 , 4800 , 9600 , 14.4k , 19.2K , 28.8K , 38.4K , 57.6K			    */
/* for speeds greater than or equal 8 M Hz you can also choose:			    */
/* 76.8K , 115.2K , 2304K , 250K , 0.5M									    */
/****************************************************************************/
#define BAUD_Rate		2400

#define UBRR_Value		((u16)(FCPU/(16.0*BAUD_Rate))-1)


/****************************************************************************/
/*choose the interrupts will be enabled, use (|) between them				*/
/*	 UART_CompleteRX_InterruptEnable										*/
/*	 UART_CompleteTX_InterruptEnable										*/
/*	 UART_DataRegEmpty_InterruptEnable										*/
/*	 UART_RX_InterruptEnable												*/
/*	 UART_TX_InterruptEnable												*/
/*	 UART_ALLInterruptEnable												*/
/****************************************************************************/
#define UART_Interrupts					(UART_TX_InterruptEnable | UART_CompleteTX_InterruptEnable)

/****************************************************************************/
/*choose the Parity mode, select between:									*/
/*	 UART_ParityDisable														*/
/*	 UART_ParityEven														*/
/*	 UART_ParityOdd															*/
/****************************************************************************/
#define UART_Parity					UART_ParityOdd

/****************************************************************************/
/*choose the number of stop bits, select between:							*/
/*	 UART_Stop_1Bit															*/
/*	 UART_Stop_2Bit															*/
/****************************************************************************/
#define UART_StopBits					UART_Stop_1Bit

/****************************************************************************/
/*choose the character size, select between:								*/
/*	 UART_CharSize_5Bit														*/
/*	 UART_CharSize_6Bit														*/
/*	 UART_CharSize_7Bit														*/
/*	 UART_CharSize_8Bit														*/
/****************************************************************************/
#define UART_CharSize					UART_CharSize_8Bit

/****************************************************************************/
/*choose the operation mode, select between:								*/
/*	 UART_AsyncOperation													*/
/*	 UART_SyncOperation														*/
/****************************************************************************/
#define UART_OpertationMode					UART_AsyncOperation

#endif /* UART_CFG_H_ */