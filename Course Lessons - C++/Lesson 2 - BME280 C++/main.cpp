#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "bme280.h"

bme280Data_t bme280Data = {0};

int main(void)
{
	//Variables
	pinStruct_t SCL = {GPIOB,GPIO_PIN_8};
	pinStruct_t SDA = {GPIOB,GPIO_PIN_9};
	//Initializations
	System_Init();
	BME280 bme280(I2C1,SCL,SDA);
	
	while(1)
	{
		bme280Data = bme280.GetData();
		HAL_Delay(1000);
	}
}

