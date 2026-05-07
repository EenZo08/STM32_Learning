#ifndef __AD_H__
#define __AD_H__

#include <stdint.h>

extern uint16_t AD_Value[4];

void AD_Init(void);
uint16_t ADC_GetValue(uint8_t ADC_Channel);

#endif