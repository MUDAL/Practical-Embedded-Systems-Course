#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "led.h"

namespace
{
	GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_LEDS];
	GPIO_TypeDef* GPIO_Portx[NUMBER_OF_LEDS] = {GPIOA,GPIOC,GPIOC};
	uint16_t GPIO_Pinx[NUMBER_OF_LEDS] = {GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_6};	
};

LED::LED(uint8_t pinNumber)
{
	if(pinNumber < NUMBER_OF_LEDS)
	{
		pin = pinNumber;
		GPIO_InitStructArray[pinNumber].Pin = GPIO_Pinx[pinNumber];
		GPIO_InitStructArray[pinNumber].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_Portx[pinNumber],&GPIO_InitStructArray[pinNumber]);
	}
}

void LED::TurnOn(void)
{
	HAL_GPIO_WritePin(GPIO_Portx[pin],GPIO_Pinx[pin],GPIO_PIN_SET);	
}

void LED::TurnOff(void)
{
	HAL_GPIO_WritePin(GPIO_Portx[pin],GPIO_Pinx[pin],GPIO_PIN_RESET);	
}

void LED::Toggle(void)
{
	HAL_GPIO_TogglePin(GPIO_Portx[pin],GPIO_Pinx[pin]);
}
