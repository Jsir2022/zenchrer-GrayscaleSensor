#ifndef __SENSOR_H__
#define __SENSOR_H__

#include <stdint.h>
#include <stdbool.h>

//传感器总数
#define TOTAL_SENSOR 10

typedef enum
{
    SENSOR_RUN=0,
    SENSOR_CALIBRATE,
}Sensor_Mode_enum;

void Sensor_clear_calibration(void);

#endif
