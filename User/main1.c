#include "Delay.h"
#include "stm32f10x.h"

// 点亮pa0的led灯    流水灯

int main(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // PA0

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // reset   低电平 0   set 高电平 1    挽 输出低电平 亮
    // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);

    // GPIO_SetBits(GPIOA, GPIO_Pin_0);

    while (1)
    {
        // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_SET);
        // Delay_ms(500);
        // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);
        // Delay_ms(500);



    }
}