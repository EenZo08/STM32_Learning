#ifndef __SERIAL_H__
#define __SERIAL_H__
#include "stm32f10x.h"

void Serial_Init(void);
void Serial_SendByte(uint8_t data);
void Serial_SendString(char *str);
void Serial_SendNumber(uint32_t num, uint8_t len);
void Serial_SendHex(uint32_t num, uint8_t len);
void Serial_SendArray(uint8_t *arr, int len);
uint8_t Serial_GetRXFlag(void);
uint8_t Serial_GetRXData(void);

#endif