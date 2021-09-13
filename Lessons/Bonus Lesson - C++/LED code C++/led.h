#ifndef LED_H
#define LED_H

#define NUMBER_OF_LEDS	3

enum LEDPin
{
	LED_PA5 = 0,
	LED_PC5,
	LED_PC6
};

class LED
{
	private:
		uint8_t pin;
	
	public:
		LED(uint8_t pinNumber);
		void TurnOn(void);
		void TurnOff(void);
		void Toggle(void);
};

#endif //LED_H
