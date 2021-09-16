#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "keypad.h"

char pressedKey = '\0';

int main(void)
{
	//Variables
	pinStruct_t columnPins[NUMBER_OF_COLUMNS] =
	{
		{GPIOC,GPIO_PIN_0},
		{GPIOC,GPIO_PIN_1},
		{GPIOC,GPIO_PIN_2},
		{GPIOC,GPIO_PIN_3}
	};
	pinStruct_t rowPins[NUMBER_OF_ROWS] =
	{
		{GPIOC,GPIO_PIN_4},
		{GPIOC,GPIO_PIN_5},
		{GPIOC,GPIO_PIN_6},
		{GPIOC,GPIO_PIN_7}	
	};
	//Initializations
	System_Init();
	Keypad keypad(columnPins,rowPins);
	
	while(1)
	{
		pressedKey = keypad.GetChar();
	}
}
