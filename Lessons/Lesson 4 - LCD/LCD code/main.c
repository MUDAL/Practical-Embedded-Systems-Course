#include "main.h"

int main(void)
{
	//Initializations
	System_Init();
	LCD_Init();
	
	while(1)
	{
		LCD_WriteString("Good day everyone");
		LCD_SetCursor(1,0);
		LCD_WriteString("Embedded systems is");
		LCD_SetCursor(2,0);
		LCD_WriteString("interesting,");
		LCD_SetCursor(3,0);
		LCD_WriteString("So stay tuned.");
		System_DelayMs(2000);
		LCD_Clear();
	}
}
