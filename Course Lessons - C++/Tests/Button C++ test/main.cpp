#include "button.h"

uint8_t i = 0;
uint8_t j = 0;
uint8_t k = 0;

int main(void)
{
	HAL_Init();
	  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
	
	//variables
	pinStruct_t PC0 = {GPIOC,GPIO_PIN_0};
	pinStruct_t PC1 = {GPIOC,GPIO_PIN_1};
	pinStruct_t PC2 = {GPIOC,GPIO_PIN_13};
	
	static Button firstButton(PC0);
	static Button secondButton(PC1);
	static Button thirdButton(PC2);
	
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

extern "C" void SysTick_Handler(void)
{
  HAL_IncTick();
}

