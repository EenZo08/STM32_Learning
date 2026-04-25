#include "Delay.h"
#include "stm32f10x.h"

// 流水灯

int main(void)
{

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 开启GPIO的时钟

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; // PA0

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // reset   低电平 0   set 高电平 1    挽 输出低电平 亮
    // GPIO_WriteBit(GPIOA, GPIO_Pin_0, Bit_RESET);

    // GPIO_SetBits(GPIOA, GPIO_Pin_0);

    while (1)
    {
        /*使用GPIO_Write，同时设置GPIOA所有引脚的高低电平，实现LED流水灯*/
        GPIO_Write(GPIOA, ~0x0001); // 0000 0000 0000 0001，PA0引脚为低电平，其他引脚均为高电平，注意数据有按位取反
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0002); // 0000 0000 0000 0010，PA1引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0004); // 0000 0000 0000 0100，PA2引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0008); // 0000 0000 0000 1000，PA3引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0010); // 0000 0000 0001 0000，PA4引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0020); // 0000 0000 0010 0000，PA5引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0040); // 0000 0000 0100 0000，PA6引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
        GPIO_Write(GPIOA, ~0x0080); // 0000 0000 1000 0000，PA7引脚为低电平，其他引脚均为高电平
        Delay_ms(100);              // 延时100ms
    }
}