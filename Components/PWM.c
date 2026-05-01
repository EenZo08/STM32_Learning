#include "stm32f10x.h"

/**
 * @brief  PWM初始化
 * @param
 * @retval
 * @note   依靠定时器输出电平，通过ccr和arr的比较得到ref高低电平
 */
void PWM_Init(void)
{

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    // 用pa0引脚   注意引脚的默认复用功能有没包含定时器
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;//对应TIM2_CH3输出比较通道3     GPIO_Pin_0;对应是可外部输入TIM2_CH1_ETR    GPIO_Pin_1  通道1对应定时器输出比较通道2 TIM_OC2Init
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // TIM_InternalClockConfig(TIM2);//选择TIM2为内部时钟    时钟有4种    默认是内部的 可以不写

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision     = TIM_CKD_DIV1;       // 时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能 要输入捕获（测红外脉宽）或外部时钟模式（红外计速）时，才需要关心它。分频越大，滤波越强，但响应会变慢
    TIM_TimeBaseStructure.TIM_CounterMode       = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseStructure.TIM_Period            = 100 - 1;            // 计数周期   ARR    计数上限     -1从0开始   10000x1ms       
    TIM_TimeBaseStructure.TIM_Prescaler         = 720 - 1;            // 预分频    psc    拦截7100   给1个脉冲给计数器             720-1
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                  // 重复计数器，高级定时器才会用到
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /*输出比较初始化*/
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);                       // 结构体初始化，若结构体没有完整赋值,则最好执行此函数，给结构体所有成员都赋一个默认值,避免结构体初值不确定的问题
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;        // 选择PWM模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 输出使能
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;    // 输出极性，高电平有效
    // 高级定时器才会用到   
    //  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable; // 输出使能
    //  TIM_OCInitStructure.TIM_OCNPolarity  = TIM_OCNPolarity_High;    // 输出极性，高电平有效
    //  TIM_OCInitStructure.TIM_OCIdleState  = TIM_OCIdleState_Set;     // 闲置状态
    TIM_OCInitStructure.TIM_Pulse = 0; // 脉宽值    CCR  提供给外面配置

    // TIM_OC1Init(TIM2, &TIM_OCInitStructure);
    // TIM_OC2Init(TIM2, &TIM_OCInitStructure);
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);//直流电机用通道x输出  

    TIM_Cmd(TIM2, ENABLE); // 使能TIM2
}

/**
 * @brief  设置CCR   比较器的值
 * @param
 * @retval
 * @note
 */
void PWM_SetCompare(uint16_t CompareValue)
{
    TIM_SetCompare3(TIM2, CompareValue);
}

/**
 * @brief  修改 ARR 和 PSC
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void PWM_SetPeriod(uint16_t arr, uint16_t psc)
{

    TIM_SetAutoreload(TIM2, arr);
    TIM2->PSC = psc;                                 // 直接写寄存器
    TIM_GenerateEvent(TIM2, TIM_EventSource_Update); // 手动生成更新事件，让 PSC 立即生效

    TIM_SetCompare3(TIM2, 0); // 防止切换时误输出
}
