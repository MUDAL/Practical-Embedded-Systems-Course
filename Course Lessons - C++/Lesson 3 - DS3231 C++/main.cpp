#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "ds3231.h"

time_t time = {0};

int main(void)
{
	//Variables
	pinStruct_t SCL = {GPIOB,GPIO_PIN_8};
	pinStruct_t SDA = {GPIOB,GPIO_PIN_9};
	//Initializations
	System_Init();
	DS3231 ds3231(I2C1,SCL,SDA);
	//ds3231.SetFormat(TWELVE_HR_FORMAT_AM);
	//ds3231.SetTime(7,30);
	
	while(1)
	{
		time = ds3231.GetTime();
	}
}	

