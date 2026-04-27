#ifndef __LED_H__
#define __LED_H__
#include <stdint.h> // ✅ 添加这一行

void LED_Init();
void LED_ON(uint8_t num);
void LED_OFF(uint8_t num);
void LED_Turn(uint8_t num);

#endif // !__LED_H__
