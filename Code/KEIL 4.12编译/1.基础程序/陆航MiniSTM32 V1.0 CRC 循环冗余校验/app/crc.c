#include "stm32f10x.h"
#include "crc.h"
__IO uint32_t CRCValue = 0;		 // ���ڴ�Ų�����CRCУ��ֵ
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
		printf("\r\n32-bit CRC У����Ϊ:0X%X\r\n", CRCValue);
	}
 	printf("\r\nCRC(ѭ������У��)���Գɹ�\r\n");
}
