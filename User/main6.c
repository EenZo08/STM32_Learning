#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "delay.h"

// 按键控制LED
int main(void)
{
    LED_Init();
    Key_Init();
    LED_OFF(0);
    uint8_t i = 0;
    while (1)
    {

        // if (Key_GetKeyNum(0))
        // {
            // // LED_ON(0);
        //     LED_Turn(0); // 翻转
        // }



        if (Key_GetKeyNum(11))
        {
            i = !i;
        }
        if (i)
        {
            // LED_ON(0);
            // Delay_ms(500);
            // LED_OFF(0);

            LED_Turn(0); // 翻转
            Delay_ms(500);
        }
        else
        {
            LED_OFF(0);
        }
    }
}