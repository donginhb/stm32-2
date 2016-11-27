#include "stm32f10x.h"
#include "crc.h"
__IO uint32_t CRCValue = 0;		 // 用于存放产生的CRC校验值
void ConfigurationCrc(void)
{
	/* Enable CRC clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
}
void TestCrcData(void)
{
    u8 i = 0;
    /* Compute the CRC of "DataBuffer" */
	for(i=0; i<BUFFER_SIZE; i++ ) 
	{
		CRCValue = CRC_CalcBlockCRC((uint32_t *)DataBuffer, BUFFER_SIZE);
		printf("\r\n32-bit CRC 校验码为:0X%X\r\n", CRCValue);
	}
 	printf("\r\nCRC(循环冗余校验)测试成功\r\n");
}
