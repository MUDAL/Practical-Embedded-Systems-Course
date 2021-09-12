#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "gpio.h"
#include "lcd.h"

#define NUMBER_OF_LCD_PINS	6

//LCD Mode
enum LCDMode
{
	CMD_MODE = 0,
	DATA_MODE
};

//LCD commands
enum LCDCommands
{
	FUNCTION_SET_8BIT	= 0x03,
	FUNCTION_SET_4BIT = 0x02,
	FUNCTION_SET_2LINE_5x8DOT = 0x28,
	CLEAR_DISPLAY = 0x01,
	DISPLAY_ON_CURSOR_ON = 0x0E,
	DISPLAY_ON_CURSOR_OFF = 0x0C,
	ENTRY_MODE_INCREMENT_CURSOR = 0x06
};

//Private globals
/*
The arrays below are mapped to the LCD pins as follows:
index: [0] = RS, [1] = EN, [2] = D4, [3] = D5, [4] = D6, [5] = D7
*/
static GPIO_InitTypeDef GPIO_InitStructArray[NUMBER_OF_LCD_PINS];
static GPIO_TypeDef* GPIO_Portx[NUMBER_OF_LCD_PINS] = 
{
	GPIOC,GPIOC,GPIOC,GPIOC,GPIOC,GPIOC
};
static uint16_t GPIO_Pinx[NUMBER_OF_LCD_PINS] = 
{
	GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3,GPIO_PIN_4,GPIO_PIN_5
};

/*Two-dimensional array to map column and row
combinations to LCD DDRAM addresses. (see HD44780 datasheet)
*/
const uint8_t ddramAddr[4][20] = 
{{0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,0x13},
 {0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x53},
 {0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27},
 {0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67}
};

//Static functions
static void LCD_Write(uint8_t lcdMode,char byte)
{
	uint8_t byteArr[4] = 
	{
		(byte&(1<<4))>>4,
		(byte&(1<<5))>>5,
		(byte&(1<<6))>>6,
		(byte&(1<<7))>>7
	};	
	//Select Instruction register or data register using RS pin
	GPIO_WritePin(GPIO_Portx[0],GPIO_Pinx[0],lcdMode);
	//Send high nibble to D4-D7(clear the pins first)
	for(uint8_t i = 2; i < NUMBER_OF_LCD_PINS; i++)
	{
		HAL_GPIO_WritePin(GPIO_Portx[i],GPIO_Pinx[i],GPIO_PIN_RESET);
	}
	for(uint8_t i = 2; i < NUMBER_OF_LCD_PINS; i++)
	{
		GPIO_WritePin(GPIO_Portx[i],GPIO_Pinx[i],byteArr[i-2]);
	}
	//High to Low pulse on EN pin
	HAL_GPIO_WritePin(GPIO_Portx[1],GPIO_Pinx[1],GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIO_Portx[1],GPIO_Pinx[1],GPIO_PIN_RESET);
	HAL_Delay(1);
	
	uint8_t lowNibbleArr[4] = 
	{
	 (byte&(1<<0))>>0,
	 (byte&(1<<1))>>1,
	 (byte&(1<<2))>>2,
	 (byte&(1<<3))>>3	
	};	
	//Send low nibble to D4-D7 (clear the pins first)
	for(uint8_t i = 2; i < NUMBER_OF_LCD_PINS; i++)
	{
		HAL_GPIO_WritePin(GPIO_Portx[i],GPIO_Pinx[i],GPIO_PIN_RESET);
	}
	for(uint8_t i = 2; i < NUMBER_OF_LCD_PINS; i++)
	{
		GPIO_WritePin(GPIO_Portx[i],GPIO_Pinx[i],lowNibbleArr[i-2]);
	}
	//High to Low pulse on EN pin
	HAL_GPIO_WritePin(GPIO_Portx[1],GPIO_Pinx[1],GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIO_Portx[1],GPIO_Pinx[1],GPIO_PIN_RESET);
	HAL_Delay(1);
}

void LCD_Init(void)
{	
	//Initialize output pins for parallel communication
	for(uint8_t i = 0; i < NUMBER_OF_LCD_PINS; i++)
	{
		GPIO_InitStructArray[i].Pin = GPIO_Pinx[i];
		GPIO_InitStructArray[i].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_Portx[i],&GPIO_InitStructArray[i]);
	}
	//Initialization sequence (according to HD44780 datasheet)
	HAL_Delay(16); //Power-on delay (must be greater than 15ms for 4.5v and 40ms for 2.7v)
	LCD_Write(CMD_MODE,FUNCTION_SET_8BIT);
	HAL_Delay(5); //wait for more than 4.1ms
	LCD_Write(CMD_MODE,FUNCTION_SET_8BIT);
	HAL_Delay(1); //wait for more than 100us
	
	//Select all initialization commands for 4 bit operation
	LCD_Write(CMD_MODE,FUNCTION_SET_4BIT);
	LCD_Write(CMD_MODE,FUNCTION_SET_2LINE_5x8DOT);
	LCD_Write(CMD_MODE,CLEAR_DISPLAY);
	LCD_Write(CMD_MODE,DISPLAY_ON_CURSOR_OFF);
	LCD_Write(CMD_MODE,ENTRY_MODE_INCREMENT_CURSOR);
}

void LCD_WriteChar(char data)
{
	LCD_Write(DATA_MODE,data);
}

void LCD_WriteString(char* pData)
{
	while(*pData != '\0')
	{
		LCD_WriteChar(*pData);
		pData++;
	}
}

void LCD_Clear(void)
{
	LCD_Write(CMD_MODE,CLEAR_DISPLAY);
}

void LCD_SetCursor(uint8_t row,uint8_t column)
{
	if((row > 3)||(column > 19))
	{
		//Out of range
		return;
	}
	/*
	Set DB7 and write address into D4-D7 to set DDRAM address
	*/
	LCD_Write(CMD_MODE,((1<<7) | ddramAddr[row][column])); 
}
