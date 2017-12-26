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
#include "usart1.h"

static void InitSys(void)
{
 	SystemInit();
}
/***************************************************************************************/
static void InitBSP(void)
{
   	ConfigurationUsart1();
	printf("\r\n this is a printf demo \r\n");
	USART1_printf(USART1, "\r\n This is a USART1_printf demo \r\n");

	USART1_printf(USART1, "\r\n ("__DATE__ " - " __TIME__ ") \r\n"); 	
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
