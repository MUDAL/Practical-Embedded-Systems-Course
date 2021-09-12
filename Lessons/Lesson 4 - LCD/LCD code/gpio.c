#include "stm32f4xx.h"                  // Device header

enum State
{
	LOW = 0,
	HIGH
};

void GPIO_WritePin(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t state)
{
	switch(state)
	{
		case LOW:
			GPIOx->ODR &= ~pin;
			break;
		case HIGH:
			GPIOx->ODR |= pin;
			break;
	}
}
