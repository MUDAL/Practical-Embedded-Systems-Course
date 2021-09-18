#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "keypad.h"

char pressedKey = '\0';
char arr[100] = {0};

int main(void)
{
	//Variables
	pinStruct_t rowPins[NUMBER_OF_ROWS] =
	{
		{GPIOC,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7},
		{GPIOB,GPIO_PIN_6}
	};
	pinStruct_t columnPins[NUMBER_OF_COLUMNS] =
	{
		{GPIOA,GPIO_PIN_0},
		{GPIOA,GPIO_PIN_1},
		{GPIOA,GPIO_PIN_4},
		{GPIOB,GPIO_PIN_0}			
	};
	//Initializations
	System_Init();
	Keypad keypad(rowPins,columnPins);
	
	while(1)
	{
		pressedKey = keypad.GetCharShortPress();
		if(pressedKey != '\0')
		{
			static uint8_t i;
			if(i>99)
			{
				i = 0;
			}
			arr[i] = pressedKey;
			i++;
		}
	}
}
