#include "AD.h"
#include "OLED.h"
#include "stm32f10x.h"


//ADC+DMA  多通道采样数据转换
int main(void)
{

    AD_Init();
    OLED_Init();
    while (1)
    {
        OLED_ShowNum(1, 1 , AD_Value[0], 4);
        OLED_ShowNum(2, 1 , AD_Value[1], 4);
        OLED_ShowNum(3, 1 , AD_Value[2], 4);
        OLED_ShowNum(4, 1 , AD_Value[3], 4);
    }
}