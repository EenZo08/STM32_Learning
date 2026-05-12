#ifndef __MPU6050_H__
#define __MPU6050_H__
#include "stm32f10x.h"

typedef struct
{
    int16_t ACC_x;  // 加速度x轴
    int16_t ACC_y;  // 加速度y轴
    int16_t ACC_z;  // 加速度z轴
    int16_t GYRO_x; // 陀螺仪x轴
    int16_t GYRO_y; // 陀螺仪y轴
    int16_t GYRO_z; // 陀螺仪z轴
} MPU6050_Angle;

void MPU6050_Init(void);
void MPU6050_GetData(MPU6050_Angle *angle);
uint8_t MPU6050_GetID(void);

#endif