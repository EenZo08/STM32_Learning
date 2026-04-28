#include "stm32f10x.h"

uint16_t CountSensor_Value;

/**
 * @brief 对射式红外感应初始化               像红外线关卡  挡中间的空隙就触发
 *@param
 *@retval
 *@note GPIOB PB14引脚作输入 上拉输入 外部中断 EXIT
 */

void CountSensor_Init()
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 开AFIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // AFIO选择中断引脚
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

    // EXTI初始化
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // Rising上升沿触发   FALLING下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 中断分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;

    // NVIC_PriorityGroup_2	2 位	2 位	4 级 (0-3)	4 级 (0-3)
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢占优先级   4 级 (0-3)
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 响应优先级   4 级 (0-3)
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// 不能直接提供countsensorValue的值      外面只能读取
uint16_t CountSensor_Get(void)
{
    return CountSensor_Value;
}

/**
 * @brief  EIXT中断函数
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */

void EXTI15_10_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line14) != RESET) // 判断是否是p14触发中断
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0) // 判断引脚电平变化   避免抖动带来影响
        {
            CountSensor_Value++;
        }

        // 清除外部中断0号线的中断标志位
        // 中断标志位必须清除
        // 否则中断将连续不断地触发，导致主程序卡死
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
}