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
#include "led.h"
static void InitSys(void)
{
 	SystemInit();
}

/***************************************************************************************/
static void InitBSP(void)
{
    GpioConfigurationLed();
   	/* 配置SysTick 为10us中断一次 */
	InitSysTick();
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	       Delay_us(60000);    // 50000 * 10us = 500ms
	   XOR_LED_D4();	   //(LED共阳极) 
	   	   Delay_us(40000);    // 50000 * 10us = 500ms
	   XOR_LED_D6();	   //(LED共阳极) 
	   	   Delay_us(20000);    // 50000 * 10us = 500ms
	   XOR_LED_D5();	   //(LED共阳极) 
	   	   Delay_us(10000);    // 50000 * 10us = 500ms
	   XOR_LED_D3();	   //(LED共阳极) 
	}
}
