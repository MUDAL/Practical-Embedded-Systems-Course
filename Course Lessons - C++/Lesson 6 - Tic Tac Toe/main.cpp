#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "keypad.h"
#include "lcd.h"

namespace
{
	void DisplayIntro(LCD& lcd)
	{
		lcd.Clear();
		lcd.SetCursor(0,1);
		lcd.Print("|   WELCOME      |");
		lcd.SetCursor(1,1);
		lcd.Print("|   TO THE       |");
		lcd.SetCursor(2,1);
		lcd.Print("|   TIC TAC TOE  |");
		lcd.SetCursor(3,1);
		lcd.Print("|   TOURNAMENT   |");
		HAL_Delay(1500);		
	}
	
	void DisplayRules(LCD& lcd)
	{
		lcd.Clear();
		lcd.SetCursor(0,4);
		lcd.Print("Rule");
		lcd.SetCursor(1,0);
		lcd.Print("Press the numbers");
		lcd.SetCursor(2,0);
		lcd.Print("to place X or O to");
		lcd.SetCursor(3,0);
		lcd.Print("the game board");
		HAL_Delay(1500);
		lcd.Clear();
		lcd.SetCursor(0,4);
		lcd.Print("Game Menu");
		lcd.SetCursor(1,0);
		lcd.Print("1|2|3   A:Start");
		lcd.SetCursor(2,0);
		lcd.Print("4|5|6   #:Rules");
		lcd.SetCursor(3,0);
		lcd.Print("7|8|9");	
	}
};

int main(void)
{
	//Variables
	pinStruct_t columnPins[NUMBER_OF_COLUMNS] =
	{
		{GPIOC,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_6},
		{GPIOA,GPIO_PIN_7},
		{GPIOB,GPIO_PIN_6}
	};
	pinStruct_t rowPins[NUMBER_OF_ROWS] =
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
	
	char pressedKey = '\0';
	
	//Initializations
	System_Init();
	Keypad keypad(columnPins,rowPins);
	LCD lcd(rs,en,d4,d5,d6,d7);
	
	//Game intro and rules
	DisplayIntro(lcd);
	DisplayRules(lcd);
	
	while(1)
	{
		pressedKey = keypad.GetCharShortPress();
		if(pressedKey != '\0')
		{
			switch(pressedKey)
			{
				case '#':
					DisplayRules(lcd);
					break;
			}
		}
	}
}	
