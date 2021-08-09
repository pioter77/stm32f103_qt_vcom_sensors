/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "stdio.h"
#include "bme280_lib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t mainBuff[B_SIZE]={0xf2,0,0,0,0,0,0,0,0,0,0,0,0,0,};
uint8_t data1[50]={"this is an example message\n"};
 uint8_t recBuffer[64];
 uint8_t recBufferSPI2[64];
_Bool isReceiveComplete=0;
_Bool isAnswerAllowed=0;
int _write(int file, char *ptr,int len)
{
	int i=0;
	for(i=0;i<len;i++)
		ITM_SendChar((*ptr++));
return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USB_DEVICE_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  LL_GPIO_SetOutputPin(Rel1_GPIO_Port, Rel1_Pin);
  LL_GPIO_SetOutputPin(Rel2_GPIO_Port, Rel2_Pin);
  LL_GPIO_SetOutputPin(Rel3_GPIO_Port, Rel3_Pin);
  LL_GPIO_SetOutputPin(Rel4_GPIO_Port, Rel4_Pin);
  uint8_t getdevid[2]={0xD0,0};
  uint8_t config_hum[2]={(0xF2 & 0x7F),0x02};
  uint8_t config_ctrl_meas[2]={(0xF4 & 0x7F),0x4B};
  uint8_t readburst3_fullbit[11]={0xF7,0,0,0,0,0,0,0,0,0,0};

  //set the bme 280

  spi_half_init(&spi2);
isReceiveComplete=1;
while(isReceiveComplete==0){	//wait for finishing
}

isAnswerAllowed=0;
spi_half_send(&spi2, getdevid,2);
while(isReceiveComplete==0);	//wait for finishing
isAnswerAllowed=0;
spi_half_send(&spi2, config_hum,2);

while(isReceiveComplete==0);	//wait for finishing
isAnswerAllowed=0;
spi_half_send(&spi2, config_ctrl_meas,2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	   CDC_Transmit_FS(data1,29);
	  while(isReceiveComplete==0){
		  //wait for finishing
	  }
//example
		isAnswerAllowed=1;
		spi_half_send_n_receive(&spi2, readburst3_fullbit, 10, recBufferSPI2, 10);

//	  	 	CDC_Transmit_FS(recBufferSPI2, 8);
	  switch (recBuffer[0]) {
		case 0x11:
			LL_GPIO_ResetOutputPin(Rel1_GPIO_Port, Rel1_Pin);
			break;
		case 0x01:
			LL_GPIO_SetOutputPin(Rel1_GPIO_Port, Rel1_Pin);
			break;
		case 0x12:
			LL_GPIO_ResetOutputPin(Rel2_GPIO_Port, Rel2_Pin);
			break;
		case 0x02:
			LL_GPIO_SetOutputPin(Rel2_GPIO_Port, Rel2_Pin);
			break;
		case 0x14:
			LL_GPIO_ResetOutputPin(Rel3_GPIO_Port, Rel3_Pin);
			break;
		case 0x04:
			LL_GPIO_SetOutputPin(Rel3_GPIO_Port, Rel3_Pin);
			break;
		case 0x18:
			LL_GPIO_ResetOutputPin(Rel4_GPIO_Port, Rel4_Pin);
			break;
		case 0x08:
			LL_GPIO_SetOutputPin(Rel4_GPIO_Port, Rel4_Pin);
			break;
		default:
			break;
	}
	  CDC_Transmit_FS(recBufferSPI2, 10);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);
  while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_2)
  {
  }
  LL_RCC_HSE_Enable();

   /* Wait till HSE is ready */
  while(LL_RCC_HSE_IsReady() != 1)
  {

  }
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
  LL_RCC_PLL_Enable();

   /* Wait till PLL is ready */
  while(LL_RCC_PLL_IsReady() != 1)
  {

  }
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

   /* Wait till System clock is ready */
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {

  }
  LL_SetSystemCoreClock(72000000);

   /* Update the time base */
  if (HAL_InitTick (TICK_INT_PRIORITY) != HAL_OK)
  {
    Error_Handler();
  }
  LL_RCC_SetUSBClockSource(LL_RCC_USB_CLKSOURCE_PLL_DIV_1_5);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
