/*
 * Sched.c
 *
 * Created: 3/21/2023 8:44:09 AM
 *  Author: Esraa Beshir
 */ 


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/TIMER0/TMR0.h"
#include "Sched.h"
#include "Sched_cfg.h"

#define FCPU		8000000UL

typedef struct {
	TasksInfo_t * taskinfo;
	u32 remaining;
}Tasks_t;

Tasks_t tasks[Tasks_Number];

static void SchedCBF (void);
static void Sched (void);
u8 flag =0;
void Sched_Init(void){
	TMR0_vidInitPreCompile();
	TMR0_enuSetTickTimeMS(TickTime,FCPU);
	TMR0_enuRegisterCallback(SchedCBF);
	for(int idx=0;idx<Tasks_Number;idx++){
		tasks[idx].taskinfo= &TasksInfo[idx];
		tasks[idx].remaining = TasksInfo[idx].StartDelayms;
	}
}

void Sched_Start(void){
	TMR0_enuStart();
	while(1){
		if (flag==1)
		{
			Sched();
			flag=0;
		}
	}
}

static void SchedCBF (void){
	flag=1;
}

static void Sched (void){
	for(int idx=0;idx<Tasks_Number;idx++){
		if (tasks[idx].remaining==0)
		{
			tasks[idx].taskinfo->runnable();
			tasks[idx].remaining= tasks[idx].taskinfo->TaskPeriodms;

		}
		tasks[idx].remaining -= TickTime;
	}
}