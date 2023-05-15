/*
 * KEYPAD_Cfg.h
 *
 * Created: 1/29/2023 11:25:09 AM
 *  Author: Esraa Beshir
 */ 


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#define KEYPAD_Rows_No		4
#define KEYPAD_Cols_No		4

extern u8 KEYPAD_PINS[KEYPAD_Rows_No + KEYPAD_Cols_No];
extern u8 KEYPAD_Values[KEYPAD_Rows_No] [KEYPAD_Cols_No];

#endif /* KEYPAD_CFG_H_ */