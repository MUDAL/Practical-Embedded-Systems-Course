#include <stdbool.h>
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "button.h"

static GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_BUTTONS];
static GPIO_TypeDef* GPIO_Portx[NUMBER_OF_BUTTONS] = {GPIOC,GPIOC,GPIOC};
static uint16_t GPIO_Pinx[NUMBER_OF_BUTTONS] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_13};
static bool buttonPrevPressed[NUMBER_OF_BUTTONS];

static bool Button_IsDebounced(ButtonID buttonID)
{
	if(HAL_GPIO_ReadPin(GPIO_Portx[buttonID],GPIO_Pinx[buttonID]) == GPIO_PIN_RESET)
	{
		HAL_Delay(10); 
		if(HAL_GPIO_ReadPin(GPIO_Portx[buttonID],GPIO_Pinx[buttonID]) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

void Button_Init(uint8_t numberOfButtons)
{
	for(uint8_t i = 0; i < numberOfButtons; i++)
	{
		GPIO_InitStructArray[i].Pin = GPIO_Pinx[i];
		GPIO_InitStructArray[i].Mode = GPIO_MODE_INPUT;
		GPIO_InitStructArray[i].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIO_Portx[i],&GPIO_InitStructArray[i]);
	}
}

bool Button_Pressed(ButtonID buttonID)
{
	if(Button_IsDebounced(buttonID) && !buttonPrevPressed[buttonID])
	{
		buttonPrevPressed[buttonID] = true;
		return true;
	}
	else if(!Button_IsDebounced(buttonID) && buttonPrevPressed[buttonID])
	{
		buttonPrevPressed[buttonID] = false;
	}
	return false;
}
