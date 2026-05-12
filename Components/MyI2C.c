#include "stm32f10x.h"
#include "delay.h"

// 7位地址下时序        起始    发地址+读写位  RA  数据 ....    RA  停止
// RA 从机应答   低电平是应答

/**
 * @brief  软件模拟I2C
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // 初始化I2C引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;         // 通用开漏
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // 引脚只要能通用开漏输出就行
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_SetBits(GPIOB, GPIO_Pin_10); // SCL
    GPIO_SetBits(GPIOB, GPIO_Pin_11); // SDA
}

/**
 * @brief  设置时钟线电平
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_S_SCL(uint8_t val)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)val);
    Delay_us(10);
}

/**
 * @brief  设置数据线电平  set
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   BitAction是标准库内置枚举类型，用于设置引脚电平
 */
void MyI2C_S_SDA(uint8_t val)
{
    GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)val);
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
    uint8_t val;
    val = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
    Delay_us(10);
    return val;
}

/**
 * @brief  起始条件
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_Start(void)
{
    MyI2C_S_SDA(1);
    MyI2C_S_SCL(1);
    MyI2C_S_SDA(0);
    MyI2C_S_SCL(0);
}

/**
 * @brief  发送一个字节
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_SendByte(uint8_t data)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        MyI2C_S_SDA(!!(data & (0x80 >> i))); // 进行两次取反 非0都输出1   ！！（非0）输出1
        MyI2C_S_SCL(1);
        MyI2C_S_SCL(0);
    }
}

/**
 * @brief  发送应答位
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_SendAck(uint8_t ack)
{
    MyI2C_S_SDA(ack);
    MyI2C_S_SCL(1);
    MyI2C_S_SCL(0);
}

/**
 * @brief  接收一个字节
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t MyI2C_RecvByte(void)
{
    uint8_t i;
    uint8_t data = 0;
    for (i = 0; i < 8; i++)
    {
        MyI2C_S_SCL(1); // 主机先释放SCL 时钟线上升
        // if (MyI2C_R_SDA())
        // {
        //     data |= (0x01 << i); // 高位在尾  地位在前
        // }
		if (MyI2C_R_SDA()){data |= (0x80 >> i);}	//读取SDA数据，并存储到Byte变量      低位在尾     对于一个byte，mpu6050是先发高位的数据   0001 1001   先发0

        MyI2C_S_SCL(0);
    }
    return data;
}

/**
 * @brief  接收应答
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
uint8_t MyI2C_RecvAck(void)
{
    MyI2C_S_SDA(1); // 接收前，主机先确保释放SDA，避免干扰从机的数据发送
    MyI2C_S_SCL(1);
    uint8_t ack = MyI2C_R_SDA(); // sda线不止是主机控制的    从机发数据就会接管
    MyI2C_S_SCL(0);
    return ack;
}

/**
 * @brief  停止条件
 * @param  参数名  参数说明
 * @retval 返回值  返回值说明
 * @note   补充
 */
void MyI2C_Stop(void)
{
    MyI2C_S_SDA(0);
    MyI2C_S_SCL(1);
    MyI2C_S_SDA(1);
}
