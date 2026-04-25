#include "delay.h"
#include "stm32f10x.h" // Device header

// 点亮最小系统板的pc13  LED灯

int main(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//pp推挽   od开漏

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);

    GPIO_ResetBits(GPIOC, GPIO_Pin_13);

    while (1)
    {

        // LED 闪烁
        //   GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);
        //  Delay_ms(500 ms);

        //  GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);
        // Delay_ms(500 ms);
    }
}