#include "stm32f10x.h"

uint16_t Encoder_Value;

/**
 * @brief 旋转编码器初始化
 *@param
 *@retval
 *@note GPIO_Pin_0  GPIO_Pin_1引脚作输入 上拉输入 外部中断 EXIT
 */

void Encoder_Init()
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // 开AFIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // AFIO选择中断引脚
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);


    // EXTI初始化
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line =  EXTI_Line0 | EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Rising上升沿触发   Falling下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 中断分组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);


    NVIC_InitTypeDef NVIC_InitStructure;                      // 定义结构体变量
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          // 选择配置NVIC的EXTI0线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // 指定NVIC线路的响应优先级为1
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;          // 选择配置NVIC的EXTI0线
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // 指定NVIC线路使能
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 指定NVIC线路的抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;        // 指定NVIC线路的响应优先级为2
    NVIC_Init(&NVIC_InitStructure);
}

uint16_t Encoder_Get(void)
{
    /*使用Temp变量作为中继，目的是返回Encoder_Count后将其清零*/
    /*在这里，也可以直接返回Encoder_Count
      但这样就不是获取增量值的操作方法了
      也可以实现功能，只是思路不一样*/
    uint16_t tem = Encoder_Value;
    Encoder_Value = 0;
    return tem;
}

void EXTI0_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) // 判断是否是p14触发中断
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1) == 0) // 判断引脚电平变化   避免抖动带来影响
        {
            Encoder_Value--;
        }

        // 清除外部中断0号线的中断标志位
        // 中断标志位必须清除
        // 否则中断将连续不断地触发，导致主程序卡死
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/**
 * @brief  EIXT中断函数
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) // 判断是否是p14触发中断
    {
        if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0) // 判断引脚电平变化   避免抖动带来影响
        {
            Encoder_Value++;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}