#include "stm32f10x.h"
#include "Encoder.h"
#include "TIMer.h"

int16_t speed;

// 输入捕获   编码器测5
int main(void)
{

    while (1)
    {
    }
}


/**
 * @brief  函数功能描述
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   3用来测速  2计数
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        speed = Encoder_Get();
    }
}