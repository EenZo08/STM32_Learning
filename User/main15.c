#include "AD.h"
#include "OLED.h"
#include "delay.h"
#include "stm32f10x.h"

//AD是ADC电路量化后的值 显示AD值  AD单通道测试 电位器

// 滑动平均滤波    先存10个取平均再显示
#define FILTER_N 10 // 滤波窗口大小

uint16_t adc_buffer[FILTER_N]; // 存放最近 10 次采样值
uint8_t filter_index = 0;      // 当前写入位置
uint8_t filter_full = 0;       // 是否已存满 10 次

// 添加一次新采样
void ADC_Filter_Add(uint16_t new_val)
{
    adc_buffer[filter_index] = new_val; // 存入数组
    filter_index++;
    if (filter_index >= FILTER_N)
    {
        filter_index = 0;
        filter_full = 1; // 已经转了一圈，数组满了
    }
}

// 求当前平均值
uint16_t ADC_Filter_GetAvg(void)
{
    uint32_t sum = 0;
    uint8_t count = filter_full ? FILTER_N : filter_index; // 不满10次时只算已有的
    for (uint8_t i = 0; i < count; i++)
    {
        sum += adc_buffer[i];
    }
    return (uint16_t)(sum / count);
}

int main(void)
{

    uint16_t adc_val;
    uint16_t avg;

    AD_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "AD:");
    OLED_ShowString(2, 1, "V:");

    while (1)
    {

        // 显示AD值
        adc_val = ADC_GetValue();             // 读一次 ADC
        ADC_Filter_Add(adc_val);              // 加入滤波数组
        avg = ADC_Filter_GetAvg();            // 取平均值
        OLED_ShowNum(1, 4, avg , 4); // 0-4095  12位ad   2^12=4096     0-3.3V分成4096份

        // 转换
        float voltage = (float)ADC_GetValue() * 3.3 / 4096;
        OLED_ShowNum(2, 3, voltage, 1); // 显示整数

        OLED_ShowNum(2, 4, (uint16_t)(voltage * 100) % 100, 3);
        Delay_ms(50);
    }

}