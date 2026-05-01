#include "ENCODER.h"
#include "OLED.h"
#include "stm32f10x.h"


//旋转编码器   oled显示
uint16_t count = 0;

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
