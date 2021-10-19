#include "ds3231.h"

time_t time = {0};

int main(void)
{
	HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_I2C1_CLK_ENABLE();
	//Variables
	pinStruct_t SCL = {GPIOB,GPIO_PIN_8};
	pinStruct_t SDA = {GPIOB,GPIO_PIN_9};

	static DS3231 ds3231(I2C1,SCL,SDA);
	ds3231.SetFormat(TWELVE_HR_FORMAT_AM);
	ds3231.SetTime(7,30);
	
	while(1)
	{
		time = ds3231.GetTime();
	}
}	

extern "C" void SysTick_Handler(void)
{
  HAL_IncTick();
}

