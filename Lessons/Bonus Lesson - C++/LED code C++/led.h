#ifndef LED_H
#define LED_H

#define NUMBER_OF_LEDS	3

typedef enum
{
	LED1 = 0,
	LED2,
	LED3
}LED_ID;

class LED
{
	private:
		LED_ID id;
	
	public:
		LED(LED_ID ledID);
		void TurnOn(void);
		void TurnOff(void);
		void Toggle(void);
};

#endif //LED_H
