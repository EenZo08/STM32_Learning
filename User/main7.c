// #include "OLED.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "stm32f10x.h"

int main(void)
{
    Buzzer_Init();
    LightSensor_Init();
    while (1)
    {
        if (LightSensor_Get())
        {
            Buzzer_ON();
        }
        else
        {
            Buzzer_OFF();
        }
    }
}