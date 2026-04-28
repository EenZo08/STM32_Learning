#ifndef __COUNTER_SENSOR_H__
#define __COUNTER_SENSOR_H__
#include <stdint.h> // ✅ 添加这一行

void CountSensor_Init(void);
uint16_t CountSensor_Get(void);

#endif // !__COUNTER_SENSOR_H__
