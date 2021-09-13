#include <stdbool.h>
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "button.h"

static GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_BUTTONS];
static GPIO_TypeDef* GPIO_Portx[NUMBER_OF_BUTTONS] = {GPIOC,GPIOC,GPIOC};
static uint16_t GPIO_Pinx[NUMBER_OF_BUTTONS] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_13};
static bool buttonPrevPressed[NUMBER_OF_BUTTONS];

static bool Button_IsDebounced(uint8_t pinNumber)
{
	if(HAL_GPIO_ReadPin(GPIO_Portx[pinNumber],GPIO_Pinx[pinNumber]) == GPIO_PIN_RESET)
	{
		HAL_Delay(10); 
		if(HAL_GPIO_ReadPin(GPIO_Portx[pinNumber],GPIO_Pinx[pinNumber]) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

void Button_Init(uint8_t pinNumber)
{
	if(pinNumber < NUMBER_OF_BUTTONS)
	{
		GPIO_InitStructArray[pinNumber].Pin = GPIO_Pinx[pinNumber];
		GPIO_InitStructArray[pinNumber].Mode = GPIO_MODE_INPUT;
		GPIO_InitStructArray[pinNumber].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIO_Portx[pinNumber],&GPIO_InitStructArray[pinNumber]);
	}
}

bool Button_Pressed(uint8_t pinNumber)
{
	if(Button_IsDebounced(pinNumber) && !buttonPrevPressed[pinNumber])
	{
		buttonPrevPressed[pinNumber] = true;
		return true;
	}
	else if(!Button_IsDebounced(pinNumber) && buttonPrevPressed[pinNumber])
	{
		buttonPrevPressed[pinNumber] = false;
	}
	return false;
}
