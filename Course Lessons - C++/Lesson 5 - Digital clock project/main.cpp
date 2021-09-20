#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "system.h"
#include "ds3231.h"
#include "bme280.h"
#include "lcd.h"

int main(void)
{
	//Variables
	static pinStruct_t scl = {GPIOB,GPIO_PIN_8};
	static pinStruct_t sda = {GPIOB,GPIO_PIN_9};
	static pinStruct_t rs = {GPIOC,GPIO_PIN_0};
	static pinStruct_t en = {GPIOC,GPIO_PIN_1};
	static pinStruct_t d4 = {GPIOC,GPIO_PIN_2};
	static pinStruct_t d5 = {GPIOC,GPIO_PIN_3};
	static pinStruct_t d6 = {GPIOC,GPIO_PIN_4};
	static pinStruct_t d7 = {GPIOC,GPIO_PIN_5};
	
	static time_t time;
	static bme280Data_t bme280Data;
	
	//Initializations
	System_Init();
	static DS3231 ds3231(I2C1,scl,sda);
	static BME280 bme280(I2C1,scl,sda);
	static LCD lcd(rs,en,d4,d5,d6,d7);
	
	ds3231.SetFormat(TWELVE_HR_FORMAT_PM);
	ds3231.SetTime(9,59);
	
	lcd.Print("Time: ");
	lcd.SetCursor(1,0);
	lcd.Print("Temperature:   C");
	lcd.SetCursor(2,0);
	lcd.Print("Humidity:   %");
	
	while(1)
	{
		time = ds3231.GetTime();
		lcd.SetCursor(0,6);
		lcd.Print(time.hrs);
		lcd.Print(':');
		lcd.Print(time.mins);
		lcd.Print(':');
		lcd.Print(time.secs);
		lcd.Print(' ');
		switch(time.period)
		{
			case TWELVE_HR_FORMAT_AM:
				lcd.Print("AM");
				break;
			case TWELVE_HR_FORMAT_PM:
				lcd.Print("PM");
				break;
			case TWENTY_FOUR_HR_FORMAT_NO_PERIOD:
				break;
		}		
		
		bme280Data = bme280.GetData();
		lcd.SetCursor(1,13);
		lcd.Print(bme280Data.temperature);
		lcd.SetCursor(2,10);
		lcd.Print(bme280Data.humidity);
	}
}
