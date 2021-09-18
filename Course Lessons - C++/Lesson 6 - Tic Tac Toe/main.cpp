#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "game.h"

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
	
	pinStruct_t rs = {GPIOC,GPIO_PIN_0};
	pinStruct_t en = {GPIOC,GPIO_PIN_1};
	pinStruct_t d4 = {GPIOC,GPIO_PIN_2};
	pinStruct_t d5 = {GPIOC,GPIO_PIN_3};
	pinStruct_t d6 = {GPIOC,GPIO_PIN_4};
	pinStruct_t d7 = {GPIOC,GPIO_PIN_5};
	
	//Initializations
	System_Init();
	static Keypad keypad(rowPins,columnPins);
	static LCD lcd(rs,en,d4,d5,d6,d7);
	
	//Game startup
	Game_DisplayIntro(lcd);
	HAL_Delay(1500);
	Game_DisplayMenu(lcd);
	
	while(1)
	{
		char pressedKey = keypad.GetCharShortPress();
		
		switch(pressedKey)
		{
			case 'A':
				Game_Start(lcd,keypad);
				break;
			case 'B':
				Game_DisplayMenu(lcd);
				break;
			case '#':
				Game_DisplayRules(lcd);
				break;
		}
	}
}	
