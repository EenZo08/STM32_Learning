#include "MPU6050S.h"
#include "MPU6050_Reg.h"
#include "stm32f10x.h"

#define MPU6050_ADDRESS 0xD0

// MPU6050配置硬件I2C通信

/**
 * @brief  写
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MPU6050S_WriteReg(uint8_t reg, uint8_t data)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) // ev5事件
        ;
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) // ev6事件
        ;
    I2C_SendData(I2C2, reg);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) // ev8事件
        ;

    // 写单一字节
    I2C_SendData(I2C2, data);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) // ev8_2事件
        ;
    I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
 * @brief  读取MPU6050寄存器
 * @param  reg  寄存器地址
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t MPU6050S_ReadReg(uint8_t reg)
{
    uint8_t data;
    I2C_GenerateSTART(I2C2, ENABLE);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) // ev5事件
        ;
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) // ev6事件
        ;
    I2C_SendData(I2C2, reg);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) // ev8_2事件
        ;

    I2C_GenerateSTART(I2C2, ENABLE);                            // 再次启动
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) // ev5事件
        ;
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) // ev6事件
        ;

    I2C_AcknowledgeConfig(I2C2, DISABLE); // 应答失能
    I2C_GenerateSTOP(I2C2, ENABLE);       // 先提前申请停止条件

    // I2C_ReceiveData(I2C2);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)) // ev7事件
        ;

    data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2, ENABLE); // 应答使能

    return data;
}

/**
 * @brief  MPU6050硬件初始化函数
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MPU6050S_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;          // 复用开漏
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // I2C2引脚     I2C1引脚PB6 PB7
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;                               // 应答信号
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // 应答地址7位
    I2C_InitStruct.I2C_ClockSpeed = 100000;                                // 时钟频率                 0-100kHz占空比默认1：1 不受影响                 100kHz-400kHz   受影响
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;                                // I2C模式
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;                        // I2C占空比
    I2C_InitStruct.I2C_OwnAddress1 = 0x00;                                 // 自己的地址
    // I2C_InitStruct.I2C_OwnAddress2 = 0x00;                                 // 自己的地址
    I2C_Init(I2C2, &I2C_InitStruct);
    I2C_Cmd(I2C2, ENABLE);

    MPU6050S_WriteReg(MPU6050_PWR_MGMT_1, 0x01);   // 电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
    MPU6050S_WriteReg(MPU6050_PWR_MGMT_2, 0x00);   // 电源管理寄存器2，保持默认值0，所有轴均不待机
    MPU6050S_WriteReg(MPU6050_SMPLRT_DIV, 0x09);   // 采样率分频寄存器，配置采样率
    MPU6050S_WriteReg(MPU6050_CONFIG, 0x06);       // 配置寄存器，配置DLPF
    MPU6050S_WriteReg(MPU6050_GYRO_CONFIG, 0x18);  // 陀螺仪配置寄存器，选择满量程为±2000°/s
    MPU6050S_WriteReg(MPU6050_ACCEL_CONFIG, 0x18); // 加速度计配置寄存器，选择满量程为±16g
}

/**
 * @brief  获取xyz值
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MPU6050S_GetData(MPU6050_Angle *angle)
{
    angle->ACC_x = (MPU6050S_ReadReg(MPU6050_ACCEL_XOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_ACCEL_XOUT_L);
    angle->ACC_y = (MPU6050S_ReadReg(MPU6050_ACCEL_YOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_ACCEL_YOUT_L);
    angle->ACC_z = (MPU6050S_ReadReg(MPU6050_ACCEL_ZOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_ACCEL_ZOUT_L);  
    angle->GYRO_x = (MPU6050S_ReadReg(MPU6050_GYRO_XOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_GYRO_XOUT_L);
    angle->GYRO_y = (MPU6050S_ReadReg(MPU6050_GYRO_YOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_GYRO_YOUT_L);   
    angle->GYRO_z = (MPU6050S_ReadReg(MPU6050_GYRO_ZOUT_H) << 8) | MPU6050S_ReadReg(MPU6050_GYRO_ZOUT_L);   
}

/**
 * @brief  获取MPU6050ID
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t MPU6050S_GetID(void)
{
    return MPU6050S_ReadReg(MPU6050_WHO_AM_I);
}