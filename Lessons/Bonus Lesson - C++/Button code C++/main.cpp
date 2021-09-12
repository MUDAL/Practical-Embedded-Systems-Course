#include "main.h"

static uint8_t i;
static uint8_t j;
static uint8_t k;

int main(void)
{
	//Initializations
	System_Init();
	Button firstButton(BUTTON1);
	Button secondButton(BUTTON2);
	Button thirdButton(BUTTON3);
	
	while(1)
	{
		if(firstButton.Pressed())
		{
			i++;
		}
		if(secondButton.Pressed())
		{
			j++;
		}
		if(thirdButton.Pressed())
		{
			k++;
		}
	}
}	
