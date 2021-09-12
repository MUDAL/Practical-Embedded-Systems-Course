#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "bme280.h"

enum RegisterAddresses
{
	BME280_ADDR = 0x76,
	CALIB_00_25_ADDR = 0x88,
	CALIB_26_41_ADDR = 0xE1,
	CTRL_HUM_ADDR = 0xF2,
	CTRL_MEAS_ADDR = 0xF4,
	DATA_REG_ADDR = 0xF7 
};

enum BitFields
{
	CTRL_HUM_OSRS_H_OVR1 = 0x01,
	CTRL_HUM_OSRS_H_OVR2 = 0x02,
	CTRL_HUM_OSRS_H_OVR4 = 0x03,
	CTRL_HUM_OSRS_H_OVR8 = 0x04,
	CTRL_HUM_OSRS_H_OVR16 = 0x05,
	
	CTRL_MEAS_MODE_SLEEP = 0x00,
	CTRL_MEAS_MODE_FORCED1 = 0x01,
	CTRL_MEAS_MODE_FORCED2 = 0x02,
	CTRL_MEAS_MODE_NORMAL = 0x03,
	
	CTRL_MEAS_OSRS_T_OVR1 = 1<<5,
	CTRL_MEAS_OSRS_T_OVR2 = 2<<5,
	CTRL_MEAS_OSRS_T_OVR4 = 3<<5,
	CTRL_MEAS_OSRS_T_OVR8 = 4<<5,
	CTRL_MEAS_OSRS_T_OVR16 = 5<<5
};

typedef struct CompensationParameters
{
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
}bme280_comp_param_t;

#define ADC_REGISTER_SIZE		8
#define CALIB_00_25_SIZE		26
#define CALIB_26_41_SIZE		16

//Private global variables
static bme280_comp_param_t bme280;
static uint8_t rawAdcValue[ADC_REGISTER_SIZE];
static uint8_t bme280Calib00_25[CALIB_00_25_SIZE];
static uint8_t bme280Calib26_41[CALIB_26_41_SIZE]; 
static int32_t t_fine;
static I2C_HandleTypeDef hi2c1;

static void BME280_Store_Compensation_Parameters(uint8_t* calibReg1,
																								 uint8_t* calibReg2,
																								 bme280_comp_param_t* bme)
{
	bme->dig_T1 = (calibReg1[0] | (calibReg1[1] << 8));
	bme->dig_T2 = (calibReg1[2] | (calibReg1[3] << 8));
	bme->dig_T3 = (calibReg1[4] | (calibReg1[5] << 8));
	bme->dig_H1 = calibReg1[25];
	bme->dig_H2 = (calibReg2[0] | (calibReg2[1] << 8));
	bme->dig_H3 = calibReg2[2];
	bme->dig_H4 = ((calibReg2[3] << 4) | (calibReg2[4] & 0x0F));
	bme->dig_H5 = (((calibReg2[4] & ~(0x0F)) >> 4) | (calibReg2[5] << 4));
	bme->dig_H6 = calibReg2[6];
}

//External functions
void BME280_Init(void)
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
	
	HAL_I2C_Mem_Read(&hi2c1,
									 BME280_ADDR<<1,
	                 CALIB_00_25_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 bme280Calib00_25,
	                 CALIB_00_25_SIZE,
									 15);
	//Read the first 7 calibration data of calib26_41 register of bme280
	HAL_I2C_Mem_Read(&hi2c1,
									 BME280_ADDR<<1,
	                 CALIB_26_41_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 bme280Calib26_41,
	                 7,
									 15);	
	BME280_Store_Compensation_Parameters(bme280Calib00_25,bme280Calib26_41,&bme280);
}

void BME280_GetData(bme280_t* pSensorData)
{
	uint8_t data = CTRL_HUM_OSRS_H_OVR16;
	HAL_I2C_Mem_Write(&hi2c1,
									  BME280_ADDR<<1,
	                  CTRL_HUM_ADDR,
	                  I2C_MEMADD_SIZE_8BIT,
	                  &data,
	                  1,
									  15);
	data = CTRL_MEAS_OSRS_T_OVR16|CTRL_MEAS_MODE_FORCED1;
	HAL_I2C_Mem_Write(&hi2c1,
									  BME280_ADDR<<1,
	                  CTRL_MEAS_ADDR,
	                  I2C_MEMADD_SIZE_8BIT,
	                  &data,
	                  1,
									  15);
	
	HAL_I2C_Mem_Read(&hi2c1,
									 BME280_ADDR<<1,
	                 DATA_REG_ADDR,
	                 I2C_MEMADD_SIZE_8BIT,
	                 rawAdcValue,
	                 ADC_REGISTER_SIZE,
									 15);		
	//Temperature calculation
	int32_t adc_T, var1, var2, T;
	adc_T = ((rawAdcValue[3] << 12) | (rawAdcValue[4] << 4) | (rawAdcValue[5] >> 4));
	var1 = ((((adc_T>>3) - ((int32_t)bme280.dig_T1<<1))) * ((int32_t)bme280.dig_T2)) >> 11;
	
	var2 = (((((adc_T>>4) - ((int32_t)bme280.dig_T1)) * 
						((adc_T>>4) - ((int32_t)bme280.dig_T1))) >> 12) * ((int32_t)bme280.dig_T3)) >> 14;

	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	
	pSensorData->temperature = T / 100;
	
	//Humidity calculation
	int32_t adc_H, v_x1_u32r;
	adc_H = ((rawAdcValue[6] << 8) | rawAdcValue[7]);

	v_x1_u32r = (t_fine - ((uint32_t)76800));
	
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)bme280.dig_H4) << 20) -
              (((int32_t)bme280.dig_H5) * v_x1_u32r)) +
              ((int32_t)16384)) >> 15) *
              (((((((v_x1_u32r * ((int32_t)bme280.dig_H6)) >> 10) *
              (((v_x1_u32r * ((int32_t)bme280.dig_H3)) >> 11) +
              ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
              ((int32_t)bme280.dig_H2) + 8192) >> 14));
	
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)bme280.dig_H1)) >> 4));

	//change the ternary operators to if..else statements if you like
  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
	uint32_t rawHumidity = (uint32_t)(v_x1_u32r >> 12);
  
	pSensorData->humidity =  rawHumidity / 1024;	
}
