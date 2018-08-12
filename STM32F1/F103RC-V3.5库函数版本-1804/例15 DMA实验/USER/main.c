#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "dma.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com  ********/

//DMA ʵ��  

uint8_t  DIS_Buffer[64];//��ʾ�ַ���λ�뻺����

u8 SendBuff[5200];
const u8 TEXT_TO_SEND[]={" mcudev.taobao.com \r\n Ƕ��ʽ������\r\n STM32 DMA ����ʵ��\r\n "};	

	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;//����

 int main(void)
 {	 


	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	
 	KEY_Init();				//������ʼ��	
		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,5168);//DMA1ͨ��4,����Ϊ����1,�洢��ΪSendBuff,����5168.    

	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 DMA     ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("Ƕ��ʽ������\r\n");             //�������
	printf("mcudev.taobao.com\r\n");             //�������
	 
	 
	//��ʾ��ʾ��Ϣ	
	j=sizeof(TEXT_TO_SEND);	
	
	for(i=0;i<5168;i++)//���ASCII�ַ�������
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
	
	i=0;
		
	while(1)
	{
		t=KEY_Scan(0);
		
		if(t)//KEY0����
		{
			t=0;//�����ֵ
			
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Transimit....");
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"   %");//��ʾ�ٷֺ�
			
			printf("\r\nDMA DATA:\r\n"); 	
			
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //ʹ�ܴ���1��DMA����  
			MYDMA_Enable(DMA1_Channel4);//��ʼһ��DMA���䣡	
			
		    //�ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//�ж�ͨ��4�������
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);//���ͨ��4������ɱ�־
					break; 
		        }
				pro=DMA_GetCurrDataCounter(DMA1_Channel4);//�õ���ǰ��ʣ����ٸ�����
				pro=1-pro/5168;//�õ��ٷֱ�	  
				pro*=100;      //����100��
				
        sprintf(DIS_Buffer,"  %3.1f",pro);             //��ʽ���ַ���			
        Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,DIS_Buffer);//��ʾ�ٷֺ�						
			
						
		    }
				
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"  100%");//��ʾ�ٷֺ�//��ʾ100%	  
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Transimit Finished!");//��ʾ�������
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED=!LED;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}
