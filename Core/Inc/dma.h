/**
  ******************************************************************************
  * @file    dma.h
  * @brief   This file contains all the function prototypes for
  *          the dma.c file
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
#ifndef __DMA_H__
#define __DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* DMA memory to memory transfer handles -------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_DMA_Init(void);

/* USER CODE BEGIN Prototypes */
void dma_init_tx(uint8_t count,uint8_t *buff);
void dma_init_rx(uint8_t count,uint8_t *buff);

void spi_dma_rx_enable(void);
void spi_dma_rx_disable(void);

void spi_dma_tx_enable(void);
void spi_dma_tx_disable(void);



void spi_disable(SPI_TypeDef *spi);
void spi_enable(SPI_TypeDef *spi);

void spi_dma_rx_init(uint8_t count,uint8_t *buff);
void spi_dma_tx_init(uint8_t count,uint8_t *buff);

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DMA_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
