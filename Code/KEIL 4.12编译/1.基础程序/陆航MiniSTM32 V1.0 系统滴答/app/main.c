/*
*  Copyright(c) 2012-2020     ΢Ƕ���� http://Tonvon.taobao.com
*
*  QQ: 30611966    ������twd3621576   Email: tangweidong2004@163.com 
*
* Ӳ��ƽ̨��½��MiniStm32������
*
* Ӳ�����ӣ�
*===========================================�ļ���Ϣ=======================================================
* �ļ�����:         
* ��    ��:
*
* ���������Keil MDK for ARM 4.12
* ��ǰ�汾: V5.0.0.0
* ��    ��: Tonvdon(a dong)
* �������: 2012-03-03
*
* ȡ���汾:
* ԭ����  :
* �������:
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
   	/* ����SysTick Ϊ10us�ж�һ�� */
	InitSysTick();
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	       Delay_us(60000);    // 50000 * 10us = 500ms
	   XOR_LED_D4();	   //(LED������) 
	   	   Delay_us(40000);    // 50000 * 10us = 500ms
	   XOR_LED_D6();	   //(LED������) 
	   	   Delay_us(20000);    // 50000 * 10us = 500ms
	   XOR_LED_D5();	   //(LED������) 
	   	   Delay_us(10000);    // 50000 * 10us = 500ms
	   XOR_LED_D3();	   //(LED������) 
	}
}
