/*
 * IncFile1.h
 *
 * Created: 3/21/2023 8:43:06 AM
 *  Author: Esraa Beshir
 */ 


#ifndef  SCHED_H_
#define SCHED_H_


typedef void (*RunnableCBF_t)(void);

void Sched_Init(void);
void Sched_Start(void);


#endif /*  SCHED_H_ */