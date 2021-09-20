#ifndef LCD_H
#define LCD_H

#include "pinmap.h"

#define INT_TO_STR_BUFFER_LEN	2

class LCD
{
	private:
		pinStruct_t rs;
		pinStruct_t en; 
		pinStruct_t dataPins[4];
		void Write(GPIO_PinState lcdMode,char byte);
		void PrintInteger(uint32_t data);
	
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
		void Print(uint16_t& data);
		void Print(uint32_t& data);
		void Clear(void);
};

#endif //LCD_H
