#include "OLED.h"
#include "serial.h"
#include "stm32f10x.h"



// 收发HEX数据包 
int main(void)
{
    Serial_Init();
    OLED_Init();

    // Serial_TXData[0] = Serial_RXData[0];
    // Serial_TXData[1] = Serial_RXData[1];
    // Serial_TXData[2] = Serial_RXData[2];
    // Serial_TXData[3] = Serial_RXData[3];

    // Serial_SendPacket();

    while (1)
    {

        OLED_ShowHexNum(1, 1, Serial_RXData[0], 2);
        OLED_ShowHexNum(2, 1, Serial_RXData[1], 2);
        OLED_ShowHexNum(3, 1, Serial_RXData[2], 2);
        OLED_ShowHexNum(4, 1, Serial_RXData[3], 2);




        //  1、只查询 只读
        // if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
        // {
        //     RXData = USART_ReceiveData(USART1);
        //     // Serial_RXFlag = 1;
        //     USART_ClearFlag(USART1, USART_FLAG_RXNE);
        //     Serial_SendByte(RXData);
        // }

        // 2、设置中断   使用接收数据
        // if (Serial_GetRXFlag() == 1)
        // {
        //     RXData = Serial_GetRXData();
        //     Serial_SendByte(RXData);
        // }
    }
}