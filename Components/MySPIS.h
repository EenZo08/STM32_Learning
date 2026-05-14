#ifndef __MYSPIS_H__
#define __MYSPIS_H__
#include "stm32f10x.h"

void MySPIS_Init(void);
void MySPIS_Start(void);
void MySPIS_Stop(void);
uint8_t MySPIS_SendByte(uint8_t data);


#endif // !__MYSPIS_H__
