#include "Key.h"
#include "Motor.h"
#include "OLED.h"
#include "stm32f10x.h"

int8_t speed = 0;
int8_t speed1 = 0;

int main(void)
{
    Motor1_Init();
    Motor2_Init();
    // OLED_Init();
    Key_Init();
    OLED_ShowString(1, 1, "SPEED:");
    while (1)
    {
        if (Key_GetKeyNum(1) == 1)
        {
            speed += 20;
            if (speed > 100)
            {
                speed = -100;
            }
        }



        if (Key_GetKeyNum(11) == 1){
            speed1 += 20;
            if (speed1 > 100)
            {
                speed1 = 0;
            }
        }

        Motor1_SetSpeed(speed);
        Motor2_SetSpeed(speed1);

        // OLED_ShowSignedNum(2, 1, speed, 5);
    }
}





// int main()
// {
//     OLED_Init();
//     OLED_ShowString(1, 1, "SPEED:");
//     while (1)
//     {
//     }
// }