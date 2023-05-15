/*
 * UART_Prv.h
 *
 * Created: 3/26/2023 9:40:01 PM
 *  Author: Esraa Beshir
 */ 


#ifndef UART_PRV_H_
#define UART_PRV_H_

#define UDR			(*((volatile u8*) 0x2C))
#define UCSRA		(*((volatile u8*) 0x2B))
#define UCSRB		(*((volatile u8*) 0x2A))
#define UCSRC		(*((volatile u8*) 0x40))
#define UBRRH		(*((volatile u8*) 0x40))
#define UBRRL		(*((volatile u8*) 0x29))

#define RXC_Pin		7
#define TXC_Pin		6
#define UDRE_Pin	5
#define FE_Pin		4
#define DOR_Pin		3
#define PE_Pin		2

#define UART_CompleteRX_InterruptEnable			0x80
#define UART_CompleteTX_InterruptEnable			0x40
#define UART_DataRegEmpty_InterruptEnable		0x20
#define UART_RX_InterruptEnable					0x10
#define UART_TX_InterruptEnable					0x08
#define UART_ALLInterruptEnable					0xF8
#define UART_ParityDisable						0x00
#define UART_ParityEven							0x20
#define UART_ParityOdd							0x30
#define UART_Stop_1Bit							0x00
#define UART_Stop_2Bit							0x08
#define UART_CharSize_5Bit						0x00
#define UART_CharSize_6Bit						0x02
#define UART_CharSize_7Bit						0x04
#define UART_CharSize_8Bit						0x06
#define ClearRegSelect							0x7F
#define Select_UCSRC_Reg						0x80
#define Select_UBRRH_Reg						0x00
#define ClearOperationMode						(~(0x40))
#define UART_AsyncOperation						0x00
#define UART_SyncOperation						0x40

#endif /* UART_PRV_H_ */