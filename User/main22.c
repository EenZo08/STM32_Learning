#include "LED.h"
#include "OLED.h"
#include "serial.h"
#include "stm32f10x.h"
#include "string.h"

// 发文本数据包
int main(void)
{
    Serial_Init();
    OLED_Init();
    LED_Init();

    // Serial_TXData[0] = Serial_RXData[0];
    // Serial_TXData[1] = Serial_RXData[1];
    // Serial_TXData[2] = Serial_RXData[2];
    // Serial_TXData[3] = Serial_RXData[3];

    // Serial_SendPacket();

    while (1)
    {
        if (Serial_RXFlag == 1)
        {
            OLED_ShowString(1, 1, Serial_RXStr);
            // LED_ON(0);
            if (strcmp(Serial_RXStr, "LED_ON") == 0)
            {
                LED_ON(0);
            }
            else if (strcmp(Serial_RXStr, "LED_OFF") == 0)
            {
                LED_OFF(0);
            }
        }

        // OLED_ShowHexNum(1, 1, Serial_RXData[0], 2);
        // OLED_ShowHexNum(2, 1, Serial_RXData[1], 2);
        // OLED_ShowHexNum(3, 1, Serial_RXData[2], 2);
        // OLED_ShowHexNum(4, 1, Serial_RXData[3], 2);
    }
}