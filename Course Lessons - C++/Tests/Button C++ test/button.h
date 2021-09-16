#ifndef BUTTON_H
#define BUTTON_H

class Button
{
	private:
		pinStruct_t pinStruct;
		bool prevPressed;
		bool IsDebounced(void);
	
	public:
		Button(pinStruct_t& gpioPinStruct);
		bool Pressed(void);
};

#endif //BUTTON_H
