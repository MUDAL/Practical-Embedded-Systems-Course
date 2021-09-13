#ifndef BUTTON_H
#define BUTTON_H

#define NUMBER_OF_BUTTONS		3

enum ButtonPin
{
	BUTTON_PC0 = 0,
	BUTTON_PC1,
	BUTTON_PC13
};

extern void Button_Init(uint8_t pinNumber);
extern bool Button_Pressed(uint8_t pinNumber);

#endif //BUTTON_H
