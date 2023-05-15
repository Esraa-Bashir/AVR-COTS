/*
 * UART.h
 *
 * Created: 3/26/2023 9:39:35 PM
 *  Author: Esraa Beshir
 */ 


#ifndef UART_H_
#define UART_H_

typedef void (*UART_CBF_t)(void);


void UART_enuInit(void);
void UART_enuSendAsyncByte(u8* data , UART_CBF_t cbf);
void UART_enuSendSyncByte(u8 data);
void UART_enuRecieveAsyncByte(u8 * data, UART_CBF_t cbf);
void UART_enuRecieveSyncByte (u8 * data);


#endif /* UART_H_ */