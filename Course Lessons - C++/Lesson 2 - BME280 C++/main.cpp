#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "bme280.h"

uint8_t temperature = 0;
uint8_t humidity = 0;

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
		temperature = bme280.GetTemperature();
		humidity = bme280.GetHumidity();
		HAL_Delay(1000);
	}
}

