#ifndef BME280_H
#define BME280_H

#include "pinmap.h"

class BME280
{
	private:
		I2C_HandleTypeDef hi2c;
		uint8_t humidity;
		uint8_t temperature;
		void TakeMeasurements(void);
	
	public:
		BME280(I2C_TypeDef* I2Cx,pinStruct_t& i2cPin1,pinStruct_t& i2cPin2);
		uint8_t GetTemperature(void);
		uint8_t GetHumidity(void);
};

#endif //BME280_H
