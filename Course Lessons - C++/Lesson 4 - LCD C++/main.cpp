#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "lcd.h"

int main(void)
{
	//Variables
	pinStruct_t rs = {GPIOC,GPIO_PIN_0};
	pinStruct_t en = {GPIOC,GPIO_PIN_1};
	pinStruct_t d4 = {GPIOC,GPIO_PIN_2};
	pinStruct_t d5 = {GPIOC,GPIO_PIN_3};
	pinStruct_t d6 = {GPIOC,GPIO_PIN_4};
	pinStruct_t d7 = {GPIOC,GPIO_PIN_5};
		
	//Initializations
	System_Init();
	LCD lcd(rs,en,d4,d5,d6,d7);
	
	lcd.Print("I love football");
	HAL_Delay(1000);
	lcd.Clear();
	lcd.Print("Go home!!!!!!");
	HAL_Delay(1000);
	lcd.Clear();
	HAL_Delay(1000);
	uint8_t number = 65;
	lcd.Print(number);
	
	while(1)
	{
	}
}
