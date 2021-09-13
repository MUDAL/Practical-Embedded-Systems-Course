#include "main.h"

int main(void)
{
	//Initializations
	System_Init();
	LED_Init(LED_PA5);
	LED_Init(LED_PC5);
	LED_Init(LED_PC6);
	
	while(1)
	{
		LED_Write(LED_PA5,LED_ON);
		System_DelayMs(1000);
		LED_Write(LED_PA5,LED_OFF);
		System_DelayMs(1000);
	}
}
