#include "stm32f10x.h"

uint16_t AD_Value[4];
/**
 * @brief  ADC
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   电压转换为数字信号
 */

void AD_Init(void)
{
    // 使能ADC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); // 使能 DMA1 时钟

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // 配置ADC时钟 6分频 72MHz / 6 = 12MHz

    // 配置GPIOA PA0引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;                                    // 模拟输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; // GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 55个时钟周期芯片固定的  12.5+ 采样时间              输入时：采样、保持时间
    // 序列和通道    通道可以重复  序列决定优先
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // 规则组的序列1  组的第一个位置配置   通道0   第x位的次序  1-16 55个时钟周期

    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5); // 规则组的序列1  组的第二个位置配置   通道1    55个时钟周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5); // 规则组的序列1  组的第三个位置配置   通道2   55个时钟周期
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5); // 规则组的序列1  组的第四个位置配置   通道3    55个时钟周期

    // 配置ADC参数
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 外部触发 软件触发
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;              // 12位数据右对齐

    // 单次非扫描
    // ADC_InitStruct.ADC_ScanConvMode = DISABLE;       // 规则组 关闭扫描模式  一个序列一个序列的转换
    // ADC_InitStruct.ADC_ContinuousConvMode = DISABLE; // 转换模式 关闭连续转换 单次转化

    // 连续扫描 + 连续转换    连续扫描只需要开启一次转换  随后会自动转化
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;       // 规则组 开启扫描模式  一个序列一个序列的转换
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; // 转换模式 开启连续转换 单次转化

    // 扫描模式 + 单次转换 没有dma下 的多通道测试
    // ADC_InitStruct.ADC_ScanConvMode = ENABLE;        // 规则组 关闭扫描模式  一个序列一个序列的转换
    // ADC_InitStruct.ADC_ContinuousConvMode = DISABLE; // 转换模式 关闭连续转换 单次转化

    ADC_InitStruct.ADC_NbrOfChannel = 4; // 通道数量为1   与上面配置的序列组数量一致
    ADC_Init(ADC1, &ADC_InitStruct);

    DMA_InitTypeDef DMA_InitStruct;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;             // 要转数据的地址  外设基地址
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            // 外设地址递增  数组要递增
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; // 外设数据宽度 byte 8位  halfword 16位 word 32位
    DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)AD_Value;                  // 存储到地址   存储器
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                     // 内存地址递增
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         // 内存数据宽度 和外设数据宽度  要一致
    DMA_InitStruct.DMA_BufferSize = 4;                                       // 要转的字节数
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                          // 转运方向  从外设到存储器
    DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                                // 内存到内存传输  开启          MtoM  内存到内存传输是软件触发 sram和flash 芯片内的数据交流  硬件触发要关  外设和芯片交流
    DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                             // 传输模式 正常
    DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                       // 优先级中等

    DMA_Init(DMA1_Channel1, &DMA_InitStruct);
    DMA_Cmd(DMA1_Channel1, ENABLE); // 使能

    ADC_DMACmd(ADC1, ENABLE);       // ADC1触发DMA1的信号使能
    
    ADC_Cmd(ADC1, ENABLE);          // 使能ADC

    // 校验ADC  固定流程
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1))
        ;
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1))
        ;
    // 开启转换  连续转化
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/**
 * @brief  函数功能描述
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   单通道非扫描
 */
uint16_t ADC_GetValue(uint8_t ADC_Channel)
{

    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); // 重新配置

    // 开启转换  连续转化
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    // 等待转换完成
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
        ;
    // while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);

    // 返回转换结果
    return ADC_GetConversionValue(ADC1);
}

// 扫描模式 + 单次转换 的规则组   没有dma存 是会覆盖的
/**
 * @brief  函数功能描述
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
// uint16_t ADC_GetValue(uint8_t rank)
// {
//     ADC_SoftwareStartConvCmd(ADC1, ENABLE);
//     while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         ;
//     if (rank >= 1 && rank <= 4)
//     {
//         return ADC_GetConversionValue(ADC1); // 你已有的读取函数
//     }
//     return 0;
// }
