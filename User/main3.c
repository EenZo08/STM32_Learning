#include "Delay.h"
#include "stm32f10x.h"

// 蜂鸣器  低电平触发  reset

int main(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; // PA0

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // reset   低电平 0   set 高电平 1    挽 输出低电平 亮
    // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);

    // GPIO_SetBits(GPIOA, GPIO_Pin_0);

    while (1)
    {
        GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_RESET);
        Delay_s(1);
        GPIO_WriteBit(GPIOB, GPIO_Pin_12, Bit_SET);
        Delay_s(1);

    }
}