#include "global.h"

/*
 *@ ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���
 *@ ����delay_us,delay_ms  
 *@ �������ж��е��ó�����ѭ���Ĵ���
 *@ ��ֹ��ʱ��׼ȷ,����do while�ṹ! 
 */

static u8  fac_us=0;                    //us��ʱ������
static u16 fac_ms=0;                    //ms��ʱ������

/*��ʼ���ӳٺ���*/
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;          //ѡ���ڲ�ʱ�� HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}								    
/*
 *@ ��ʱNms
 *@ ע��Nms�ķ�Χ
 *@ Nms<=0xffffff*8/SYSCLK
 *@ ��72M������,Nms<=1864 
 */
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;       //ʱ�����
	SysTick->VAL =0x00;                  //��ռ�����
	SysTick->CTRL=0x01 ;                 //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));    //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                   //�رռ�����
	SysTick->VAL =0X00;                   //��ռ�����	  	    
}   
/*��ʱNus*/								   
void delay_us(u32 Nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=Nus*fac_us;             //ʱ�����	  		 
	SysTick->VAL=0x00;                    //��ռ�����
	SysTick->CTRL=0x01 ;                  //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));    //�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;                   //�رռ�����
	SysTick->VAL =0X00;                   //��ռ�����	    
}  
