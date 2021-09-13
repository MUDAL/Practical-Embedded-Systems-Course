#ifndef BUTTON_H
#define BUTTON_H

#define NUMBER_OF_BUTTONS		3

enum ButtonPin
{
	BUTTON_PC0 = 0,
	BUTTON_PC1,
	BUTTON_PC13
};

class Button
{
	private:
		uint8_t pin;
		bool prevPressed;
		bool IsDebounced(void);
	
	public:
		Button(uint8_t pinNumber);
		bool Pressed(void);
};

#endif //BUTTON_H
