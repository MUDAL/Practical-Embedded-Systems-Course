#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"

void System_Init(void)
{
	HAL_Init();
	  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}