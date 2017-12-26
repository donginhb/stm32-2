/******************** (C) COPYRIGHT 2009 STMicroelectronics ********************
* File Name      : SysTick.c
* Author         : ����
* Version        : V1.0
* Date           : 04/05/2009
* Description    : ϵͳ��ʱ��������
*******************************************************************************/

#include "config.h" 

static __IO uint32_t TimingDelay;//ȫ�ֱ������� 

 
/*******************************************************************************
* Function Name  : SysTick_Config
* Description    : systick��ʼ������.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 void SysTick_IntConfig(void)
{ 
    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemFrequency / 1000))
    { 
        /* Capture error */ 
        while (1);       
    }
} 
 

 
/*******************************************************************************
* Function Name  : Delay_ms
* Description    : �ӳٺ���ĺ���.
* Input          : nTime ��Ҫ��ʱ��ʱ�䣬��λΪ����
* Output         : None
* Return         : None
*******************************************************************************/
void Delay_ms(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}


/*******************************************************************************
* Function Name  : TimingDelay_Decrement
* Description    : �ݼ������������������ɡ�stm32f10x_it.c���е��ж���Ӧ��������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/ 
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}