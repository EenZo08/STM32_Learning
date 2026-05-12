#include "OLED.h"
#include "serial.h"
#include "stm32f10x.h"

uint8_t RXData;
// uint8_t Serial_RXFlag;

// USART 串口单片机接收数据   1、只查询 只读  2、设置中断   使用接收数据
int main(void)
{
    Serial_Init();
    OLED_Init();
    while (1)
    {
        //  1、只查询 只读
        // if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
        // {
        //     RXData = USART_ReceiveData(USART1);
        //     // Serial_RXFlag = 1;
        //     USART_ClearFlag(USART1, USART_FLAG_RXNE);
        //     Serial_SendByte(RXData);
        // }

       

        // 2、设置中断   使用接收数据
        if (Serial_GetRXFlag() == 1)
        {
            RXData = Serial_GetRXData();
            Serial_SendByte(RXData);
        }
        // 发送数据
        // Serial_SendByte('A');
        // delay_ms(1000);
        // Serial_SendByte('B');
        // delay_ms(1000);
        // Serial_SendByte('C');
        // delay_ms(1000);

         OLED_ShowHexNum(1, 1, RXData, 2);
    }
}