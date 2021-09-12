#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "keypad.h"

/**
@brief Keypad module
@note Column IDs are values from 0 - NUMBER_OF_COLUMNS
*/

#define NUMBER_OF_COLUMNS		4
#define NUMBER_OF_ROWS			4

//Private globals
static GPIO_InitTypeDef GPIO_ColumnStructArray[NUMBER_OF_COLUMNS];
static GPIO_TypeDef* GPIO_ColumnPort[NUMBER_OF_COLUMNS] = {GPIOC,GPIOC,GPIOC,GPIOC};
static uint16_t GPIO_ColumnPin[NUMBER_OF_COLUMNS] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_2,GPIO_PIN_3};

static GPIO_InitTypeDef GPIO_RowStructArray[NUMBER_OF_ROWS];
static GPIO_TypeDef* GPIO_RowPort[NUMBER_OF_ROWS] = {GPIOC,GPIOC,GPIOC,GPIOC};
static uint16_t GPIO_RowPin[NUMBER_OF_ROWS] = {GPIO_PIN_4,GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7};

static char keypadChar[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS] = 
																								{{'1','2','3','A'},
																								 {'4','5','6','B'},
																								 {'7','8','9','C'},
																								 {'*','0','#','D'}};

//Static functions
static void Keypad_ClearOneColumn_SetTheRest(uint8_t id)
{
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		if(i == id)
		{
			HAL_GPIO_WritePin(GPIO_ColumnPort[i],GPIO_ColumnPin[i],GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIO_ColumnPort[i],GPIO_ColumnPin[i],GPIO_PIN_SET);
		}
	}
}
																								 
static void Keypad_SelectColumn(uint8_t id)
{
	Keypad_ClearOneColumn_SetTheRest(id);
}

//External functions
void Keypad_Init(void)
{
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		GPIO_ColumnStructArray[i].Pin = GPIO_ColumnPin[i];
		GPIO_ColumnStructArray[i].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIO_ColumnPort[i],&GPIO_ColumnStructArray[i]);
	}
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		GPIO_RowStructArray[i].Pin = GPIO_RowPin[i];
		GPIO_RowStructArray[i].Mode = GPIO_MODE_INPUT;
		GPIO_RowStructArray[i].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(GPIO_RowPort[i],&GPIO_RowStructArray[i]);
	}
}

char Keypad_GetChar(void)
{
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Keypad_SelectColumn(i);
		for(uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if(HAL_GPIO_ReadPin(GPIO_RowPort[j],GPIO_RowPin[j]) == GPIO_PIN_RESET)
			{
				HAL_Delay(10);
				return keypadChar[i][j];
			}
		}
	}
	return '\0'; //If no key is pressed
}
