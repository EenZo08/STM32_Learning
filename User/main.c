#include "ENCODER.h"
#include "OLED.h"
#include "stm32f10x.h"

uint16_t count = 0;
// 按键控制LED
int main(void)
{

    Encoder_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "ENCODER:");
    while (1)
    {
        count += Encoder_Get(); // 0-65535
        OLED_ShowNum(2, 1, count, 5);
    }
}
