/*
 * SPI.h
 *
 * Created: 4/7/2023 9:22:28 PM
 *  Author: Esraa Beshir
 */ 


#ifndef SPI_H_
#define SPI_H_


/* interrupt status */
#define SPI_InterruptEnable			0x80
#define SPI_InterruptDisable		0x00

/* Data order */
#define SPI_LSB_First				0x20
#define SPI_MSB_First				0x00

/* SPI mode */
#define SPI_Master					0x10
#define SPI_Slave					0x00

/* SPI Clock polarity */
#define SPI_SCK_Idle_High			0x08
#define SPI_SCK_Idle_Low			0x00

/* SPI Clock phase */
#define SPI_Sample_on_Trailing		0x04
#define SPI_Sample_on_Leading		0x00

/* SPI Clock rate */
#define SPI_Fosc_Div4_SpeedNormal	0x00
#define SPI_Fosc_Div2_Speed2x		0x00
#define SPI_Fosc_Div16_SpeedNormal	0x01
#define SPI_Fosc_Div8_Speed2x		0x01
#define SPI_Fosc_Div64_SpeedNormal	0x02
#define SPI_Fosc_Div32_Speed2x		0x02
#define SPI_Fosc_Div128_SpeedNormal	0x03
#define SPI_Fosc_Div64_Speed2x		0x03

/* SPI Speed */
#define SPI_SpeedNormal		0x00
#define SPI_Speed2x			0x01

typedef enum {
	SPI_enuOK=0,
	SPI_enuNotOK,
	SPI_enuNullPtr,
	}SPI_enuErrorStatus_t;
typedef struct {
	u8 InterruptStatus;
	u8 DataOrder;
	u8 Mode;
	u8 ClkPolarity;
	u8 ClkPhase;
	u8 ClkRate;
	u8 Speed;
	}SPI_strConfg_t;
	
typedef void (*SPI_CBF_t)(void);

void SPI_voidEnable	 (void);
void SPI_voidDisable (void);
SPI_enuErrorStatus_t SPI_enuInit(SPI_strConfg_t Spi_configuration);
SPI_enuErrorStatus_t SPI_enuSendSyncByte(u8 data);
SPI_enuErrorStatus_t SPI_enuRecieveSyncByte (u8 * data);
SPI_enuErrorStatus_t SPI_enuTransmitRecieveSyncByte (u8 TxData, u8 * RxData);
SPI_enuErrorStatus_t SPI_enuSetCallBack (SPI_CBF_t cbf);
SPI_enuErrorStatus_t SPI_enuSendAsyncByte(u8 data);
SPI_enuErrorStatus_t SPI_enuRecieveAsyncByte (u8 * data);
SPI_enuErrorStatus_t SPI_enuTransmitRecieveAsyncByte (u8 TxData, u8 * RxData);

#endif /* SPI_H_ */