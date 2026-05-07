#ifndef __DMA_H__
#define __DMA_H__

#include <stdint.h>

void MYDMA_Init(uint32_t Addra, uint32_t Addrb, uint32_t Size);
void MYDMA_Transfer(void);

#endif // !__DMA_H__
    