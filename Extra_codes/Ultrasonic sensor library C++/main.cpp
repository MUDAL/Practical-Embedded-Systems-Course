#include "hcsr04.h"

//Simple application to get distance measurements from...
//3 ultrasonic sensors at the same time.

int main(void)
{
	HAL_Init();
  __HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_TIM1_CLK_ENABLE();
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	//Trigger pin initialization for HCSR04 sensors
	pinStruct_t trigPin = {GPIOA,GPIO_PIN_10};
	HCSR04_TrigPinPWMInit(trigPin,TIM1,GPIO_AF1_TIM1,TIM_CHANNEL_3);
	
	pinStruct_t echoPin1 = {GPIOA,GPIO_PIN_8};
	pinStruct_t echoPin2 = {GPIOA,GPIO_PIN_0};
	pinStruct_t echoPin3 = {GPIOA,GPIO_PIN_6};
	
	static HCSR04 middleSensor(echoPin1,TIM1,GPIO_AF1_TIM1);
	static HCSR04 leftSensor(echoPin2,TIM2,GPIO_AF1_TIM2);
	static HCSR04 rightSensor(echoPin3,TIM3,GPIO_AF2_TIM3);
	
	while(1)
	{
		//get distance measurements here
	}
}

extern "C" void SysTick_Handler(void)
{
	HAL_IncTick();
}

