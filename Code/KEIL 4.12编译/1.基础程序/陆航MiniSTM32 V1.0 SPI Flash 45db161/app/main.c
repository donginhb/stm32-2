/*
*  Copyright(c) 2012-2020     ΢Ƕ���� http://Tonvon.taobao.com
*
*  QQ: 30611966    ������twd3621576   Email: tangweidong2004@163.com 
*
* Ӳ��ƽ̨��½��MiniStm32������
*
* Ӳ�����ӣ�
*===========================================�ļ���Ϣ=======================================================
* �ļ�����:         
* ��    ��:
*
* ���������Keil MDK for ARM 4.12
* ��ǰ�汾: V5.0.0.0
* ��    ��: Tonvdon(a dong)
* �������: 2012-03-03
*
* ȡ���汾:
* ԭ����  :
* �������:
*********************************************************************************************************
*/
#include "stm32f10x_gpio.h"
#include "usart1.h"
#include "AT45DB161.H"

static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   	ConfigurationUsart1();
	printf("\r\n this is a printf demo \r\n");
	USART1_printf(USART1, "This is a USART1_printf demo \r\n");
	USART1_printf(USART1, "("__DATE__ " - " __TIME__ ") \r\n");
	
	SPI1_Init();
	  /* Get SPI Flash ID */
  FLASH_ID = SPI_FLASH_ReadID();
  if(FLASH_ID ==  AT45DB161D_FLASH_ID){
  	printf(" FlashID: 0x%x\r\n",FLASH_ID);
  }
  else{
  	 	printf("Failed");
  } 	
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
