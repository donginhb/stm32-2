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
#include "Led.h"
#include "Delay.h"
#include "stm32f10x_gpio.h"

/**************************************************************************************
默认72Mh 主频 ： 
在文件 system_stm32f10x.c中有定义
#define SYSCLK_FREQ_72MHz  72000000	 可根据需要自行修改
****************************************************************************************/
static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   GpioConfigurationLed();
   GpioConfigurationKey();
}
/***************************************************************************************/
int main(void)
{  u8 TempKey;
    InitSys();
    InitBSP();

	for(;;) {

       TempKey = ScanKey();

	   switch(TempKey) {
	   	  
		  case 1: XOR_LED_D4(); break;
		  case 2: XOR_LED_D6(); break;
		  case 3: XOR_LED_D5(); break;	//点亮(LED共阳极)break;
		  case 4: XOR_LED_D3(); break;
		 default:break;
	   }

	}
}
