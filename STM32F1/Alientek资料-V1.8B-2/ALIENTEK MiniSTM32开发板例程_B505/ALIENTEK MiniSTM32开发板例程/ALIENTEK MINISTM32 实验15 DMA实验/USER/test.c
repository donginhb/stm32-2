#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "lcd.h"	   
#include "rtc.h"
#include "wkup.h"
#include "adc.h"
#include "dma.h"
//Mini STM32�����巶������15
//DMA ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com

u8 SendBuff[5200];
const u8 TEXT_TO_SEND[]={"ALIENTEK MiniSTM32 DMA ����ʵ��"};	 
int main(void)
{		
	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;//����
			   
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��   
	LED_Init();
	KEY_Init();	
	LCD_Init(); 
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,5200);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����5200.

 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DMA USART TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");
	//��ʾ��ʾ��Ϣ
	LCD_ShowString(60,130,"Press KEY0 To Start!");

	j=sizeof(TEXT_TO_SEND);	   
	for(i=0;i<5200;i++)//���ASCII�ַ�������
    {
		if(t>=j)//���뻻�з�
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}   	   
    }		 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
	while(1)
	{
		t=KEY_Scan();
		if(t==1)//KEY0����
		{
			LCD_ShowString(60,150,"Start Transimit....");
			LCD_ShowString(60,170,"   %");//��ʾ�ٷֺ�
			printf("\n\nDMA DATA:\n"); 	    
		    USART1->CR3=1<<7;           //ʹ�ܴ���1��DMA����       
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	  
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		    while(1)
		    {
				if(DMA1->ISR&(1<<13))//�ȴ�ͨ��4�������
				{
					DMA1->IFCR|=1<<13;//���ͨ��4������ɱ�־
					break; 
		        }
				pro=DMA1_Channel4->CNDTR;//�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/5200;//�õ��ٷֱ�	  
				pro*=100;      //����100��
				LCD_ShowNum(60,170,pro,3,16);	  
		    }			    
			LCD_ShowNum(60,170,100,3,16);//��ʾ100%	  
			LCD_ShowString(60,150,"Transimit Finished!");//��ʾ�������
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}






















