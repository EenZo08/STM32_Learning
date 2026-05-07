#include "stm32f10x.h"

/**
 * @brief  输入捕获初始化   
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   测率   编码器的速率
 */
void IC_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 时基单元初始化
    TIM_TimeBaseInitTypeDef TIM_BASEInitStructure;
    TIM_BASEInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_BASEInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BASEInitStructure.TIM_Period = 65536 - 1;    // arr
    TIM_BASEInitStructure.TIM_Prescaler = 71;        // pcs
    TIM_BASEInitStructure.TIM_RepetitionCounter = 0; // rcr
    TIM_TimeBaseInit(TIM3, &TIM_BASEInitStructure);

    // 输入捕获单元初始化
    TIM_ICInitTypeDef TIM_ICInitStructure;
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICFilter = 0xF;                         // 滤波系数
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;     // 上升沿捕获
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           // 预分频系数
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 直接映射到TI1上
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    // 触发源和从模式
    TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);    // 选择TI1作为触发输入  TI1FP1 = 通道1 引脚输入的信号，经过滤波器后再经过极性选择（是否取反）之后的最终信号
    TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); // 选择复位模式

    TIM_Cmd(TIM3, ENABLE); // 使能定时器3
}

/**
 * @brief  获取输入捕获的频率
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */

uint32_t IC_GetFreq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3) + 1);//测周法得到频率fx = fc / N，这里不执行+1的操作也可
}