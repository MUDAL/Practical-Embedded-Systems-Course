#ifndef BME280_H
#define BME280_H

typedef struct
{
	uint8_t temperature;
	uint8_t humidity;
}bme280_t;

extern void BME280_Init(void);
extern void BME280_GetData(bme280_t* pSensorData);

#endif //BME280_H
