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

static void InitSys(void)
{
    /* Setup STM32 system (clock, PLL and Flash configuration) */
 	SystemInit();

}
/***************************************************************************************/
static void InitBSP(void)
{ 
 __IO u32     ChipID[3];

   	 ConfigurationUsart1();
	 /* to get the chipid and put it in ChipID[3] */
	 GetChipID(&ChipID);
	 	/* printf the chipid */
	 printf("\r\nоƬ��ΨһIDΪ: %X-%X-%X\r\n",
	        ChipID[0],ChipID[1],ChipID[2]);

	/* printf the flash memory amount */
    printf("\r\nоƬflash������Ϊ: %dK \r\n", *(__IO u16 *)(0X1FFFF7E0));	
}
int main(void)
{
    InitSys();
    InitBSP();

	for(;;) {
	
	}
}
