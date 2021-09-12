#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "led.h"

static GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_LEDS];
static GPIO_TypeDef* GPIO_Portx[NUMBER_OF_LEDS] = {GPIOA,GPIOC,GPIOC};
static uint16_t GPIO_Pinx[NUMBER_OF_LEDS] = {GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_6};

void LED_Init(uint8_t numberOfLeds)
{
	for(uint8_t i = 0; i < numberOfLeds; i++)
	{
		GPIO_InitStructArray[i].Pin = GPIO_Pinx[i];
		GPIO_InitStructArray[i].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_Portx[i],&GPIO_InitStructArray[i]);
	}
}

void LED_Write(LED_ID LedID,LED_State LedState)
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
	HAL_GPIO_WritePin(GPIO_Portx[LedID],GPIO_Pinx[LedID],pinState);
}
