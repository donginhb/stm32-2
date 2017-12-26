/*********************** Copyright(c) 2012-2020 **********************************************************
*
*  微嵌电子：淘宝店 http://Tonvdon.taobao.com   
*
*  旺旺：twd3621576 QQ: 30611966   Email: tangweidong2004@163.com
* 
*  QQ群：C语言 深入应用交流(1)：168545343
*
*  QQ群：Cortex M0-M3-M4+Lwip+uip(1)：8753696
*
*  QQ群：Cortex+M0-M3-M4+Lwip+uip(2)：213952438
*
* 硬件平台： 
*
* 硬件连接：
*===========================================文件信息=======================================================
* 文件名称: mian.c        
* 功    能: 初始化STM32与外部接口
*
* 编译软件：Keil MDK for ARM 4.12
* 当前版本: V1.00
* 作    者: Tonvdon(a dong)
* 完成日期: 2013-02-25
*
* 取代版本:
* 原作者  :
* 完成日期:
*********************************************************************************************************
*/
#include "stm32f10x_gpio.h"
#include "Led.h"
#include "Delay.h"
//上电后系统有个默认时钟启动(先可以不配置 一般配置在72Mh)
static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
    GpioConfigurationLed();   
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {

	   GPIOC ->ODR = GPIO_Pin_6;	   //熄灭(LED共阳极)
	   GPIOC ->ODR &= ~GPIO_Pin_7;
	   DelayLED(0x543210);
	   GPIOC ->ODR &= ~GPIO_Pin_6;	   //点亮(LED共阳极)
	   GPIOC ->ODR = GPIO_Pin_7;
	   DelayLED(0x543210);	
	}
}
/***********************微嵌电子：淘宝店 http://Tonvdon.taobao.com ***********************************************************/
