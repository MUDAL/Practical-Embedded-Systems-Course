#include "button.h"

bool Button::IsDebounced(void)
{
	if(HAL_GPIO_ReadPin(pinStruct.port,pinStruct.selectedPin) == GPIO_PIN_RESET)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(pinStruct.port,pinStruct.selectedPin) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

Button::Button(pinStruct_t& gpioPinStruct)
{
	GPIO_InitTypeDef gpioInitStruct = {0};
	pinStruct = gpioPinStruct;
	prevPressed = false;
	gpioInitStruct.Pin = pinStruct.selectedPin;
	gpioInitStruct.Mode = GPIO_MODE_INPUT;
	gpioInitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(pinStruct.port,&gpioInitStruct);
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
