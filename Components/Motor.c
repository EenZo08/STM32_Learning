#include "PWM.h"
#include "PWM1.h"
#include "stdint.h"
#include "stm32f10x.h"

void Motor1_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 配置电机引脚为推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    PWM_Init();
    PWM_SetPeriod(100 - 1, 36 - 1);
}

void Motor2_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // 配置电机引脚为推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    PWM1_Init();
    // PWM1_SetPeriod(100 - 1, 36 - 1);
}

void Motor1_SetSpeed(int16_t speed)
{
    if (speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare(speed);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        PWM_SetCompare(-speed);
    }
}

void Motor2_SetSpeed(int16_t speed)
{
    if (speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_7);
        GPIO_ResetBits(GPIOA, GPIO_Pin_6);
        PWM1_SetCompare(speed);
    }
    else
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_6);
        GPIO_ResetBits(GPIOA, GPIO_Pin_7);
        PWM1_SetCompare(-speed);
    }
}