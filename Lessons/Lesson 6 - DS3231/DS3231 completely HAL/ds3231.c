#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "ds3231.h"

enum RegisterAddresses
{
	DS3231_ADDR = 0x68,
	SEC_REG_ADDR = 0x00,
	MIN_REG_ADDR = 0x01,
	HOUR_REG_ADDR = 0x02
};

static I2C_HandleTypeDef hi2c1;

//Static functions
static uint8_t BCD_To_Hex(uint8_t bcd)
{
	uint8_t hex;
	hex = (((bcd & 0xF0)>>4)*10) + (bcd&0x0F);
	return hex;
}

static uint8_t Hex_To_BCD(uint8_t hex)
{
	uint8_t bcd;
	uint8_t multipleOfTen = 0;
	while (hex >= 10)
	{
		hex -= 10;
		multipleOfTen++;
	}
	bcd = ((multipleOfTen<<4) | hex);
	return bcd;
}

//External functions
void DS3231_Init(void)
{
	//GPIO configuration for I2C
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	//I2C configuration
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
	HAL_I2C_Init(&hi2c1);
}

void DS3231_GetTime(ds3231_t* pTime)
{
	uint8_t timeBCD[3]; //sec,min,hour
	uint8_t periodOfDay;
	
	HAL_I2C_Mem_Read(&hi2c1,
									 DS3231_ADDR<<1,
	                 SEC_REG_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 timeBCD,
	                 3,
									 15);	
	if ((timeBCD[2]&(1<<6)) == (1<<6))
	{
		/*
		1.)read AM/PM status of 12 hour clock
		2.)if 12 hour format is the current clock format, 
		read only bits 4-0 of ds3231 hour register*/
		periodOfDay = ((timeBCD[2]&(1<<5)) >> 5);
		timeBCD[2] = (timeBCD[2]&0x1F);
	}
	else
	{
		/*
		1.)no AM/PM status for 24 hour clock
		2.)if 24 hour format is the current clock format, 
		read only bits 5-0 of ds3231 hour register*/
		periodOfDay = DS3231_NO_PERIOD;
		timeBCD[2] = (timeBCD[2]&0x3F);	
	}
	pTime->seconds = BCD_To_Hex(timeBCD[0]);
	pTime->minutes = BCD_To_Hex(timeBCD[1]);
	pTime->hours = BCD_To_Hex(timeBCD[2]);
	pTime->period = periodOfDay;
}

void DS3231_SetTime(uint8_t hour,uint8_t minute)
{
	uint8_t minutesBCD;
	uint8_t prevHoursBCD;
	uint8_t hoursBCD;
	
	minutesBCD = Hex_To_BCD(minute);
	hoursBCD = Hex_To_BCD(hour);
	HAL_I2C_Mem_Read(&hi2c1,
									DS3231_ADDR<<1,
									HOUR_REG_ADDR,
									I2C_MEMADD_SIZE_8BIT,
									&prevHoursBCD,
									1,
									15);
	/* 0xE0 preserves settings of the ds3231 hour register
	so that a write to the register doesn't clear the hour configurations.
	*/
	hoursBCD = (hoursBCD | (prevHoursBCD&0xE0));
	
	uint8_t timeBCDArr[3] = {0,minutesBCD,hoursBCD};
	HAL_I2C_Mem_Write(&hi2c1,
										DS3231_ADDR<<1,
										SEC_REG_ADDR,
										I2C_MEMADD_SIZE_8BIT,
										timeBCDArr,
										3,
										15);
}

void DS3231_Set12HourFormat(uint8_t periodOfDay)
{
	uint8_t hoursBCD;
	
	HAL_I2C_Mem_Read(&hi2c1,
									 DS3231_ADDR<<1,
	                 HOUR_REG_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 &hoursBCD,
	                 1,
									 15);		
	if (periodOfDay == DS3231_PERIOD_PM)
	{
		hoursBCD |= ((1<<6)|(1<<5));
	}
	else
	{
		hoursBCD &= ~(1<<5);
		hoursBCD |= (1<<6);
	}
	HAL_I2C_Mem_Write(&hi2c1,
										DS3231_ADDR<<1,
										HOUR_REG_ADDR,
										I2C_MEMADD_SIZE_8BIT,
										&hoursBCD,
										1,
										15);
}

void DS3231_Set24HourFormat(void)
{
	uint8_t hoursBCD;
	
	HAL_I2C_Mem_Read(&hi2c1,
									 DS3231_ADDR<<1,
	                 HOUR_REG_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 &hoursBCD,
	                 1,
									 15);		
	hoursBCD &= ~((1<<6)|(1<<5));
	HAL_I2C_Mem_Write(&hi2c1,
										DS3231_ADDR<<1,
										HOUR_REG_ADDR,
										I2C_MEMADD_SIZE_8BIT,
										&hoursBCD,
										1,
										15);	
}
