#include "main.h"

static uint8_t i;
static uint8_t j;
static uint8_t k;

int main(void)
{																				
	//Initializations
	System_Init();
	Button_Init(BUTTON_PC0);
	Button_Init(BUTTON_PC1);
	Button_Init(BUTTON_PC13);
																							 
	while(1)
	{
		if(Button_Pressed(BUTTON_PC0))
		{
			i++;
		}
		if(Button_Pressed(BUTTON_PC1))
		{
			j++;
		}
		if(Button_Pressed(BUTTON_PC13))
		{
			k++;
		}
	}
}
