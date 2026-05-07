#include "stm32f10x_dma.h"

uint16_t MyDMA_Size;
void MYDMA_Init(uint32_t Addra, uint32_t Addrb, uint32_t Size)
{
    MyDMA_Size = Size;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 使能 DMA1 时钟

    DMA_InitTypeDef DMA_InitStruct;
    DMA_InitStruct.DMA_PeripheralBaseAddr = Addra;                       // 要转数据的地址  外设基地址
    DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Enable;    // 外设地址递增  数组要递增
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; // 外设数据宽度 byte 8位  halfword 16位 word 32位
    DMA_InitStruct.DMA_MemoryBaseAddr     = Addrb;                       // 存储到地址   存储器
    DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;        // 内存地址递增
    DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;     // 内存数据宽度 和外设数据宽度  要一致
    DMA_InitStruct.DMA_BufferSize         = Size;                        // 要转的字节数
    DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;       // 转运方向  从外设到存储器
    DMA_InitStruct.DMA_M2M                = DMA_M2M_Enable;              // 内存到内存传输  开启          MtoM  内存到内存传输是软件触发 sram和flash 芯片内的数据交流  硬件触发要关  外设和芯片交流
    DMA_InitStruct.DMA_Mode               = DMA_Mode_Normal;             // 传输模式 正常
    DMA_InitStruct.DMA_Priority           = DMA_Priority_Medium;         // 优先级中等

    DMA_Init(DMA1_Channel1, &DMA_InitStruct);
    DMA_Cmd(DMA1_Channel1, DISABLE); // 先失能
}

void MYDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);                   // 先失能
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size); // 设置当前数据计数器
    DMA_Cmd(DMA1_Channel1, ENABLE);                    // 使能

    while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); // 等待传输完成
    DMA_ClearFlag(DMA1_FLAG_TC1);                      // 清除传输完成标志位
}