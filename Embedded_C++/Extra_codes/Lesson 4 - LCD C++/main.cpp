#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "lcd.h"

int main(void)
{
	HAL_Init();
	__HAL_RCC_GPIOC_CLK_ENABLE();		
	
	pinStruct_t rs = {GPIOC,GPIO_PIN_0};
	pinStruct_t en = {GPIOC,GPIO_PIN_1};
	pinStruct_t d4 = {GPIOC,GPIO_PIN_2};
	pinStruct_t d5 = {GPIOC,GPIO_PIN_3};
	pinStruct_t d6 = {GPIOC,GPIO_PIN_4};
	pinStruct_t d7 = {GPIOC,GPIO_PIN_5};
		
	static LCD lcd(rs,en,d4,d5,d6,d7);
	
	lcd.Print("I like football");
	HAL_Delay(1000);
	lcd.Clear();
	lcd.Print("Go home!!!!!!");
	HAL_Delay(1000);
	lcd.Clear();
	HAL_Delay(1000);
	uint8_t number = 35;
	lcd.Print(number);
	HAL_Delay(1000);
	uint32_t var = 0;
	
	while(1)
	{
		lcd.SetCursor(0,0);
		lcd.Print(var);
		var++;
		HAL_Delay(300);
	}
}

extern "C" void SysTick_Handler(void)
{
  HAL_IncTick();
}

