#include "main.h"

char pressedKey;

int main(void)
{
	//Initializations
	System_Init();
	Keypad_Init();
	
	while(1)
	{
		pressedKey = Keypad_GetChar();
	}
}
