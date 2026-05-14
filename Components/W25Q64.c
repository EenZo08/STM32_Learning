#include "MySPI.h"
#include "MySPIS.h"
#include "W25Q64_Ins.h"
#include "delay.h"
#include "stm32f10x.h"

// void W25Q64_Init(void)
// {
//     MySPI_Init();
// }

// /**
//  * @brief  读取W25Q64的id
//  * @param  MID  指向uint8_t的指针，用于存储.Manufacturer ID    工厂id
//  * @param  DID  指向uint8_t的指针，用于存储.Device ID           设备id
//  * @retval 返回值  返回值说明
//  * @note  JEDEC ID 24位  分三段    0xEF 制造商id  0x40设备id  0x18容量
//  */
// void W25Q64_ReadID(uint8_t *MID, uint8_t *MemoryType, uint8_t *Capacity)
// {
//     MySPI_Start();

//     MySPI_SendByte(0X9F);

//     *MID = MySPI_SendByte(0XFF);        // 制造商id
//     *MemoryType = MySPI_SendByte(0XFF); // 设备id
//     // *DID <<= 8;
//     *Capacity = MySPI_SendByte(0XFF); // 容量

//     MySPI_Stop();
// }

// /**
//  * @brief  写使能
//  * @param  参数名  参数说明
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */

// void W25Q64_WriteEnable(void)
// {
//     MySPI_Start();
//     MySPI_SendByte(W25Q64_WRITE_ENABLE);
//     MySPI_Stop();
// }

// /**
//  * @brief  等busy
//  * @param  参数名  参数说明
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */

// void W25Q64_WaitBusy(void)
// {
//     uint32_t i;

//     MySPI_Start();
//     MySPI_SendByte(W25Q64_READ_STATUS_REGISTER_1); // 交换发送读状态寄存器1的指令
//     i = 100000;
//     // 1为busy
//     while (MySPI_SendByte(W25Q64_DUMMY_BYTE) & 0x01)
//     {
//         i--;
//         if (i == 0)
//         {
//             break;
//         }
//     };
//     MySPI_Stop();
// }

// /**
//  * @brief  页编程
//  * @param  Addr  地址
//  * @param  DataArray  数据组
//  * @param  Len  长度  每页256字节
//  * @retval 返回值  返回值说明
//  * @note   不能跨页   只会重头开始
//  */

// void W25Q64_PageProgram(uint32_t Addr, uint8_t *DataArray, uint16_t Len)
// {

//     W25Q64_WriteEnable();

//     MySPI_Start();
//     MySPI_SendByte(W25Q64_PAGE_PROGRAM);
//     MySPI_SendByte(Addr >> 16);
//     MySPI_SendByte(Addr >> 8); // 1110 1110
//     MySPI_SendByte(Addr);
//     for (uint16_t i = 0; i < Len; i++)
//     {
//         MySPI_SendByte(DataArray[i]);
//         DataArray++;
//     }
//     MySPI_Stop();
//     W25Q64_WaitBusy();
// }

// /**
//  * @brief  扇区擦除 4kb
//  * @param  参数名  参数说明
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */
// void W25Q64_SectorErase(uint32_t Addr)
// {
//     W25Q64_WriteEnable();
//     MySPI_Start();
//     MySPI_SendByte(W25Q64_SECTOR_ERASE_4KB);
//     MySPI_SendByte(Addr >> 16);
//     MySPI_SendByte(Addr >> 8);
//     MySPI_SendByte(Addr);
//     MySPI_Stop();
//     W25Q64_WaitBusy();
// }

// /**
//  * @brief   读取数据
//  * @param  Address 读取数据的起始地址，范围：0x000000~0x7FFFF
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */

// void W25Q64_ReadData(uint32_t Addr, uint8_t *DataArray, uint16_t Len)
// {
//     MySPI_Start();
//     MySPI_SendByte(W25Q64_READ_DATA);
//     MySPI_SendByte(Addr >> 16);
//     MySPI_SendByte(Addr >> 8);
//     MySPI_SendByte(Addr);
//     for (uint16_t i = 0; i < Len; i++)
//     {
//         DataArray[i] = MySPI_SendByte(W25Q64_DUMMY_BYTE);
//     }
//     MySPI_Stop();
// }

/**
 * 函    数：W25Q64初始化
 * 参    数：无
 * 返 回 值：无
 */
void W25Q64_Init(void)
{
    MySPIS_Init(); // 先初始化底层的SPI
}

/**
 * 函    数：W25Q64读取ID号
 * 参    数：MID 工厂ID，使用输出参数的形式返回
 * 参    数：DID 设备ID，使用输出参数的形式返回
 * 返 回 值：无
 */
void W25Q64_ReadID(uint8_t *MID, uint8_t *DID, uint8_t *Capacity)
{
    MySPIS_Start();                            // SPI起始
    MySPIS_SendByte(W25Q64_JEDEC_ID);          // 交换发送读取ID的指令
    *MID = MySPIS_SendByte(W25Q64_DUMMY_BYTE); // 交换接收MID，通过输出参数返回
    *DID = MySPIS_SendByte(W25Q64_DUMMY_BYTE); // 交换接收DID高8位
    // *DID <<= 8;									//高8位移到高位
    *Capacity = MySPIS_SendByte(W25Q64_DUMMY_BYTE); // 或上交换接收DID的低8位，通过输出参数返回
    MySPIS_Stop();                                  // SPI终止
}

/**
 * 函    数：W25Q64写使能
 * 参    数：无
 * 返 回 值：无
 */
void W25Q64_WriteEnable(void)
{
    MySPIS_Start();                       // SPI起始
    MySPIS_SendByte(W25Q64_WRITE_ENABLE); // 交换发送写使能的指令
    MySPIS_Stop();                        // SPI终止
}

/**
 * 函    数：W25Q64等待忙
 * 参    数：无
 * 返 回 值：无
 */
void W25Q64_WaitBusy(void)
{
    uint32_t Timeout;
    MySPIS_Start();                                             // SPI起始
    MySPIS_SendByte(W25Q64_READ_STATUS_REGISTER_1);             // 交换发送读状态寄存器1的指令
    Timeout = 100000;                                           // 给定超时计数时间
    while ((MySPIS_SendByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01) // 循环等待忙标志位
    {
        Timeout--;        // 等待时，计数值自减
        if (Timeout == 0) // 自减到0后，等待超时
        {
            /*超时的错误处理代码，可以添加到此处*/
            break; // 跳出等待，不等了
        }
    }
    MySPIS_Stop(); // SPI终止
}

/**
 * 函    数：W25Q64页编程
 * 参    数：Address 页编程的起始地址，范围：0x000000~0x7FFFFF
 * 参    数：DataArray	用于写入数据的数组
 * 参    数：Count 要写入数据的数量，范围：0~256
 * 返 回 值：无
 * 注意事项：写入的地址范围不能跨页
 */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
    uint16_t i;

    W25Q64_WriteEnable(); // 写使能

    MySPIS_Start();                       // SPI起始
    MySPIS_SendByte(W25Q64_PAGE_PROGRAM); // 交换发送页编程的指令
    MySPIS_SendByte(Address >> 16);       // 交换发送地址23~16位
    MySPIS_SendByte(Address >> 8);        // 交换发送地址15~8位
    MySPIS_SendByte(Address);             // 交换发送地址7~0位
    for (i = 0; i < Count; i++)           // 循环Count次
    {
        MySPIS_SendByte(DataArray[i]); // 依次在起始地址后写入数据
    }
    MySPIS_Stop(); // SPI终止

    W25Q64_WaitBusy(); // 等待忙
}

/**
 * 函    数：W25Q64扇区擦除（4KB）
 * 参    数：Address 指定扇区的地址，范围：0x000000~0x7FFFFF
 * 返 回 值：无
 */
void W25Q64_SectorErase(uint32_t Address)
{
    W25Q64_WriteEnable(); // 写使能

    MySPIS_Start();                           // SPI起始
    MySPIS_SendByte(W25Q64_SECTOR_ERASE_4KB); // 交换发送扇区擦除的指令
    MySPIS_SendByte(Address >> 16);           // 交换发送地址23~16位
    MySPIS_SendByte(Address >> 8);            // 交换发送地址15~8位
    MySPIS_SendByte(Address);                 // 交换发送地址7~0位
    MySPIS_Stop();                            // SPI终止

    W25Q64_WaitBusy(); // 等待忙
}

/**
 * 函    数：W25Q64读取数据
 * 参    数：Address 读取数据的起始地址，范围：0x000000~0x7FFFFF
 * 参    数：DataArray 用于接收读取数据的数组，通过输出参数返回
 * 参    数：Count 要读取数据的数量，范围：0~0x800000
 * 返 回 值：无
 */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
    uint32_t i;
    MySPIS_Start();                    // SPI起始
    MySPIS_SendByte(W25Q64_READ_DATA); // 交换发送读取数据的指令
    MySPIS_SendByte(Address >> 16);    // 交换发送地址23~16位
    MySPIS_SendByte(Address >> 8);     // 交换发送地址15~8位
    MySPIS_SendByte(Address);          // 交换发送地址7~0位
    for (i = 0; i < Count; i++)        // 循环Count次
    {
        DataArray[i] = MySPIS_SendByte(W25Q64_DUMMY_BYTE); // 依次在起始地址后读取数据
    }
    MySPIS_Stop(); // SPI终止
}
