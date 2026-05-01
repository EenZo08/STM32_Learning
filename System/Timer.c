#include "stm32f10x.h"

/**
 * @brief  定时器初始化
 * @param
 * @retval
 * @note   TIM1/2/3/4    用定时器2    2-5在apb1
 */

void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 开始定时器2的APB1时钟

    // TIM_InternalClockConfig(TIM2);//选择TIM2为内部时钟    时钟有4种    默认是内部的


    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseStructure.TIM_Period = 10000 - 1;               // 计数周期   ARR    计数上限     -1从0开始   10000x1ms
    TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;             // 预分频    psc    拦截7100   给1个脉冲给计数器
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            // 重复计数器，高级定时器才会用到
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 手动清除定时器更新标志位
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);

    // 开启更新中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 配置NVIC中断优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 配置分组2

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 响应1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}

/**
 * @brief  获取cnt值
 * @param  参数名  参数说明
 * @retval cnt值
 * @note   0-ARR的值
 */

uint16_t Timer_GetCount(void)
{
    return TIM_GetCounter(TIM2);//cnt的值
}

/**
 * @brief  定时器2的中断函数
 * @param
 * @retval
 * @note   补充
 */
// void TIM2_IRQHandler(void)
// {
//     if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//为1
//     {
//     }
//     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
// }