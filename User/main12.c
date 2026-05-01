#include "Servo.h"
#include "delay.h"
#include "key.h"
#include "oled.h"
#include "stm32f10x.h"

// pwm舵机模拟   0-180
float angle = 0;

int main(void)
{
    Servo_Init();
    OLED_Init();
    Key_Init();
    OLED_ShowString(1, 1, "ANGLE:");
    while (1)
    {
        if (Key_GetKeyNum(1) == 1)
        {
            angle += 30;
            if (angle > 180)
            {
                angle = 0;
            }
        }
        Servo_SetAngle(angle);
        OLED_ShowNum(2, 1, angle, 5);
    }
}