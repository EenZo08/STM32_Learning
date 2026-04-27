#include "stm32f10x.h"

/**
 * @brief  蜂鸣器启动驱动
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   GPIOB PB12引脚
 */

void Buzzer_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    // GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

/**
 * @brief  蜂鸣器开启
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Buzzer_ON(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief  蜂鸣器关闭
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Buzzer_OFF(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
 * @brief  蜂鸣器状态翻转
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Buzzer_Turn(void)
{

    if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0) // 获取输出寄存器的状态，如果当前引脚输出低电平
    {
        Buzzer_ON();
    }
    else
    {
        Buzzer_OFF();
    }
}