/*
 * Sched_cfg.h
 *
 * Created: 3/21/2023 8:44:56 AM
 *  Author: Esraa Beshir
 */ 


#ifndef SCHED_CFG_H_
#define SCHED_CFG_H_

#define Tasks_Number		2
#define TickTime	2
typedef struct {
	char* name;
	RunnableCBF_t runnable;
	u32 TaskPeriodms;
	u32 StartDelayms;

}TasksInfo_t;

extern const TasksInfo_t TasksInfo[Tasks_Number];



#endif /* SCHED_CFG_H_ */