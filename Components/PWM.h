#ifndef __PWM_H__
#define __PWM_H__
#include <stdint.h>

void PWM_Init(void);
void PWM_SetCompare(uint16_t CompareValue);//设置占空比  ccr的值
void PWM_SetPeriod(uint16_t arr, uint16_t psc);  // 修改 ARR 和 PSC

#endif // DEBUG