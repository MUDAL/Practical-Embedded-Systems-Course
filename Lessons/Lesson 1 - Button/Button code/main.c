#include "main.h"

static uint8_t i;
static uint8_t j;
static uint8_t k;

int main(void)
{																				
	//Initializations
	System_Init();
	Button_Init(NUMBER_OF_BUTTONS);
																							 
	while(1)
	{
		if(Button_Pressed(BUTTON1))
		{
			i++;
		}
		if(Button_Pressed(BUTTON2))
		{
			j++;
		}
		if(Button_Pressed(BUTTON3))
		{
			k++;
		}
	}
}
