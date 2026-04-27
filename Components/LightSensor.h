#ifndef __LIGHT_SENSOR_H__
#define __LIGHT_SENSOR_H__
#include <stdint.h> // ✅ 添加这一行

void LightSensor_Init();
uint8_t LightSensor_Get(void);

#endif // !__LIGHT