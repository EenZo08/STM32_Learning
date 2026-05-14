// #include "stm32f10x.h"
// #include "delay.h"
// /**
//  * @brief  SS 写
//  * @param  BitValue 0/1
//  * @retval None
//  * @note   None
//  */
// void MySPI_W_SS(uint8_t BitValue)
// {
//     GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
// }

// /**
//  * @brief  SCK 写
//  * @param  BitValue 0/1
//  * @retval None
//  * @note   None
//  */

// void MySPI_W_SCK(uint8_t BitValue)
// {
//     GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
// }

// /**
//  * @brief  MOSI 写
//  * @param  BitValue 0/1
//  * @retval None
//  * @note   None
//  */
// void MySPI_W_MOSI(uint8_t BitValue)
// {
//     GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
// }

// /**
//  * @brief  MISO 读
//  * @param  None
//  * @retval 0/1
//  * @note   None
//  */
// uint8_t MySPI_R_MISO(void)
// {
//     return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
// }

// /**
//  * @brief  SPI 初始化
//  * @param  None
//  * @retval None
//  * @note   MOSI主输 MISO从输 SCK时钟线 SS转权限
//  */
// void MySPI_Init(void)
// {
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

//     GPIO_InitTypeDef GPIO_InitStruct;
//     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // MOSI主输  通用推挽输出
//     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
//     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOA, &GPIO_InitStruct);

//     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // MISO从输  上拉输入
//     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
//     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

//     GPIO_Init(GPIOA, &GPIO_InitStruct);

//     // SPI初始化 默认电平
//     MySPI_W_SS(1);
//     MySPI_W_SCK(0);
// }

// /**
//  * @brief  开始
//  * @param  参数名  参数说明
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */
// void MySPI_Start(void)
// {
//     // MySPI_W_SCK(0);
//     MySPI_W_SS(0);
//     Delay_us(100);
// }

// /**
//  * @brief  结束
//  * @param  参数名  参数说明
//  * @retval 返回值  返回值说明
//  * @note   补充
//  */
// void MySPI_Stop(void)
// {
//     Delay_us(100);

//     MySPI_W_SS(1);
// }

// /**
//  * @brief  交换一个字节    模式0
//  * @param  data 要发送的字节
//  * @retval None
//  * @note   思路是和从机交换8位数据，每次先发送，再接收
//  */
// uint8_t MySPI_SendByte(uint8_t data)
// {
//     uint8_t i;
//     uint8_t BitReceive = 0;
//     for (i = 0; i < 8; i++)
//     {
//         //!!(data & (0x80 >> i)) 滤掉非1、非0的数
//         MySPI_W_MOSI(!!(data & (0x80 >> i))); // 掩码方式    0x80 1000 0000 0x40 0100 0000   或者直接操作data   模拟移入移出的过程
//         Delay_us(100);
//         MySPI_W_SCK(1); // 上升沿移出数据
//         Delay_us(100);
//         // 正确放置 MOSI 值
//         // if (data & (0x80 >> i))
//         //     MySPI_W_MOSI(1);
//         // else
//         //     MySPI_W_MOSI(0);

//         // MySPI_W_SCK(1); // 上升沿，从机读 MOSI

//         if (MySPI_R_MISO())
//         {
//             BitReceive |= (0x80 >> i);
//         }
//         MySPI_W_SCK(0); // 下降沿接收数据
//         Delay_us(100);
//     }
//     return BitReceive;
// }
#include "stm32f10x.h"                  // Device header

/*引脚配置层*/

/**
  * 函    数：SPI写SS引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SS的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SS为低电平，当BitValue为1时，需要置SS为高电平
  */
void MySPI_W_SS(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);		//根据BitValue，设置SS引脚的电平
}

/**
  * 函    数：SPI写SCK引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入SCK的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置SCK为低电平，当BitValue为1时，需要置SCK为高电平
  */
void MySPI_W_SCK(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);		//根据BitValue，设置SCK引脚的电平
}

/**
  * 函    数：SPI写MOSI引脚电平
  * 参    数：BitValue 协议层传入的当前需要写入MOSI的电平，范围0~1
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，当BitValue为0时，需要置MOSI为低电平，当BitValue为1时，需要置MOSI为高电平
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);		//根据BitValue，设置MOSI引脚的电平，BitValue要实现非0即1的特性
}

/**
  * 函    数：SPI读MISO引脚电平
  * 参    数：无
  * 返 回 值：协议层需要得到的当前MISO的电平，范围0~1
  * 注意事项：此函数需要用户实现内容，当前MISO为低电平时，返回0，当前MISO为高电平时，返回1
  */
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);			//读取MISO电平并返回
}

/**
  * 函    数：SPI初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，实现SS、SCK、MOSI和MISO引脚的初始化
  */
void MySPI_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA4、PA5和PA7引脚初始化为推挽输出
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					//将PA6引脚初始化为上拉输入
	
	/*设置默认电平*/
	MySPI_W_SS(1);											//SS默认高电平
	MySPI_W_SCK(0);											//SCK默认低电平
}

/*协议层*/

/**
  * 函    数：SPI起始
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Start(void)
{
	MySPI_W_SS(0);				//拉低SS，开始时序
}

/**
  * 函    数：SPI终止
  * 参    数：无
  * 返 回 值：无
  */
void MySPI_Stop(void)
{
	MySPI_W_SS(1);				//拉高SS，终止时序
}

/**
  * 函    数：SPI交换传输一个字节，使用SPI模式0
  * 参    数：ByteSend 要发送的一个字节
  * 返 回 值：接收的一个字节
  */
uint8_t MySPI_SendByte(uint8_t ByteSend)
{
	uint8_t i, ByteReceive = 0x00;					//定义接收的数据，并赋初值0x00，此处必须赋初值0x00，后面会用到
	
	for (i = 0; i < 8; i ++)						//循环8次，依次交换每一位数据
	{
		/*两个!可以对数据进行两次逻辑取反，作用是把非0值统一转换为1，即：!!(0) = 0，!!(非0) = 1*/
		MySPI_W_MOSI(!!(ByteSend & (0x80 >> i)));	//使用掩码的方式取出ByteSend的指定一位数据并写入到MOSI线
		MySPI_W_SCK(1);								//拉高SCK，上升沿移出数据
		if (MySPI_R_MISO()){ByteReceive |= (0x80 >> i);}	//读取MISO数据，并存储到Byte变量
															//当MISO为1时，置变量指定位为1，当MISO为0时，不做处理，指定位为默认的初值0
		MySPI_W_SCK(0);								//拉低SCK，下降沿移入数据
	}
	
	return ByteReceive;								//返回接收到的一个字节数据
}
