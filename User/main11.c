#include "PWM.h"
#include "delay.h"
#include "oled.h"
#include "stm32f10x.h"
#include <stdint.h>



//PWM 实现呼吸灯效果
uint8_t i;

int main(void)
{
    PWM_Init();
    // OLED_Init();
    while (1)
    {

        for (i = 0; i < 100; i++)
        {
            PWM_SetCompare(i);
            Delay_ms(10);
        }
        for (i = 0; i < 100; i++)
        {
            PWM_SetCompare(100 - i);
            Delay_ms(10);
        }
    }
}