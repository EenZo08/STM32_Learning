#include "stm32f10x.h"

/**
 * @brief  光敏传感器初始
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   GPIOB PB13引脚
 */
void LightSensor_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  获取光敏传感器的值
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t LightSensor_Get(void)
{

    return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13);
}
