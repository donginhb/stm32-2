/*
*  Copyright(c) 2012-2020     微嵌电子 http://Tonvon.taobao.com
*
*  QQ: 30611966    旺旺：twd3621576   Email: tangweidong2004@163.com 
*
* 硬件平台：陆航MiniStm32开发板
*
* 硬件连接：PC10->D3 PC11->D4 PC12->D5 PD2->D6 PA8->D1
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

void GpioConfigurationLed(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB 
	                       |RCC_APB2Periph_GPIOC
						   |RCC_APB2Periph_GPIOD, ENABLE);
	
	/* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
}
