#include "main.h"

static uint8_t i;
static uint8_t j;
static uint8_t k;

int main(void)
{
	//Initializations
	System_Init();
	Button firstButton(BUTTON_PC0);
	Button secondButton(BUTTON_PC1);
	Button thirdButton(BUTTON_PC13);
	
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
