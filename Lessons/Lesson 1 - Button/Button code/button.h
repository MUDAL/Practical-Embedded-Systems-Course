#ifndef BUTTON_H
#define BUTTON_H

#define NUMBER_OF_BUTTONS		3

typedef enum
{
	BUTTON1 = 0,
	BUTTON2,
	BUTTON3
}ButtonID;

extern void Button_Init(uint8_t numberOfButtons);
extern bool Button_Pressed(ButtonID buttonID);

#endif //BUTTON_H
