#include "stm32f4xx.h"                  // Device header

void GPIO_WritePin(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t state)
{
	switch(state)
	{
		case 0:
			GPIOx->ODR &= ~pin;
			break;
		case 1:
			GPIOx->ODR |= pin;
			break;
	}
}
