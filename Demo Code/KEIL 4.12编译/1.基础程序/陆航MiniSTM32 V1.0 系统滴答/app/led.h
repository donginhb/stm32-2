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
//#define XOR_LED_D1	 GPIOA ->ODR ^= GPIO_Pin_8;
#define XOR_LED_D4()   GPIOC ->ODR ^= GPIO_Pin_11;
#define XOR_LED_D6()   GPIOD ->ODR ^= GPIO_Pin_2;
#define XOR_LED_D5()   GPIOC ->ODR ^= GPIO_Pin_12;
#define XOR_LED_D3()   GPIOC ->ODR ^= GPIO_Pin_10;

  
void GpioConfigurationLed(void);
