#include "AD.h"
#include "OLED.h"
#include "delay.h"
#include "stm32f10x.h"

// ADC多通道测试  没有dma情况下 表里存一个读一个  只用一个通道    单通道 非扫描   改一次扫一次读一次

uint16_t A0;
uint16_t A1;
uint16_t A2;
uint16_t A3;

// uint16_t adc_vals[4]; // 存放四个ADC结果

// #define ADC_TIMEOUT_MAX 100000 // 超时上限，按需调整

/**
 * @brief  带超时退出的多通道ADC读取
 * @param  adc_buf：存放ADC结果的数组，长度至少为通道数
 * @param  n_ch：要读取的通道总数
 * @retval 0 表示读取成功，-1 表示超时
 */
// int ADC_ReadMultiChannel(uint16_t *adc_buf, uint8_t n_ch)
// {
//     uint32_t timeout;
//     uint8_t i;

//     // 1. 启动一次完整的扫描
//     ADC_SoftwareStartConvCmd(ADC1, ENABLE);

//     // 2. 逐通道读取
//     for (i = 0; i < n_ch; i++)
//     {
//         timeout = ADC_TIMEOUT_MAX;
//         while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         {
//             if (--timeout == 0)
//             {
//                 // 超时退出，返回错误码
//                 return -1;
//             }
//         }
//         adc_buf[i] = ADC_GetConversionValue(ADC1);
//     }

//     return 0; // 读取成功
// }

// void ADC_ADC_MultiChannelRead(void)
// {
//     // 读取流程示例 (主循环或任务函数中)
//     ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 启动一次完整的扫描

//     while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         ;                              // 等Rank 1完成
//     A0 = ADC_GetConversionValue(ADC1); // 读到通道0数据

//     while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         ;                              // 等Rank 2完成
//     A1 = ADC_GetConversionValue(ADC1); // 读到通道1数据

//     while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         ;                              // 等Rank 3完成
//     A2 = ADC_GetConversionValue(ADC1); // 读到通道2数据

//     while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))
//         ;                              // 等Rank 4完成
//     A3 = ADC_GetConversionValue(ADC1); // 读到通道3数据
// }

int main(void)
{
    AD_Init();
    OLED_Init();

    while (1)
    {
        // // 读取多通道ADC
        // if (ADC_ReadMultiChannel(adc_vals, 4) == 0)
        // {
        //     // 读取成功，更新显示
        //     OLED_ShowNum(1, 1, adc_vals[0], 4);
        //     OLED_ShowNum(1, 6, adc_vals[1], 4);
        //     OLED_ShowNum(2, 1, adc_vals[2], 4);
        //     OLED_ShowNum(2, 6, adc_vals[3], 4);
        // }
        // else
        // {
        //     // 超时处理：可以显示错误、重试或复位ADC
        //     OLED_ShowString(1, 1, "ADC Err");
        // }

        A0 = ADC_GetValue(ADC_Channel_0);
        OLED_ShowNum(1, 1, A0, 4);
        A1 = ADC_GetValue(ADC_Channel_1);
        OLED_ShowNum(1, 6, A1, 4);
        A2 = ADC_GetValue(ADC_Channel_2);
        OLED_ShowNum(2, 1, A2, 4);
        A3 = ADC_GetValue(ADC_Channel_3);
        OLED_ShowNum(2, 6, A3, 4);
        Delay_ms(500);
    }
}