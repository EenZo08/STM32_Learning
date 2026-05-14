#include "MPU6050S.h"
#include "OLED.h"
#include "stm32f10x.h"

uint8_t MPU6050_ID = 0;
// 发文本数据包       硬配I2C
int main(void)
{

    OLED_Init();

    MPU6050S_Init();
    MPU6050_Angle angle;

    while (1)
    {
        MPU6050S_GetData(&angle);
        MPU6050_ID = MPU6050S_GetID();
        OLED_ShowHexNum(1, 1, MPU6050_ID, 2);
        OLED_ShowSignedNum(2, 1, angle.ACC_x, 5);
        OLED_ShowSignedNum(3, 1, angle.ACC_y, 5);
        OLED_ShowSignedNum(4, 1, angle.ACC_z, 5);
        OLED_ShowSignedNum(2, 8, angle.GYRO_x, 5);
        OLED_ShowSignedNum(3, 8, angle.GYRO_y, 5);
        OLED_ShowSignedNum(4, 8, angle.GYRO_z, 5);
    }
}