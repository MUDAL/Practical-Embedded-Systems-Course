#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "keypad.h"

namespace
{
	char keypadMatrix[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS] =
	{{'1','2','3','A'},
	 {'4','5','6','B'},
	 {'7','8','9','C'},
	 {'*','0','#','D'}};
};

void Keypad::SelectColumn(uint8_t pinIndex)
{
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		if(i == pinIndex)
		{
			HAL_GPIO_WritePin(pCol[i].port,pCol[i].selectedPin,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(pCol[i].port,pCol[i].selectedPin,GPIO_PIN_SET);
		}
	}
}

bool Keypad::IsDebounced(pinStruct_t* pRow)
{
	if(HAL_GPIO_ReadPin(pRow->port,pRow->selectedPin) == GPIO_PIN_RESET)
	{
		HAL_Delay(15); //De-bounce delay
		if(HAL_GPIO_ReadPin(pRow->port,pRow->selectedPin) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

Keypad::Keypad(pinStruct_t* pColumnPins,pinStruct_t* pRowPins)
{
	GPIO_InitTypeDef columnPinInitStruct[NUMBER_OF_COLUMNS];
	GPIO_InitTypeDef rowPinInitStruct[NUMBER_OF_ROWS];	
	pCol = pColumnPins;
	pRow = pRowPins;
	//Initialize columns
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		columnPinInitStruct[i].Pin = pCol[i].selectedPin;
		columnPinInitStruct[i].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(pCol[i].port,&columnPinInitStruct[i]);
	}
	//Initialize rows
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		rowPinInitStruct[i].Pin = pRow[i].selectedPin;
		rowPinInitStruct[i].Mode = GPIO_MODE_INPUT;
		rowPinInitStruct[i].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(pRow[i].port,&rowPinInitStruct[i]);
	}
}

char Keypad::GetCharShortPress(void)
{
	static bool pinPrevPressed[NUMBER_OF_COLUMNS][NUMBER_OF_ROWS];
	
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Keypad::SelectColumn(i);
		for(uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if(Keypad::IsDebounced(&pRow[j]) && !pinPrevPressed[i][j])
			{
				pinPrevPressed[i][j] = true;
				return keypadMatrix[i][j];
			}
			else if(!Keypad::IsDebounced(&pRow[j]) && pinPrevPressed[i][j])
			{
				pinPrevPressed[i][j] = false;
			}
		}
	}
	return '\0'; 
}

char Keypad::GetCharLongPress(void)
{	
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		Keypad::SelectColumn(i);
		for(uint8_t j = 0; j < NUMBER_OF_ROWS; j++)
		{
			if(HAL_GPIO_ReadPin(pRow[j].port,pRow[j].selectedPin) == GPIO_PIN_RESET)
			{
				return keypadMatrix[i][j];
			}
		}
	}
	return '\0'; //If no key is pressed
}
