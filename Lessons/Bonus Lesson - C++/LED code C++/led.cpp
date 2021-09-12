#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "led.h"

namespace
{
	GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_LEDS];
	GPIO_TypeDef* GPIO_Portx[NUMBER_OF_LEDS] = {GPIOA,GPIOC,GPIOC};
	uint16_t GPIO_Pinx[NUMBER_OF_LEDS] = {GPIO_PIN_5,GPIO_PIN_5,GPIO_PIN_6};	
};

LED::LED(LED_ID ledID)
{
	if(ledID < NUMBER_OF_LEDS)
	{
		id = ledID;
		GPIO_InitStructArray[id].Pin = GPIO_Pinx[id];
		GPIO_InitStructArray[id].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_Portx[id],&GPIO_InitStructArray[id]);
	}
}

void LED::TurnOn(void)
{
	HAL_GPIO_WritePin(GPIO_Portx[id],GPIO_Pinx[id],GPIO_PIN_SET);	
}

void LED::TurnOff(void)
{
	HAL_GPIO_WritePin(GPIO_Portx[id],GPIO_Pinx[id],GPIO_PIN_RESET);	
}

void LED::Toggle(void)
{
	HAL_GPIO_TogglePin(GPIO_Portx[id],GPIO_Pinx[id]);
}
