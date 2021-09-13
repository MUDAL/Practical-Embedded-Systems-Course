#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "led.h"

static GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_LEDS];
static GPIO_TypeDef* GPIO_Portx[NUMBER_OF_LEDS] = {GPIOA,GPIOC,GPIOC};
static uint16_t GPIO_Pinx[NUMBER_OF_LEDS] = {GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_6};

void LED_Init(uint8_t pinNumber)
{
	if(pinNumber < NUMBER_OF_LEDS)
	{
		GPIO_InitStructArray[pinNumber].Pin = GPIO_Pinx[pinNumber];
		GPIO_InitStructArray[pinNumber].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_Portx[pinNumber],&GPIO_InitStructArray[pinNumber]);
	}
}

void LED_Write(uint8_t pinNumber,LED_State LedState)
{
	GPIO_PinState pinState;
	switch(LedState)
	{
		case LED_OFF:
			pinState = GPIO_PIN_RESET;
			break;
		case LED_ON:
			pinState = GPIO_PIN_SET;
			break;
	}
	HAL_GPIO_WritePin(GPIO_Portx[pinNumber],GPIO_Pinx[pinNumber],pinState);
}
