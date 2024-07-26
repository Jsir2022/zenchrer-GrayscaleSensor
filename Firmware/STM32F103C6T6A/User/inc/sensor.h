#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <stdint.h>
#include <stdbool.h>

//传感器总数
#define TOTAL_SENSOR 10
//ADC位数换算得到的值
#define ADC_MAX_NUM 1023
//传感器设定采样频率，最高1000
#define SCAN_FREQ 1000
#define SCAN_TRAS (1000 / SCAN_FREQ)

typedef enum
{
  SENSOR_RUN=0,
  SENSOR_CALIBRATE,
}Sensor_Mode_enum;

typedef struct
{
  uint32_t adcValue[TOTAL_SENSOR];
	uint32_t maxValue[TOTAL_SENSOR];
	uint32_t minValue[TOTAL_SENSOR];
	uint32_t triggerValue[TOTAL_SENSOR];
}Sensor_Data_type;

void Sensor_Init(void);
void Sensor_Process(void);

#endif
