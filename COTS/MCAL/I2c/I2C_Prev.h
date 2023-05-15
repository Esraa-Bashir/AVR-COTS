/*
 * I2C_Prev.h
 *
 * Created: 4/26/2023 10:39:08 AM
 *  Author: Esraa Beshir
 */ 


#ifndef I2C_PREV_H_
#define I2C_PREV_H_
/*  */
#define TWBR		(*((volatile u8*) 0x20))
#define TWCR		(*((volatile u8*) 0x56))
#define TWSR		(*((volatile u8*) 0x21))
#define TWDR		(*((volatile u8*) 0x23))
#define TWAR		(*((volatile u8*) 0x22))
/* interrupt flag pin ==> must be cleared by SW by writing 1 to it*/
#define TWINT		7

/* Enable ACK pin */
#define TWEA		6

/* master send start condition ==> must be cleared by SW */
#define TWSTA		5

/* master send stop condition */
#define TWSTO		4


/* Write collision flag  */
#define TWWC		3

/* Enable Pin */
#define TWEN		2

/* Interrupt Enable Pin */
#define TWIE		0

/* general call enable*/
#define TWGCE		0

#define I2C_SIGNAL_MW_START                     ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN) | (1 << TWIE)) | (1 << TWEA)
#define I2C_SIGNAL_MW_WRITE                     ((1 << TWINT) | (1 << TWEN) | (1 << TWIE)) | (1 << TWEA)
#define I2C_SIGNAL_MW_STOP                      ((1 << TWINT) | (1 << TWSTO) | (1 << TWEN) | (1 << TWIE)) | (1 << TWEA)
#define I2C_SIGNAL_SL_WRITE                     ((1 << TWINT) | (1 << TWEN) | (1 << TWIE)) | (1 << TWEA)

#define I2C_STATUS_MW_START_SEND                0x08
#define I2C_STATUS_MW_REPETED_START             0x10
#define I2C_STATUS_MW_SLA_W_ACK                 0x18
#define I2C_STATUS_MW_SLA_W_NACK                0x20
#define I2C_STATUS_MW_DATA_ACK                  0x28
#define I2C_STATUS_MW_DATA_NACK                 0x30
#define I2C_STATUS_MW_ARBITRATION_LOST          0x38

#define I2C_STATUS_MR_SLA_R_ACK                 0x40
#define I2C_STATUS_MR_SLA_R_NACK                0x48
#define I2C_STATUS_MR_DATA_ACK                  0x50
#define I2C_STATUS_MR_DATA_NACK                 0x58

#define I2C_STATUS_SR_SLA_W                     0x60
#define I2C_STATUS_SR_GEN_W                     0x70
#define I2C_STATUS_SR_SLA_DATA_RX_ACK			0x80
#define I2C_STATUS_SR_SLA_DATA_RX_NACK			0x88
#define I2C_STATUS_SR_GEN_DATA_RX_ACK			0x90
#define I2C_STATUS_SR_GEN_DATA_RX_NACK			0x98
#define I2C_STATUS_SR_STOP                      0xA0

#define I2C_STATUS_SW_SLA_R                     0xA8
#define I2C_STATUS_SW_SLA_DATA_TX_ACK			0xB8
#define I2C_STATUS_SW_SLA_DATA_TX_NACK			0xC0
#define I2C_STATUS_SW_LAST_DATA_TX_ACK			0xC8

#endif /* I2C_PREV_H_ */