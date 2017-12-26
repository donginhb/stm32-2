/*********************** Copyright(c) 2012-2020 **********************************************************
*
*  ΢Ƕ���ӣ��Ա��� http://Tonvdon.taobao.com   
*
*  ������twd3621576 QQ: 30611966   Email: tangweidong2004@163.com
* 
*  QQȺ��C���� ����Ӧ�ý���(1)��168545343
*
*  QQȺ��Cortex M0-M3-M4+Lwip+uip(1)��8753696
*
*  QQȺ��Cortex+M0-M3-M4+Lwip+uip(2)��213952438
*
* Ӳ��ƽ̨��MiniSTM32F103VET6 FSMC�� 
*
* Ӳ�����ӣ�
*===========================================�ļ���Ϣ=======================================================
* �ļ�����: mian.c        
* ��    ��: ��ʼ��STM32���ⲿ�ӿ�
*
* ���������Keil MDK for ARM 4.12
* ��ǰ�汾: V1.00
* ��    ��: Tonvdon(a dong)
* �������: 2013-02-25
*
* ȡ���汾:	��
* ԭ����  :
* �������:
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
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	//�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
}
