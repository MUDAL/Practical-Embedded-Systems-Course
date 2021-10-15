#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "keypad.h"

const char keypadMatrix[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] =
{{'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}};

void Keypad::SelectRow(uint8_t pinIndex)
{
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		if(i == pinIndex)
		{
			HAL_GPIO_WritePin(pRow[i].port,pRow[i].selectedPin,GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(pRow[i].port,pRow[i].selectedPin,GPIO_PIN_SET);
		}
	}
}

bool Keypad::IsDebounced(pinStruct_t* pColumn)
{
	if(HAL_GPIO_ReadPin(pColumn->port,pColumn->selectedPin) == GPIO_PIN_RESET)
	{
		HAL_Delay(15); //De-bounce delay
		if(HAL_GPIO_ReadPin(pColumn->port,pColumn->selectedPin) == GPIO_PIN_RESET)
		{
			return true;
		}
	}
	return false;
}

Keypad::Keypad(pinStruct_t* pRowPins,pinStruct_t* pColumnPins)
{
	GPIO_InitTypeDef rowPinInitStruct[NUMBER_OF_ROWS];	
	GPIO_InitTypeDef columnPinInitStruct[NUMBER_OF_COLUMNS];
	pRow = pRowPins;
	pCol = pColumnPins;
	//Initialize rows
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		rowPinInitStruct[i].Pin = pRow[i].selectedPin;
		rowPinInitStruct[i].Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(pRow[i].port,&rowPinInitStruct[i]);
	}
	//Initialize columns
	for(uint8_t i = 0; i < NUMBER_OF_COLUMNS; i++)
	{
		columnPinInitStruct[i].Pin = pCol[i].selectedPin;
		columnPinInitStruct[i].Mode = GPIO_MODE_INPUT;
		columnPinInitStruct[i].Pull = GPIO_PULLUP;
		HAL_GPIO_Init(pCol[i].port,&columnPinInitStruct[i]);
	}
}

char Keypad::GetCharShortPress(void)
{
	static bool pinPrevPressed[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS];
	
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		Keypad::SelectRow(i);
		for(uint8_t j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			if(Keypad::IsDebounced(&pCol[j]) && !pinPrevPressed[i][j])
			{
				pinPrevPressed[i][j] = true;
				return keypadMatrix[i][j];
			}
			else if(!Keypad::IsDebounced(&pCol[j]) && pinPrevPressed[i][j])
			{
				pinPrevPressed[i][j] = false;
			}
		}
	}
	return '\0'; 
}

char Keypad::GetCharLongPress(void)
{	
	for(uint8_t i = 0; i < NUMBER_OF_ROWS; i++)
	{
		Keypad::SelectRow(i);
		for(uint8_t j = 0; j < NUMBER_OF_COLUMNS; j++)
		{
			if(HAL_GPIO_ReadPin(pCol[j].port,pCol[j].selectedPin) == GPIO_PIN_RESET)
			{
				return keypadMatrix[i][j];
			}
		}
	}
	return '\0'; //If no key is pressed
}
