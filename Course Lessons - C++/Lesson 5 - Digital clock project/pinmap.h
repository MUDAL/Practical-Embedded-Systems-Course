#ifndef PINMAP_H
#define PINMAP_H

typedef struct
{
	GPIO_TypeDef* port;
	uint16_t selectedPin;
}pinStruct_t;

#endif //PINMAP_H
