#ifndef BME280_H
#define BME280_H

#include "pinmap.h"

typedef struct
{
	uint8_t temperature;
	uint8_t humidity;
}bme280Data_t;

class BME280
{
	private:
		I2C_HandleTypeDef hi2c;
	
	public:
		BME280(I2C_TypeDef* I2Cx,pinStruct_t& i2cPin1,pinStruct_t& i2cPin2);
		bme280Data_t GetData(void);
};

#endif //BME280_H
