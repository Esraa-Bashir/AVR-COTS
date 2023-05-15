/*
 * Sched_cfg.c
 *
 * Created: 3/21/2023 8:44:35 AM
 *  Author: Esraa Beshir
 */ 

#include "../../LIB/STD_TYPES.h"
#include "Sched.h"
#include "Sched_cfg.h"

extern void App1_Task(void);
extern void App2_Task(void);
extern void App3_Task(void);
extern void App4_Task(void);
extern void App5_Task(void);
extern void LCD_Task(void);
extern void SWITCH_Task (void);

const TasksInfo_t TasksInfo[Tasks_Number]={
	
	[0]={
		.name = "LCD_Task",
		.runnable = LCD_Task,
		.TaskPeriodms = 2,
		.StartDelayms =0,
	},
	[1]={
		.name = "APP 5",
		.runnable = App5_Task,
		.TaskPeriodms = 500,
		.StartDelayms =0,
	},
	/*[0]={
		.name = "LCD runnable",
		.runnable = App1_Task,
		.TaskPeriodms = 250,
		.StartDelayms =0,
	},
	[1]={
		.name = "APP 5",
		.runnable = App2_Task,
		.TaskPeriodms = 500,
		.StartDelayms =0,
	},
	[2]={
		.name = "APP 5",
		.runnable = App3_Task,
		.TaskPeriodms = 2,
		.StartDelayms =0,
	},*/

};