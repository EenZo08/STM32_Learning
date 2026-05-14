#ifndef __W25Q64_H__
#define __W25Q64_H__
#include "stm32f10x.h"

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint8_t *MemoryType, uint8_t *Capacity);
void W25Q64_WaitBusy(void);
void W25Q64_WriteEnable(void);
void W25Q64_SectorErase(uint32_t Addr);
void W25Q64_PageProgram(uint32_t Addr, uint8_t *DataArray, uint16_t Len);
void W25Q64_ReadData(uint32_t Addr, uint8_t *DataArray, uint16_t Len);

#endif // DEBUG