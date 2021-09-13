#include "main.h"

int main(void)
{
	//Initializations
	System_Init();
	LED led1(LED_PA5);
	LED led2(LED_PC5);
	LED led3(LED_PC6);
	
	while(1)
	{
		led1.Toggle();
		System_DelayMs(500);
	}
}
