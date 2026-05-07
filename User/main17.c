#include "dma.h"
#include "oled.h"
#include "stm32f10x.h"

//dma 数组数据转移测试
int main(void)
{
    // 程序代码都在sram   const修饰在flash中   但只读  要转换器才能写
    uint8_t a[] = {01, 02, 03, 04};//与byte对应   8：byte   16：halfword  32：word
    uint8_t b[4];

    uint8_t i = 0;

    OLED_Init();
    OLED_ShowString(1, 1, "a:");
    OLED_ShowString(3, 1, "b:");

    OLED_ShowHexNum(1, 3, (uint32_t)a, 8); // 显示 SRAM下数组a的地址值
    OLED_ShowHexNum(3, 3, (uint32_t)b, 8); // 显示 SRAM下数组b的地址值

    MYDMA_Init((uint32_t)a, (uint32_t)b, 4);
    MYDMA_Transfer();

    // OLED_ShowHexNum(2, 1, (uint32_t)&a[0], 8); // 显示 SRAM下数组a的地址值
    // OLED_ShowHexNum(4, 1, (uint32_t)&b[0], 8); // 显示 SRAM下数组b的地址值

    for (i = 0; i < 4; i++)
    {
        OLED_ShowNum(2, 1 + i * 2, a[i], 2); // 显示 SRAM下数组b的每个元素值
    }

    for (i = 0; i < 4; i++)
    {
        OLED_ShowNum(4, 1 + i * 2, b[i], 2); // 显示 SRAM下数组b的每个元素值
    }

    while (1)
    {
    }
}