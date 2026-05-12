#include "stm32f10x.h"
#include <stdarg.h>

uint8_t Serial_TXData[4]; // 发送的数据    发什么在外部填进去   数据包长度自定

// 接收hex格式  进制数文件
uint8_t Serial_RXData[4]; // 接收的数据     接收长度要与index对应

// 接收文本数据  转字符串
char Serial_RXStr[100]; // 接收的数据字符串  上限是100x    可能有数据覆盖

uint8_t Serial_RXFlag; // 接收标志

//   发送数据    发送标志位   先到TDR发送数据寄存器    再到发送移位寄存器    通过gpio发     sclk定时只能是输出发送时用 发送特定波 适配
void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;       // 9TX传输引脚            10RX接收引脚
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;    // 9TX传输引脚            10RX接收引脚
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600;                                      // 波特率             初始化会转换
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控制
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 // 只发送
    USART_InitStruct.USART_Parity = USART_Parity_No;                             // 无奇偶校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1;                          // 1个停止位
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;                     // 8个数据位     正常情况 数据+校验=9    8位数据+校验 会舍弃一位做校验位
    USART_Init(USART1, &USART_InitStruct);

    // 使能接收中断  USART接收配置中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;         // 配置USART1中断线
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           // 使能中断
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;        // 响应优先级
    NVIC_Init(&NVIC_InitStruct);

    USART_Cmd(USART1, ENABLE);
}

/**
 * @brief  USART串口发送一个字节
 * @param  Data  要发送的字节
 * @retval 返回值  返回值说明
 * @note   基于ascii表 hex 文本   hex是文本格式  有地址数据  二进制格式数据         根据ascii表 二进制转对应文本字符和操作
 */

void Serial_SendByte(uint8_t Data)
{
    USART_SendData(USART1, Data); // 写入数据寄存器    自动生成波形
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
        ; // 等待发送完成
}

/**
 * @brief  发送字符串
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Serial_SendString(char *str)
{
    while (*str)
    {
        Serial_SendByte(*str++);
    }
}

/**
 * @brief  发送一个数组
 * @param  arr  要发送的数组
 * @param  len  数组长度
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Serial_SendArray(uint8_t *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        Serial_SendByte(arr[i]);
    }
}

/**
 * @brief  次方函数  计算x的y次方
 * @param  x  底数
 * @param  y  指数
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
    uint32_t result = 1;
    for (uint32_t i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}

/**
 * @brief  发送一个数字
 * @param  num  要发送的数字
 * @param  len  数字长度
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Serial_SendNumber(uint32_t num, uint8_t len)
{
    for (int i = 0; i < len; i++)
    {
        Serial_SendByte(num / Serial_Pow(10, len - i - 1) % 10 + '0');
    }
}

/**
 * @brief  发送一个十六进制数字
 * @param  num  要发送的数字
 * @param  len  数字长度
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Serial_SendHex(uint32_t num, uint8_t len)
{
    for (int i = 0; i < len; i++)
    {
        Serial_SendByte(num / Serial_Pow(16, len - i - 1) % 16 + (num / Serial_Pow(16, len - i - 1) % 16 > 9 ? 'A' - 10 : '0'));
    }
}

/**
 * @brief  重定向printf函数  发送到串口
 * @param  ch  要发送的字符
 * @param  f  文件指针
 * @retval 返回值  返回值说明
 * @note   在<stdio.h>
 */
// int fputc(int ch, FILE *f)
// {
//     Serial_SendByte(ch);
//     return ch;
// }

/**
 * @brief  获取接收标志位
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t Serial_GetRXFlag(void)
{
    if (Serial_RXFlag)
    {
        Serial_RXFlag = 0;
        return 1;
    }
    return 0;
}

/**
 * @brief  只查询接收的数据
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
// uint8_t Serial_GetRXData(void)
// {

//     return Serial_RXData;
// }

/**
 * @brief  发送数据包
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   FF 数组  FE
 */
void Serial_SendPacket(void)
{
    Serial_SendByte(0xFF);
    // Serial_SendByte(0x55);
    Serial_SendArray(Serial_TXData, 4);
    Serial_SendByte(0xFE);
}

/**
 * @brief  USART的中断函数
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */

void USART1_IRQHandler(void)
{
    static uint8_t RXState = 0; // 定义当前接收数据的状态

    static uint8_t Index = 0; // 定义当前接收数据的位置

    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        uint8_t RXData = USART_ReceiveData(USART1);
        // Serial_RXFlag = 1;

        // 接收hex数据  FF 数组[4] FE
        // if (RXState == 0)
        // { // 等待接收数据
        //     if (RXData == 0xFF)
        //     {                // 判断包头
        //         RXState = 1; // 切换到接收数据状态
        //         Index = 0;   // 重置当前接收数据的位置
        //     }
        // }
        // else if (RXState == 1)
        // {
        //     Serial_RXData[Index] = RXData; // 接收数据
        //     Index++;
        //     if (Index >= 4)
        //     {
        //         RXState = 2; // 切换到等待接收数据状态
        //     }
        // }
        // else if (RXState == 2)
        // {
        //     if (RXData == 0xFE)
        //     {                      // 判断包尾
        //         RXState = 0;       // 切换到等待接收数据状态

        //         Serial_RXFlag = 1; // 设置接收标志位
        //     }
        // }

        // 接收文本数据  "&" 数组[4] "\r" "\n"
        if (RXState == 0)
        { // 等待接收数据
            if (RXData == '@')
            {                // 判断包头
                RXState = 1; // 切换到接收数据状态
                Index = 0;   // 重置当前接收数据的位置
            }
        }
        else if (RXState == 1)
        {

            if (RXData == '\r')
            {
                RXState = 2; // 切换到等待接收数据状态
            }
            else
            {
                Serial_RXStr[Index++] = RXData; // 接收数据
                // Index++;
            }
        }
        else if (RXState == 2)
        {
            if (RXData == '\n')
            {                // 判断包尾
                RXState = 0; // 切换到等待接收数据状态

                Serial_RXStr[Index] = '\0';

                Serial_RXFlag = 1; // 设置接收标志位
            }
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
