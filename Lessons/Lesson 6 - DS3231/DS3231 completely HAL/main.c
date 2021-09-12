#include "main.h"

ds3231_t time;

int main(void)
{
	//Initializations
	System_Init();
	DS3231_Init();
	
	//Set the time
	DS3231_Set24HourFormat();
	DS3231_SetTime(13,0);
	
	while(1)
	{
		DS3231_GetTime(&time);
	}
}
