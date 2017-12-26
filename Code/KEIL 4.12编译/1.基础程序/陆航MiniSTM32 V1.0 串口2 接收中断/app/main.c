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
#include "stm32f10x.h" 


const u8 Str[] = {" Thank you for using MiniStm32 Development Board ��^_^ !\r\n"};

static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   	NVIC_ConfigurationUSART2();
	GPIO_Configuration();
	USART2_Configuration();
	printf("***************************************************************\r\n");
	printf("******************Tonvdon.taobao.com***************************\r\n");
	printf("%s",Str);
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
