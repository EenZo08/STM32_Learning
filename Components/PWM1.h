#ifndef __PWM1_H__
#define __PWM1_H__
#include <stdint.h>

void PWM1_Init(void);
void PWM1_SetCompare(uint16_t CompareValue);//设置占空比  ccr的值
// void PWM1_SetPeriod(uint16_t arr, uint16_t psc);  // 修改 ARR 和 PSC

#endif // DEBUG