/*
 * I2C.h
 *
 * Created: 4/26/2023 10:42:23 AM
 *  Author: Esraa Beshir
 */ 


#ifndef I2C_H_
#define I2C_H_

#define I2C_Prescaller_1		0
#define I2C_Prescaller_4		1
#define I2C_Prescaller_16		2
#define I2C_Prescaller_64		3

#define I2C_GeneralCall_Enable		1
#define I2C_GeneralCall_Disable		0

typedef struct {
	u8 BitRate;/* value from 0 to 255*/
	u8 Prescaller;
	u8 Address;
	u8 GeneralCall;
}I2C_strConfg_t;

typedef enum {
	I2C_enuOK=0,
	I2C_enuNotOK,
	I2C_enuNullPtr,
}I2C_enuErrorStatus_t;

typedef void (*I2C_CBF_t)(void);
void I2C_voidDisable (void);
I2C_enuErrorStatus_t I2C_enuInit(I2C_strConfg_t config);
I2C_enuErrorStatus_t I2C_enuSetOkCallBack (I2C_CBF_t cbf);
I2C_enuErrorStatus_t I2C_enuSetNotOkCallBack (I2C_CBF_t cbf);
I2C_enuErrorStatus_t I2C_enuMasterSendBuffer (u8 * Cpy_buffer, u8 Cpy_size, u8 Cpy_address);
I2C_enuErrorStatus_t I2C_enuMasterReceiveBuffer (u8 * Cpy_buffer, u8 Cpy_size, u8 Cpy_address);
I2C_enuErrorStatus_t I2C_enuSlaveSendBuffer (u8 * Cpy_buffer, u8 Cpy_size);
I2C_enuErrorStatus_t I2C_enuSlaveReceiveBuffer (u8 * Cpy_buffer, u8 Cpy_size);

#endif /* I2C_H_ */