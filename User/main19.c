#include "Serial.h"
#include "stm32f10x.h"
#include <stdio.h>
// #include <stdarg.h>



//eide 是不行（不兼容重写 fputc 函数）
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

// USART 串口发送字节 字符串 数组
int main(void)
{
    Serial_Init();
    Serial_SendByte('a');

    Serial_SendNumber(123456, 6);

    Serial_SendHex(0x12345678, 8);


    Serial_SendString("\r\nhello world!\r\n");


    uint8_t arr[]={0x61, 0x62, 0x63, 0x64};

    Serial_SendArray(arr, 4);

    Serial_SendByte('\r');

    // printf("\r\nhello world!%d\r\n", 1234);
    while (1)
    {
    }
}