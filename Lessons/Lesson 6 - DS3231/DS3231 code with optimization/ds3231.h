#ifndef DS3231_H
#define DS3231_H

enum Period
{
	DS3231_PERIOD_AM = 0,
	DS3231_PERIOD_PM,
	DS3231_NO_PERIOD
};

typedef struct
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hours;
	uint8_t period;
}ds3231_t;

extern void DS3231_Init(void);
extern void DS3231_GetTime(ds3231_t* pTime);
extern void DS3231_SetTime(uint8_t hour,uint8_t minute);
extern void DS3231_Set12HourFormat(uint8_t periodOfDay);
extern void DS3231_Set24HourFormat(void);

#endif //DS3231_H
