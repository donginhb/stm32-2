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
#include "stm32f10x.h"

static void InitSys(void)
{
    /* Setup STM32 system (clock, PLL and Flash configuration) */
 	SystemInit();

}
/***************************************************************************************/
static void InitBSP(void)
{ 
 __IO u32     ChipID[3];

   	 ConfigurationUsart1();
	 /* to get the chipid and put it in ChipID[3] */
	 GetChipID(&ChipID);
	 	/* printf the chipid */
	 printf("\r\n芯片的唯一ID为: %X-%X-%X\r\n",
	        ChipID[0],ChipID[1],ChipID[2]);

	/* printf the flash memory amount */
    printf("\r\n芯片flash的容量为: %dK \r\n", *(__IO u16 *)(0X1FFFF7E0));	
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
