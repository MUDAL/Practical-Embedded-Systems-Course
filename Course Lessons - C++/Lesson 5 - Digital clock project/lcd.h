#ifndef LCD_H
#define LCD_H

#include "pinmap.h"

class LCD
{
	private:
		pinStruct_t rs;
		pinStruct_t en; 
		pinStruct_t dataPins[4];
		void Write(GPIO_PinState lcdMode,char byte);
	
	public:
		LCD(pinStruct_t& RS,
				pinStruct_t& EN, 
				pinStruct_t& D4,
				pinStruct_t& D5,
				pinStruct_t& D6,
				pinStruct_t& D7);
		
		void SetCursor(uint8_t row,uint8_t column);
		void Print(char data);
		void Print(const char* pData);
		void Print(uint8_t& data);
		void Clear(void);
};

#endif //LCD_H
