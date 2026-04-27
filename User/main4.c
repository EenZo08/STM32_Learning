#include "Delay.h"
#include "LED.h"
#include "delay.h"

//led模块化
int main(void)
{
    LED_Init();
    while (1)
    {

        // LED_ON(0);
        // Delay_ms(500);
        LED_OFF(0);
        // Delay_ms(500);
    }
}