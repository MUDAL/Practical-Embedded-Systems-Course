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
	
	public:
		Keypad(pinStruct_t* pColumnPins,pinStruct_t* pRowPins);
		char GetChar(void);
};

#endif //KEYPAD_H
