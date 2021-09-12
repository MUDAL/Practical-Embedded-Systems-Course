#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "i2c.h"

//Static functions
static void I2C1_ReadByte(uint8_t slaveAddr,
									       uint8_t regAddr,
									       uint8_t* pData)
{
	volatile uint32_t read_I2C_SR2;
	
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY); //wait for I2C busy bit to be cleared 
	I2C1->CR1 |= I2C_CR1_START; //Generate start condition
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);//wait for start bit to be set
	I2C1->DR = slaveAddr << 1; //slave address
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); //wait for ADDR bit to be set
	read_I2C_SR2 = I2C1->SR2;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); //wait for TXE bit to be set
	I2C1->DR = regAddr;
		
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); 
	I2C1->CR1 |= I2C_CR1_START; 
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C1->DR = slaveAddr << 1 | 1;
	
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); 
	I2C1->CR1 &= ~I2C_CR1_ACK;//Send NACK
	read_I2C_SR2 = I2C1->SR2;
		
	I2C1->CR1 |= I2C_CR1_STOP; //Send STOP
	while((I2C1->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE); //Wait for RXNE bit to be set
	*pData = I2C1->DR;
		
}

static void I2C1_Read2Bytes(uint8_t slaveAddr,
										        uint8_t regAddr,
										        uint8_t* pData)
{
	volatile uint32_t read_I2C_SR2;
	
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY); //wait for I2C busy bit to be cleared 
	I2C1->CR1 |= I2C_CR1_START; //Generate start condition
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);//wait for start bit to be set
			
	I2C1->DR = slaveAddr << 1; //slave address
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); //wait for ADDR bit to be set
	read_I2C_SR2 = I2C1->SR2;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE);//wait for TXE bit to be set
	I2C1->DR = regAddr;
		
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); 
	I2C1->CR1 |= I2C_CR1_START; 
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);
	I2C1->DR = slaveAddr << 1 | 1;
	
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); 
	I2C1->CR1 &= ~I2C_CR1_ACK;//Send NACK
	I2C1->CR1 |= I2C_CR1_POS; 
	read_I2C_SR2 = I2C1->SR2;
		
	while((I2C1->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF);//Wait for BTF bit to be set
	I2C1->CR1 |= I2C_CR1_STOP; //Send STOP
	pData[0] = I2C1->DR;
	pData[1] = I2C1->DR;
}

static void I2C1_Read3BytesMin(uint8_t slaveAddr,
															 uint8_t regAddr,
															 uint8_t* pData,
															 uint32_t length)
{
	if(length < 3)
	{
		//Invalid
		return;
	}
	volatile uint32_t read_I2C_SR2;
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY); //wait for I2C busy bit to be cleared
	I2C1->CR1 |= I2C_CR1_START; //Generate start condition
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB); //wait for start bit to be set
			
	I2C1->DR = slaveAddr << 1; //slave address
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); //wait for ADDR bit to be set
	read_I2C_SR2 = I2C1->SR2;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); //wait for TXE bit to be set
	I2C1->DR = regAddr;
		
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); 
	I2C1->CR1 |= I2C_CR1_START; 
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB); 
	I2C1->DR = slaveAddr << 1 | 1;
	
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR); 
	read_I2C_SR2 = I2C1->SR2;
	I2C1->CR1 |= I2C_CR1_ACK; //Send ACK
	
	//Read incoming data
	for (uint32_t i = 0; i < length - 3; i++)
	{
		while((I2C1->SR1 & I2C_SR1_RXNE) != I2C_SR1_RXNE); //Wait for RXNE bit to be set
		pData[i] = I2C1->DR;
	}
	
	while((I2C1->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF);//Wait for BTF bit to be set
	I2C1->CR1 &= ~I2C_CR1_ACK;//Send NACK	
	pData[length - 3] = I2C1->DR;
		
	while((I2C1->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF);
	I2C1->CR1 |= I2C_CR1_STOP; //Send STOP
	pData[length - 2] = I2C1->DR;
	pData[length - 1] = I2C1->DR;	
}

//External functions
void I2C1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	
	I2C_HandleTypeDef hi2c1;
	hi2c1.Instance = I2C1;
	hi2c1.Init.ClockSpeed = 100000;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
	HAL_I2C_Init(&hi2c1);
}

void I2C1_WriteByte(uint8_t slaveAddr,
									  uint8_t regAddr,
									  uint8_t data)
{
	volatile uint32_t read_I2C_SR2;
	
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY); //wait for I2C busy bit to be cleared	
	I2C1->CR1 |= I2C_CR1_START; //Generate start condition
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);//wait for start bit to be set
			
	I2C1->DR = slaveAddr << 1; //slave address
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR);//wait for ADDR bit to be set
	read_I2C_SR2 = I2C1->SR2;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE);//wait for TXE bit to be set
	I2C1->DR = regAddr;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); 
	I2C1->DR = data;
	while(((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) || 
				 ((I2C1->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF)); 
	I2C1->CR1 |= I2C_CR1_STOP; 	
}

void I2C1_WriteBytes(uint8_t slaveAddr,
										 uint8_t regAddr,
										 uint8_t* pData,
										 uint32_t length)
{
	volatile uint32_t read_I2C_SR2;
	
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY); //wait for I2C busy bit to be cleared	 
	I2C1->CR1 |= I2C_CR1_START; //Generate start condition
	while((I2C1->SR1 & I2C_SR1_SB) != I2C_SR1_SB);//wait for start bit to be set
	I2C1->DR = slaveAddr << 1; //slave address
	while((I2C1->SR1 & I2C_SR1_ADDR) != I2C_SR1_ADDR);//wait for ADDR bit to be set
	read_I2C_SR2 = I2C1->SR2;
	while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE);//wait for TXE bit to be set
	I2C1->DR = regAddr;
	
	for (uint32_t i = 0; i < length; i++)
	{
		while((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE); 
		I2C1->DR = pData[i];
	}
	
	while(((I2C1->SR1 & I2C_SR1_TXE) != I2C_SR1_TXE) || 
				 ((I2C1->SR1 & I2C_SR1_BTF) != I2C_SR1_BTF)); 
	I2C1->CR1 |= I2C_CR1_STOP; 
}

void I2C1_Read(uint8_t slaveAddr,
							 uint8_t regAddr,
							 uint8_t* pData,
							 uint32_t length)
{
	switch(length)
	{
		case 0:
			//Invalid
			return;
		case 1:
			I2C1_ReadByte(slaveAddr,regAddr,pData);
			break;
		case 2:
			I2C1_Read2Bytes(slaveAddr,regAddr,pData);
			break;
		default:
			I2C1_Read3BytesMin(slaveAddr,regAddr,pData,length);
			break;
	}
}
