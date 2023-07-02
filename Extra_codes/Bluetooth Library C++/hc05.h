#ifndef HC05_H
#define HC05_H

#include "pinmap.h"

class HC05
{
	private:
		UART_HandleTypeDef huart;
	public:
		HC05(pinStruct_t& uartPin,
				 USART_TypeDef* USARTx,
				 uint32_t baudRate,
				 uint32_t gpioAFSelUSARTx,
				 uint32_t mode);
		char GetChar(void);
};

#endif //HC05_H
