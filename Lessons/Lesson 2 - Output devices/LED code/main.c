#include "main.h"

int main(void)
{
	//Initializations
	System_Init();
	LED_Init(NUMBER_OF_LEDS);
	
	while(1)
	{
		LED_Write(LED1,LED_ON);
		System_DelayMs(200);
		LED_Write(LED1,LED_OFF);
		System_DelayMs(200);
	}
}
