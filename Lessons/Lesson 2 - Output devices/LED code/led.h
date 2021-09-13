#ifndef LED_H
#define LED_H

#define NUMBER_OF_LEDS	3

enum LEDPin
{
	LED_PA5 = 0,
	LED_PC5,
	LED_PC6
};

typedef enum 
{
	LED_OFF = 0,
	LED_ON
}LED_State;

extern void LED_Init(uint8_t pinNumber);
extern void LED_Write(uint8_t pinNumber,LED_State LedState);

#endif //LED_H
