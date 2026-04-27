#include "delay.h"
#include "stm32f10x.h"
// #include "Key.h"

// 以gpiob     PB0 ~ PB15引脚   输入模式    默认上拉输入

// 引脚查找表   PA0-P15的16个引脚PA0-P15的16个引脚  enum
const uint16_t KEY_Pins[] = {
    GPIO_Pin_0,  // 索引 0 → Pin0
    GPIO_Pin_1,  // 索引 1 → Pin1
    GPIO_Pin_2,  // 索引 2 → Pin2
    GPIO_Pin_3,  // 索引 3 → Pin2
    GPIO_Pin_4,  // 索引 4 → Pin2
    GPIO_Pin_5,  // 索引 5 → Pin2
    GPIO_Pin_6,  // 索引 6 → Pin2
    GPIO_Pin_7,  // 索引 7 → Pin2
    GPIO_Pin_8,  // 索引 8 → Pin2
    GPIO_Pin_9,  // 索引 9 → Pin2
    GPIO_Pin_10, // 索引 10 → Pin2
    GPIO_Pin_11, // 索引 11 → Pin2
    GPIO_Pin_12, // 索引 12 → Pin
    GPIO_Pin_13, // 索引 13 → Pin13
    GPIO_Pin_14, // 索引 14 → Pin14
    GPIO_Pin_15, // 索引 15 → Pin15
};

void Key_Init()
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 输出速度2mhz

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

    // GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}



 /**
  * @brief  判断num是否有电平改变
  * @param  
  * @retval key  1 num电平改变    0 num电平未改变
  * @note   GPIO_ReadInputDataBit  读输入电平   
  */

uint8_t Key_GetKeyNum(uint8_t num)
{
    uint8_t Key=0;
    // 上拉输入  默认高电平   低电平输入1
    if (GPIO_ReadInputDataBit(GPIOB, KEY_Pins[num]) == 0)
    {
        Delay_ms(20); // 消抖
        while (GPIO_ReadInputDataBit(GPIOB, KEY_Pins[num]) == 0); // 当它一直在按时，一直输入低电平
        Delay_ms(20);
        Key = 1;
    }
    return Key;
}


/**
 * @brief  检测所有按键，返回被按下的按键号
 * @param  无
 * @retval 0~15：被按下的按键号；0xFF：无按键按下
 */
// uint8_t Key_GetKeyNum(void)
// {
//     uint8_t i;

//     for (i = 0; i < 16; i++)
//     {
//         if (GPIO_ReadInputDataBit(GPIOB, KEY_Pins[i]) == 0)  // 检测到低电平
//         {
//             Delay_ms(20);  // 消抖
//             while (GPIO_ReadInputDataBit(GPIOB, KEY_Pins[i]) == 0)
//                 ;  // 等待松手
//             Delay_ms(20);
//             return i;  // ✅ 返回按键号
//         }
//     }

//     return 0xFF;  // 无按键按下
// }