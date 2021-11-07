#include "hcsr04.h"
#include "lcd.h"

int main(void)
{
	HAL_Init();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();
	
	//Sensor pins
	pinStruct_t trigPin = {GPIOA,GPIO_PIN_10};
	pinStruct_t echoPin = {GPIOA,GPIO_PIN_8};
	//LCD pins
	pinStruct_t rs = {GPIOC,GPIO_PIN_0};
	pinStruct_t en = {GPIOC,GPIO_PIN_1};
	pinStruct_t d4 = {GPIOC,GPIO_PIN_2};
	pinStruct_t d5 = {GPIOC,GPIO_PIN_3};
	pinStruct_t d6 = {GPIOC,GPIO_PIN_4};
	pinStruct_t d7 = {GPIOC,GPIO_PIN_5};
	
	HCSR04_TrigPinPWMInit(trigPin,TIM1,GPIO_AF1_TIM1,TIM_CHANNEL_3);
	static HCSR04 hcsr04(echoPin,TIM1,GPIO_AF1_TIM1);
	static LCD lcd(rs,en,d4,d5,d6,d7);
	uint32_t distance = 0;
	
	while(1)
	{
		lcd.SetCursor(0,0);
		lcd.Print("Distance: ");
		distance = hcsr04.GetDistance();
		lcd.Print(distance);
		lcd.Print(" ");
	}
}

extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}

