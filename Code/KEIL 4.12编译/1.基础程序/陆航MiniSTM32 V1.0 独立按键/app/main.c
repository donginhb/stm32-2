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
#include "Led.h"
#include "Delay.h"
#include "stm32f10x_gpio.h"

/**************************************************************************************
Ĭ��72Mh ��Ƶ �� 
���ļ� system_stm32f10x.c���ж���
#define SYSCLK_FREQ_72MHz  72000000	 �ɸ�����Ҫ�����޸�
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
		  case 3: XOR_LED_D5(); break;	//����(LED������)break;
		  case 4: XOR_LED_D3(); break;
		 default:break;
	   }

	}
}
