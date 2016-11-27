/*
*  Copyright(c) 2012-2020     微嵌电子 http://Tonvon.taobao.com
*
*  QQ: 30611966    旺旺：twd3621576   Email: tangweidong2004@163.com 
*
* 硬件平台：陆航MiniStm32开发板
*
* 硬件连接：
*===========================================文件信息=======================================================
* 文件名称:         
* 功    能:
*
* 编译软件：Keil MDK for ARM 4.12
* 当前版本: V5.0.0.0
* 作    者: Tonvdon(a dong)
* 完成日期: 2012-03-03
*
* 取代版本:
* 原作者  :
* 完成日期:
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
