#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "ds3231.h"

namespace
{
	enum RegisterAddresses
	{
		DS3231_ADDR = 0x68,
		SEC_REG_ADDR = 0x00,
		MIN_REG_ADDR = 0x01,
		HOUR_REG_ADDR = 0x02
	};
	
	const uint8_t I2C_HAL_TIMEOUT = 2;
	
	uint8_t BCD_To_Hex(uint8_t bcd)
	{
		uint8_t hex;
		hex = (((bcd & 0xF0)>>4)*10) + (bcd&0x0F);
		return hex;
	}
	
	uint8_t Hex_To_BCD(uint8_t hex)
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
};

DS3231::DS3231(I2C_TypeDef* I2Cx,pinStruct_t& i2cPin1,pinStruct_t& i2cPin2)
{
	GPIO_InitTypeDef i2cGPIO1InitStruct = {0};
	GPIO_InitTypeDef i2cGPIO2InitStruct = {0};
	//GPIO configuration (SDA and SCL in any order)
	i2cGPIO1InitStruct.Pin = i2cPin1.selectedPin;
	i2cGPIO1InitStruct.Mode = GPIO_MODE_AF_OD;
	i2cGPIO1InitStruct.Pull = GPIO_PULLUP;
	i2cGPIO1InitStruct.Alternate = 0x04;
	HAL_GPIO_Init(i2cPin1.port,&i2cGPIO1InitStruct);
	
	i2cGPIO2InitStruct.Pin = i2cPin2.selectedPin;
	i2cGPIO2InitStruct.Mode = GPIO_MODE_AF_OD;
	i2cGPIO2InitStruct.Pull = GPIO_PULLUP;
	i2cGPIO2InitStruct.Alternate = 0x04;
	HAL_GPIO_Init(i2cPin2.port,&i2cGPIO2InitStruct);
	
	//I2C configuration
	hi2c.Instance = I2Cx;
	hi2c.Init.ClockSpeed = 100000;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_I2C_Init(&hi2c);	
}

void DS3231::SetFormat(uint8_t periodOfDay)
{
	uint8_t hoursBCD;
	
	HAL_I2C_Mem_Read(&hi2c,
									 DS3231_ADDR<<1,
									 HOUR_REG_ADDR,
									 I2C_MEMADD_SIZE_8BIT,
									 &hoursBCD,
									 1,
									 I2C_HAL_TIMEOUT);
	switch(periodOfDay)
	{
		case TWELVE_HR_FORMAT_AM:
			hoursBCD &= ~(1<<5);
			hoursBCD |= (1<<6);
			break;
		case TWELVE_HR_FORMAT_PM:
			hoursBCD |= ((1<<6)|(1<<5));
			break;
		case TWENTY_FOUR_HR_FORMAT_NO_PERIOD:
			hoursBCD &= ~((1<<6)|(1<<5));
			break;
	}
	HAL_I2C_Mem_Write(&hi2c,
										DS3231_ADDR<<1,
										HOUR_REG_ADDR,
										I2C_MEMADD_SIZE_8BIT,
										&hoursBCD,
										1,
										I2C_HAL_TIMEOUT);		
}

void DS3231::SetTime(uint8_t hour,uint8_t minute)
{
	uint8_t minutesBCD;
	uint8_t prevHoursBCD;
	uint8_t hoursBCD;
	
	minutesBCD = Hex_To_BCD(minute);
	hoursBCD = Hex_To_BCD(hour);
	HAL_I2C_Mem_Read(&hi2c,
									 DS3231_ADDR<<1,
									 HOUR_REG_ADDR,
									 I2C_MEMADD_SIZE_8BIT,
									 &prevHoursBCD,
									 1,
									 I2C_HAL_TIMEOUT);
	/* 0xE0 preserves settings of the ds3231 hour register
	so that a write to the register doesn't clear the hour configurations.
	*/
	hoursBCD = (hoursBCD | (prevHoursBCD&0xE0));
	
	uint8_t timeBCDArr[3] = {0,minutesBCD,hoursBCD};
	HAL_I2C_Mem_Write(&hi2c,
										DS3231_ADDR<<1,
										SEC_REG_ADDR,
										I2C_MEMADD_SIZE_8BIT,
										timeBCDArr,
										3,
										I2C_HAL_TIMEOUT);
}
	
time_t DS3231::GetTime(void)
{
	uint8_t timeBCD[3]; //seconds,minutes,hours
	uint8_t periodOfDay;
	
	HAL_I2C_Mem_Read(&hi2c,
									 DS3231_ADDR<<1,
									 SEC_REG_ADDR,
									 I2C_MEMADD_SIZE_8BIT,
									 timeBCD,
									 3,
									 I2C_HAL_TIMEOUT);
	if((timeBCD[2]&(1<<6)) == (1<<6))
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
		periodOfDay = TWENTY_FOUR_HR_FORMAT_NO_PERIOD;
		timeBCD[2] = (timeBCD[2]&0x3F);
	}
	
	time_t time;
	time.secs = BCD_To_Hex(timeBCD[0]);
	time.mins = BCD_To_Hex(timeBCD[1]);
	time.hrs = BCD_To_Hex(timeBCD[2]);
	time.period = periodOfDay;

	return time;
}
