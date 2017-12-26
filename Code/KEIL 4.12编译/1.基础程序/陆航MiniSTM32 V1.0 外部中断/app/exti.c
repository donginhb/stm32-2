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
#include "stm32f10x.h"

static void NvicConfiguration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置P[A|B|C|D|E] 0位为中断源 目前用到的是PC0*/ 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/*************************************************************************/
void GpioConfigurationEXtiKey(void)
{
     GPIO_InitTypeDef GPIO_InitStructure; 
	 EXTI_InitTypeDef EXTI_InitStructure;
	 	/* config the extiline(PC0) clock and AFIO clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO,ENABLE);

     	/* EXTI line gpio config(PC0) */	
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 // 上拉输入
     GPIO_Init(GPIOC, &GPIO_InitStructure);
	 
	 NvicConfiguration();
	 
	 	/* EXTI line(PC0) mode config */
     GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0); 
     EXTI_InitStructure.EXTI_Line = EXTI_Line0;
     EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
     EXTI_InitStructure.EXTI_LineCmd = ENABLE;
     EXTI_Init(&EXTI_InitStructure);  
}
/***************************************************************************/