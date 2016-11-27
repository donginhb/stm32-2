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
* 硬件平台：MiniSTM32F103VET6 FSMC板 
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
* 取代版本:	无
* 原作者  :
* 完成日期:
*********************************************************************************************************
*/
#include "stm32f10x_gpio.h"

void GpioConfigurationLed(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	/* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
}
