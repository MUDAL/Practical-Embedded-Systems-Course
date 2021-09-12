#include "main.h"

int main(void)
{
	//Initializations
	System_Init();
	LED led1(LED1);
	LED led2(LED2);
	LED led3(LED3);
	
	while(1)
	{
		led1.Toggle();
		System_DelayMs(500);
	}
}
