#ifndef KEYPAD_H
#define KEYPAD_H

#include "pinmap.h"

#define NUMBER_OF_COLUMNS		4
#define NUMBER_OF_ROWS			4

class Keypad
{
	private:
		pinStruct_t* pCol;
		pinStruct_t* pRow;
		void SelectColumn(uint8_t pinIndex);
		bool IsDebounced(pinStruct_t* pRow);
	
	public:
		Keypad(pinStruct_t* pColumnPins,pinStruct_t* pRowPins);
		char GetCharShortPress(void);
		char GetCharLongPress(void);
};

#endif //KEYPAD_H
