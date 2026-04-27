// #include "LED.h"
#include "stm32f10x.h"

/*
    gpioA    PA0-P15的16个引脚

*/

// 引脚查找表   PA0-P15的16个引脚PA0-P15的16个引脚
const uint16_t LED_Pins[] = {
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

void LED_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // pp推挽   od开漏

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // 输出速度2mhz

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

    // GPIO_ResetBits(GPIOC, GPIO_Pin_13);
}

/**
 * @brief  第num个开灯
 * @param  num  第num个开灯
 * @retval 返回值  返回值说明
 * @note   补充
 */

void LED_ON(uint8_t num)
{

    GPIO_ResetBits(GPIOA, LED_Pins[num]);
}

/**
 * @brief  第num个关灯
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */ 
void LED_OFF(uint8_t num)
{

    GPIO_SetBits(GPIOA, LED_Pins[num]);
}



/**
 * @brief   翻转num为led灯
 * @param  num  翻转num为led灯
 * @retval 
 * @note  GPIO_ReadOutputDataBit  读取io脚的输出电平  读取按键的电平 上拉输出  默认是高电平   低电平改变      决定LED是否亮                    用按键改变输出状态     在读取状态  再改变
 */
void LED_Turn(uint8_t num)
{

    if (GPIO_ReadOutputDataBit(GPIOA, LED_Pins[num]))
    { // 当输出状态是低电平    就设置为高电平

        GPIO_ResetBits(GPIOA, LED_Pins[num]);
    }
    else
    {
        GPIO_SetBits(GPIOA, LED_Pins[num]);
    }
}