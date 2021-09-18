#ifndef KEYPAD_H
#define KEYPAD_H

#include "pinmap.h"

#define NUMBER_OF_ROWS			4
#define NUMBER_OF_COLUMNS		4

class Keypad
{
	private:
		pinStruct_t* pRow;
		pinStruct_t* pCol;
		void SelectRow(uint8_t pinIndex);
		bool IsDebounced(pinStruct_t* pCol);
	
	public:
		Keypad(pinStruct_t* pRowPins,pinStruct_t* pColumnPins);
		char GetCharShortPress(void);
		char GetCharLongPress(void);
};

#endif //KEYPAD_H
