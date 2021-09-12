#include "main.h"

bme280_t bme280Data = {0};

int main(void)
{
	//Initializations
	System_Init();
	BME280_Init();
	
	while(1)
	{
		BME280_GetData(&bme280Data);
		System_DelayMs(100);
	}
}
