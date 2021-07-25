/**
  ******************************************************************************
  * @file    dma.c
  * @brief   This file provides code for the configuration
  *          of all the requested memory to memory DMA transfers.
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
#include "dma.h"

/* USER CODE BEGIN 0 */
//void dma_init_tx(uint8_t count,uint8_t *buff)
//{
//
//
//	LL_SPI_EnableDMAReq_TX(SPI2);
//	LL_GPIO_ResetOutputPin(MYSPI_CS_GPIO_Port, MYSPI_CS_Pin);
//	LL_SPI_Enable(SPI2);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);	//wyslij dane
////	if(isAnswerAllowed)	LL_DMA_EnableChannel(DMA1, Channel)
//	isReceiveComplete=0;
//}
//
//void dma_init_rx(uint8_t count,uint8_t *buff)
//{
//
//		LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
//		LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_4);
//	  LL_SPI_EnableDMAReq_RX(SPI2);
////	  LL_SPI_Enable(SPI2);
//	  LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
//}

void spi_dma_tx_init(uint8_t count,uint8_t *buff)
{

	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
	LL_DMA_ClearFlag_TC5(DMA1);
	LL_DMA_ClearFlag_TE5(DMA1);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_5, (uint32_t)buff, LL_SPI_DMA_GetRegAddr(SPI2), LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_5));
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, (uint32_t)count);
	LL_SPI_EnableDMAReq_TX(SPI2);


}

void spi_dma_rx_init(uint8_t count,uint8_t *buff)
{
	 LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
	 LL_DMA_ClearFlag_TC4(DMA1);
	 LL_DMA_ClearFlag_TE4(DMA1);
	  LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4, LL_SPI_DMA_GetRegAddr(SPI2), (uint32_t)buff, LL_DMA_GetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4));
	  LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, (uint32_t)count);
	  LL_SPI_EnableDMAReq_RX(SPI2);

}

void spi_enable(SPI_TypeDef *spi){
//		LL_SPI_EnableDMAReq_TX(SPI2);
//			LL_SPI_EnableDMAReq_TX(SPI2);
	LL_SPI_Enable(spi);
}

void spi_disable(SPI_TypeDef *spi){
	LL_SPI_Disable(spi);
}

void spi_dma_tx_enable(void)
{

	isReceiveComplete=0;
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_5);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_5);
	LL_GPIO_ResetOutputPin(MYSPI_CS_GPIO_Port, MYSPI_CS_Pin);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);
}

void spi_dma_tx_disable(void)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_5);
	LL_DMA_ClearFlag_TC5(DMA1);
	LL_DMA_ClearFlag_TE5(DMA1);
}

void spi_dma_rx_enable(void)
{
	LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_4);
	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_4);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);
}

void spi_dma_rx_disable(void)
{
	LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
	LL_DMA_DisableIT_TC(DMA1, LL_DMA_CHANNEL_4);
	LL_DMA_DisableIT_TE(DMA1, LL_DMA_CHANNEL_4);
}
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure DMA                                                              */
/*----------------------------------------------------------------------------*/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Enable DMA controller clock
  */
void MX_DMA_Init(void)
{

  /* Init with LL driver */
  /* DMA controller clock enable */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  NVIC_SetPriority(DMA1_Channel4_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  NVIC_SetPriority(DMA1_Channel5_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
  NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
