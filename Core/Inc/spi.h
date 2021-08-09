/**
  ******************************************************************************
  * @file    spi.h
  * @brief   This file contains all the function prototypes for
  *          the spi.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define SPI_BUFF_LEN_TX 64
#define SPI_BUFF_LEN_RX 64
/* USER CODE END Private defines */

void MX_SPI2_Init(void);

/* USER CODE BEGIN Prototypes */


typedef struct T_spi_half{

	SPI_TypeDef *spi;
	DMA_TypeDef *dma;
	uint32_t dmaTx;			//dma tx channel macro
	uint32_t dmaRx;		//dma rx channel macro

	_Bool is_receive_complete;
	_Bool is_answer_allowed;

	uint8_t txBuff[SPI_BUFF_LEN_TX];
	uint8_t rxBuff[SPI_BUFF_LEN_RX];
}t_spi_ctrl;

extern t_spi_ctrl spi2;

void spi_half_init(t_spi_ctrl *spi);
void spi_half_set_tx_data_len(t_spi_ctrl *spi, uint8_t len);
void spi_half_set_rx_data_len(t_spi_ctrl *spi, uint8_t len);
void spi_half_enable(t_spi_ctrl *spi);
void spi_half_disable(t_spi_ctrl *spi);
void spi_half_send(t_spi_ctrl *spi,uint8_t *tx_data,uint8_t tx_len);
void spi_half_send_n_receive(t_spi_ctrl *spi,uint8_t *tx_data,uint8_t tx_len,uint8_t *rx_data,uint8_t rx_len);
void spi_half_dma_rx_disable(t_spi_ctrl *spi);
void spi_half_dma_rx_enable(t_spi_ctrl *spi);
void spi_half_dma_tx_disable(t_spi_ctrl *spi);
void spi_half_dma_tx_enable(t_spi_ctrl *spi);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
