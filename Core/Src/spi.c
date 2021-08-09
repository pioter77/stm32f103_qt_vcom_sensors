/**
  ******************************************************************************
  * @file    spi.c
  * @brief   This file provides code for the configuration
  *          of the SPI instances.
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

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

/* USER CODE BEGIN 0 */
   t_spi_ctrl spi2={
		  .is_answer_allowed=0,
		  .is_receive_complete=1,
		  .spi=SPI2,
		  .dma=DMA1,
		  .dmaTx=LL_DMA_CHANNEL_5,
		  .dmaRx=LL_DMA_CHANNEL_4,
  };
/* USER CODE END 0 */

/* SPI2 init function */
void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  LL_SPI_InitTypeDef SPI_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);

  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);
  /**SPI2 GPIO Configuration
  PB13   ------> SPI2_SCK
  PB14   ------> SPI2_MISO
  PB15   ------> SPI2_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13|LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_FLOATING;
  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* SPI2 DMA Init */

  /* SPI2_TX Init */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_5, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PRIORITY_LOW);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MDATAALIGN_BYTE);

  /* SPI2_RX Init */
  LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

  LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_MEDIUM);

  LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MODE_NORMAL);

  LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);

  LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);

  LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_BYTE);

  LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_BYTE);

  /* SPI2 interrupt Init */
  NVIC_SetPriority(SPI2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(SPI2_IRQn);

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV64;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 10;
  LL_SPI_Init(SPI2, &SPI_InitStruct);
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/* USER CODE BEGIN 1 */
void spi_half_init(t_spi_ctrl *spi){
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaTx));		//todo: tu moze byc problem bo  bylo basing intiger to a pointer
	LL_DMA_ClearFlag_TC5(spi->dma);
	LL_DMA_ClearFlag_TE5(spi->dma);
	LL_SPI_EnableDMAReq_TX(spi->spi);

	//rx:
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_ClearFlag_TC4(spi->dma);	//todo: this can ble ommited when porting when changed to function pointer in spi struct
	LL_DMA_ClearFlag_TE4(spi->dma);
	LL_SPI_EnableDMAReq_RX(spi->spi);
}
void spi_half_set_tx_data_len(t_spi_ctrl *spi, uint8_t len){
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaTx));
	LL_DMA_ClearFlag_TC5(spi->dma);
	LL_DMA_ClearFlag_TE5(spi->dma);
	LL_DMA_SetDataLength(spi->dma, spi->dmaTx, (uint32_t)len);
//	LL_DMA_ConfigAddresses(spi->dma, (uint32_t)(spi->dmaTx), (uint32_t)spi->txBuff, LL_SPI_DMA_GetRegAddr(spi->spi), LL_DMA_GetDataTransferDirection(spi->dma, (uint32_t)(spi->dmaTx)));
}
void spi_half_set_rx_data_len(t_spi_ctrl *spi, uint8_t len){
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_ClearFlag_TC4(spi->dma);	//todo: this can ble ommited when porting when changed to function pointer in spi struct
	LL_DMA_ClearFlag_TE4(spi->dma);
//	LL_DMA_ConfigAddresses(spi->dma, (uint32_t)(spi->dmaRx), LL_SPI_DMA_GetRegAddr(spi->spi), (uint32_t)spi->rxBuff, LL_DMA_GetDataTransferDirection(spi->dma, (uint32_t)(spi->dmaRx)));
		LL_DMA_SetDataLength(spi->dma, spi->dmaRx, (uint32_t)len);
}
void spi_half_enable(t_spi_ctrl *spi){
	LL_SPI_Enable(spi->spi);
}
void spi_half_disable(t_spi_ctrl *spi){
	LL_SPI_Disable(spi->spi);
}
void spi_half_dma_tx_enable(t_spi_ctrl *spi){
	//todo: tu bylo isrecivecompletew=0;
	spi->is_receive_complete=0;
	LL_DMA_EnableIT_TC(spi->dma,(uint32_t)(spi->dmaTx));
	LL_DMA_EnableIT_TE(spi->dma, (uint32_t)(spi->dmaTx));
	LL_GPIO_ResetOutputPin(MYSPI_CS_GPIO_Port, MYSPI_CS_Pin);
	LL_DMA_EnableChannel(spi->dma, (uint32_t)(spi->dmaTx));
}
void spi_half_dma_tx_disable(t_spi_ctrl *spi){
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaTx));
	LL_DMA_ClearFlag_TC5(spi->dma);
	LL_DMA_ClearFlag_TE5(spi->dma);
}
void spi_half_dma_rx_enable(t_spi_ctrl *spi){
	LL_DMA_EnableIT_TC(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_EnableIT_TE(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_EnableChannel(spi->dma, (uint32_t)(spi->dmaRx));
}
void spi_half_dma_rx_disable(t_spi_ctrl *spi){
	LL_DMA_DisableChannel(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_DisableIT_TC(spi->dma, (uint32_t)(spi->dmaRx));
	LL_DMA_DisableIT_TE(spi->dma, (uint32_t)(spi->dmaRx));
}
void spi_half_send(t_spi_ctrl *spi,uint8_t *tx_data,uint8_t tx_len){
	spi->is_answer_allowed=0;
	spi_half_disable(spi);
	spi_half_dma_rx_disable(spi);
	spi_half_dma_tx_disable(spi);
	LL_DMA_ConfigAddresses(spi->dma, (uint32_t)(spi->dmaTx), (uint32_t)tx_data, LL_SPI_DMA_GetRegAddr(spi->spi), LL_DMA_GetDataTransferDirection(spi->dma, (uint32_t)(spi->dmaTx)));
	spi_half_set_tx_data_len(spi, tx_len);
	spi_half_enable(spi);
	spi_half_dma_tx_enable(spi);
}
void spi_half_send_n_receive(t_spi_ctrl *spi,uint8_t *tx_data,uint8_t tx_len,uint8_t *rx_data,uint8_t rx_len){
	spi->is_answer_allowed=1;
	spi_half_disable(spi);
	spi_half_dma_rx_disable(spi);
	spi_half_dma_tx_disable(spi);

	spi_half_set_tx_data_len(spi, tx_len);
	LL_DMA_ConfigAddresses(spi->dma, (uint32_t)(spi->dmaTx), (uint32_t)tx_data, LL_SPI_DMA_GetRegAddr(spi->spi), LL_DMA_GetDataTransferDirection(spi->dma, (uint32_t)(spi->dmaTx)));
	//rx:
	spi_half_set_rx_data_len(spi, rx_len);
	LL_DMA_ConfigAddresses(spi->dma, (uint32_t)(spi->dmaRx), LL_SPI_DMA_GetRegAddr(spi->spi), (uint32_t)rx_data, LL_DMA_GetDataTransferDirection(spi->dma, (uint32_t)(spi->dmaRx)));
	spi_half_enable(spi);
	spi_half_dma_tx_enable(spi);
	spi_half_dma_rx_enable(spi);
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
