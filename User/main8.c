#include "OLED.h"
#include "countsensor.h"
#include "stm32f10x.h"


// 对射式红外感应测试

uint16_t count = 0;
// 按键控制LED
int main(void)
{

    CountSensor_Init();
    OLED_Init();
    OLED_ShowString(1, 1, "COUNTSENSOR:");
    while (1)
    {
        count = CountSensor_Get();
        OLED_ShowNum(2, 1, count, 4);
    }
}

