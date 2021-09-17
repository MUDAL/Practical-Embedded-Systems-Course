#ifndef DS3231_H
#define DS3231_H

#include "pinmap.h"

enum Period
{
	TWELVE_HR_FORMAT_AM = 0,
	TWELVE_HR_FORMAT_PM,
	TWENTY_FOUR_HR_FORMAT_NO_PERIOD
};

typedef struct
{
	uint8_t secs;
	uint8_t mins;
	uint8_t hrs;
	uint8_t period;
}time_t;

class DS3231
{
	private:
		I2C_HandleTypeDef hi2c;
	
	public:
		DS3231(I2C_TypeDef* I2Cx,pinStruct_t& i2cPin1,pinStruct_t& i2cPin2);
		void SetFormat(uint8_t periodOfDay);
		void SetTime(uint8_t hour,uint8_t minute);
		time_t GetTime(void);
};

#endif //DS3231_H
