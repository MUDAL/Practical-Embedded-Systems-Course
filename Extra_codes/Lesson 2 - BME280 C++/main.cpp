#include "bme280.h"

bme280Data_t bme280Data = {0};

int main(void)
{
	HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();	
	
	pinStruct_t SCL = {GPIOB,GPIO_PIN_8};
	pinStruct_t SDA = {GPIOB,GPIO_PIN_9};
	
	static BME280 bme280(I2C1,SCL,SDA);
	
	while(1)
	{
		bme280Data = bme280.GetData();
		HAL_Delay(1000);
	}
}

extern "C" void SysTick_Handler(void)
{
  HAL_IncTick();
}


