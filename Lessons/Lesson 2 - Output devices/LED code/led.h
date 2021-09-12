#ifndef LED_H
#define LED_H

#define NUMBER_OF_LEDS	3

typedef enum
{
	LED1 = 0,
	LED2,
	LED3
}LED_ID;

typedef enum
{
	LED_OFF = 0,
	LED_ON
}LED_State;

extern void LED_Init(uint8_t numberOfLeds);
extern void LED_Write(LED_ID LedID,LED_State LedState);

#endif //LED_H
