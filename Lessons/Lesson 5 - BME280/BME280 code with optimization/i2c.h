#ifndef I2C_H
#define I2C_H

extern void I2C1_Init(void);
extern void I2C1_WriteByte(uint8_t slaveAddr,
													 uint8_t regAddr,
													 uint8_t data);
extern void I2C1_WriteBytes(uint8_t slaveAddr,
											      uint8_t regAddr,
											      uint8_t* pData,
											      uint32_t length);
extern void I2C1_Read(uint8_t slaveAddr,
										  uint8_t regAddr,
										  uint8_t* pData,
										  uint32_t length);

#endif //I2C_H
