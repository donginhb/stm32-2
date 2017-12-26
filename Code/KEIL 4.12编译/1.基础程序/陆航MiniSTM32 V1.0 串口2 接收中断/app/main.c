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


const u8 Str[] = {" Thank you for using MiniStm32 Development Board ！^_^ !\r\n"};

static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   	NVIC_ConfigurationUSART2();
	GPIO_Configuration();
	USART2_Configuration();
	printf("***************************************************************\r\n");
	printf("******************Tonvdon.taobao.com***************************\r\n");
	printf("%s",Str);
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
