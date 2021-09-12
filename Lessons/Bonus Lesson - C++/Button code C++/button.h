#ifndef BUTTON_H
#define BUTTON_H

#define NUMBER_OF_BUTTONS		3

typedef enum
{
	BUTTON1 = 0,
	BUTTON2,
	BUTTON3
}ButtonID;

class Button
{
	private:
		ButtonID id;
		bool prevPressed;
		bool IsDebounced(void);
	
	public:
		Button(ButtonID buttonID);
		bool Pressed(void);
};

#endif //BUTTON_H
