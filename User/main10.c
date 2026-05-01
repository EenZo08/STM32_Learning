#include "timer.h"
#include "OLED.h"
#include "stm32f10x.h"


//定时器2   计数1s显示
uint16_t count = 0;

int main(void)
{

    OLED_Init();
    Timer_Init();
    OLED_ShowString(1, 1, "SECOND:");
    OLED_ShowString(2,1,"CNT:");
    while (1)
    {
        OLED_ShowNum(1, 8, count, 5);
        OLED_ShowNum(2, 8, Timer_GetCount(), 5);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//为1
    {
        count++;
    }
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}