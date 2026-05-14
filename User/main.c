#include "OLED.h"
#include "W25Q64.h"
#include "stm32f10x.h"

uint8_t ArrayWrite[] = {0x01, 0x02, 0x03, 0x04};	//定义要写入数据的测试数组
uint8_t ArrayRead[4];	

int main(void)
{
    OLED_Init();
    uint8_t MID;
    uint8_t DID;
    uint8_t Capacity;
    W25Q64_Init();
    W25Q64_ReadID(&MID, &DID, &Capacity);

    OLED_ShowHexNum(1, 1, MID, 2);
    OLED_ShowHexNum(1, 4, DID, 2);
    OLED_ShowHexNum(1, 7, Capacity, 2);

    // /*W25Q64功能函数测试*/
    // W25Q64_SectorErase(0x000000);                // 扇区擦除
    // W25Q64_PageProgram(0x000000, ArrayWrite, 4); // 将写入数据的测试数组写入到W25Q64中

    // W25Q64_ReadData(0x000000, ArrayRead, 4); // 读取刚写入的测试数据到读取数据的测试数组中

    // /*显示数据*/
    // OLED_ShowHexNum(2, 3, ArrayWrite[0], 2); // 显示写入数据的测试数组
    // OLED_ShowHexNum(2, 6, ArrayWrite[1], 2);
    // OLED_ShowHexNum(2, 9, ArrayWrite[2], 2);
    // OLED_ShowHexNum(2, 12, ArrayWrite[3], 2);

    // OLED_ShowHexNum(3, 3, ArrayRead[0], 2); // 显示读取数据的测试数组
    // OLED_ShowHexNum(3, 6, ArrayRead[1], 2);
    // OLED_ShowHexNum(3, 9, ArrayRead[2], 2);
    // OLED_ShowHexNum(3, 12, ArrayRead[3], 2);
    while (1)
    {
    }
}