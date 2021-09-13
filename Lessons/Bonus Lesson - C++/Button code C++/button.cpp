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
	if(HAL_GPIO_ReadPin(GPIO_Portx[pin],GPIO_Pinx[pin]) == GPIO_PIN_RESET)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIO_Portx[pin],GPIO_Pinx[pin]) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

Button::Button(uint8_t pinNumber)
{
	if(pinNumber < NUMBER_OF_BUTTONS)
	{
		pin = pinNumber;
		prevPressed = false;
		GPIO_InitStructArray[pinNumber].Pin = GPIO_Pinx[pinNumber];
		GPIO_InitStructArray[pinNumber].Mode = GPIO_MODE_INPUT;
		GPIO_InitStructArray[pinNumber].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIO_Portx[pinNumber],&GPIO_InitStructArray[pinNumber]);
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
