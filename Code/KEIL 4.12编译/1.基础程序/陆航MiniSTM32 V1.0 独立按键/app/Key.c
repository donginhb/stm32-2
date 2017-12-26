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

void GpioConfigurationKey(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable Button GPIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);

	/* Configure Button pin as input floating */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);

   	/* Configure Button pin as input floating */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;  //
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
u8 ScanKey(void)
{
static u8 KeyUpFlag;

	  if( KeyUpFlag && (
	      (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) == 0) ||
	  	  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == 0) ||
		  (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) == 0) ||
		  (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) )
	     ) {  
	     DelayKey(0x54321);  KeyUpFlag = 0;
	     
         if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) == 0)  {
		 
		    return  1;
		 }
		 if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == 0)  {
		 
		    return  2;
		 }
		 if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) == 0)  {
		 
		    return  3;
		 }
		 if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)  {
		 
		    return  4;
		 }
   }
   else if((GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0) == 1) &&
	  	   (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) == 1) &&
		   (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2) == 1) &&
		   (GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1) 
   
   )  {KeyUpFlag = 1; }

   return 0;
}
