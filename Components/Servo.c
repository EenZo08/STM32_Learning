#include "PWM.h"
#include "stm32f10x.h"

void Servo_Init(void)
{
    PWM_Init();
    
    // 切换为舵机模式：50Hz (20ms)，ARR=20000-1, PSC=72-1
    // PWM_SetPeriod(20000 - 1, 72 - 1);
}

/**
 * @brief  设置角度
 * @param  angle  要设置的角度0-180
 * @retval 返回值  返回值说明
 * @note   补充
 */
void Servo_SetAngle(float angle)
{

    // 控制舵机角度
    // 0度 → 500μs → CCR = 500
    // 90度 → 1500μs → CCR = 1500
    // 180度 → 2500μs → CCR = 2500
    PWM_SetCompare(angle / 180 * 2000 + 500);
}
