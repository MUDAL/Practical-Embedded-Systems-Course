#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "pinmap.h"
#include "button.h"

namespace
{
	uint8_t i = 0;
	uint8_t j = 0;
	uint8_t k = 0;
};

int main(void)
{
	//variables
	pinStruct_t PC0 = {GPIOC,GPIO_PIN_0};
	pinStruct_t PC1 = {GPIOC,GPIO_PIN_1};
	pinStruct_t PC2 = {GPIOC,GPIO_PIN_13};
	
	System_Init();
	Button firstButton(PC0);
	Button secondButton(PC1);
	Button thirdButton(PC2);
	
	while(1)
	{
		if(firstButton.Pressed())
		{
			i++;
		}
		if(secondButton.Pressed())
		{
			j++;
		}
		if(thirdButton.Pressed())
		{
			k++;
		}		
	}
}

