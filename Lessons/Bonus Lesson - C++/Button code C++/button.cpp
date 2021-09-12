#include <stdbool.h>
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "button.h"

namespace
{
	GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_BUTTONS];
	GPIO_TypeDef* GPIO_Portx[NUMBER_OF_BUTTONS] = {GPIOC,GPIOC,GPIOC};
	uint16_t GPIO_Pinx[NUMBER_OF_BUTTONS] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_13};
};

bool Button::IsDebounced(void)
{
	if(HAL_GPIO_ReadPin(GPIO_Portx[id],GPIO_Pinx[id]) == GPIO_PIN_RESET)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIO_Portx[id],GPIO_Pinx[id]) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

Button::Button(ButtonID buttonID)
{
	if(buttonID < NUMBER_OF_BUTTONS)
	{
		id = buttonID;
		prevPressed = false;
		GPIO_InitStructArray[id].Pin = GPIO_Pinx[id];
		GPIO_InitStructArray[id].Mode = GPIO_MODE_INPUT;
		GPIO_InitStructArray[id].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIO_Portx[id],&GPIO_InitStructArray[id]);
	}
}

bool Button::Pressed(void)
{
	if(IsDebounced() && !prevPressed)
	{
		prevPressed = true;
		return true;
	}
	else if(!IsDebounced() && prevPressed)
	{
		prevPressed = false;
	}
	return false;
}
