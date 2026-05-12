#include "MPU6050.h"
#include "MPU6050_Reg.h"
#include "MyI2C.h"
#include "stm32f10x.h"

#define MPU6050_ADDRESS 0xD0 // MPU6050的I2C从机地址 1101 0000              7位110 1000   0x68  

/**
 * @brief  MPU6050写寄存器
 * @param  reg  MPU6050内部的寄存器地址
 * @retval 返回值  返回值说明
 * @note   软模拟I2C
 */

void MPU6050_WriteReg(uint8_t reg, uint8_t data)
{
    MyI2C_Init();
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_RecvAck();
    MyI2C_SendByte(reg);
    MyI2C_RecvAck();
    MyI2C_SendByte(data);
    MyI2C_RecvAck();

    MyI2C_Stop();
}

/**
 * @brief  MPU6050初始化
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   地址   0110 1000   0x68   0xD0
 */
void MPU6050_Init(void)
{

    MyI2C_Init(); // 先初始化底层的I2C

    /*MPU6050寄存器初始化，需要对照MPU6050手册的寄存器描述配置，此处仅配置了部分重要的寄存器*/
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);   // 电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);   // 电源管理寄存器2，保持默认值0，所有轴均不待机
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);   // 采样率分频寄存器，配置采样率
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06);       // 配置寄存器，配置DLPF
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);  // 陀螺仪配置寄存器，选择满量程为±2000°/s
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); // 加速度计配置寄存器，选择满量程为±16g
}

/**
 * @brief  读寄存器
 * @param  reg  MPU6050内部的寄存器地址
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t MPU6050_ReadReg(uint8_t reg)
{

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_RecvAck();
    MyI2C_SendByte(reg);
    MyI2C_RecvAck();

    MyI2C_Start(); // 重新起始
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_RecvAck();
    uint8_t data = MyI2C_RecvByte();
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return data;
}

/**
 * 函    数：MPU6050获取ID号
 * 参    数：无
 * 返 回 值：MPU6050的ID号
 */
uint8_t MPU6050_GetID(void)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I); // 返回WHO_AM_I寄存器的值
}

/**
 * @brief  返回xyz的相关值
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   返回多个参数   1.结构体 2.直接形参是指针传值
 */
void MPU6050_GetData(MPU6050_Angle *angle)
{
    // 高8位   低8位
    angle->ACC_x = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H) << 8 | MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L); // 加速度x轴  |
    angle->ACC_y = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H) << 8 | MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L); // 加速度y轴  - 
    angle->ACC_z = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8 | MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L); // 加速度z轴  .
    angle->GYRO_x = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H) << 8 | MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);  // 陀螺仪x轴
    angle->GYRO_y = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H) << 8 | MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);  // 陀螺仪y轴
    angle->GYRO_z = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H) << 8 | MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);  // 陀螺仪z轴
}