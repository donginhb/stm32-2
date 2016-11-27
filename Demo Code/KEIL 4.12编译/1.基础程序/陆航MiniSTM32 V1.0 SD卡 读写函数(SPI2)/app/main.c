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
* 功    能:	测试 SD 卡是否可用 串口一 以及 LED_D1 亮灭观察
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

#define LED_D1_ON()  (GPIOA->ODR &= ~GPIO_Pin_8)
#define LED_D1_OFF() (GPIOA->ODR |= GPIO_Pin_8)

void ConfigurationLED(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE); 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);						 
/**
 *	LED -> PB1
 */					 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   	ConfigurationUsart1();
	ConfigurationLED();
	printf("\r\n this is a SD Test demo \r\n");
	USART1_printf(USART1, "\r\n this is a SD Test demo \r\n");
	USART1_printf(USART1, "\r\n ("__DATE__ " - " __TIME__ ") \r\n"); 
	
	ConfigurationSDCard(); 
if (TestSD_ReadWriteFunction()) {
    LED_D1_ON();  //D1 
    printf ( " SD ReadWriteFunction Success !\r\n");   
}
else{LED_D1_OFF();   
    printf ( " SD ReadWriteFunction Fail !\r\n");  
	}	
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
