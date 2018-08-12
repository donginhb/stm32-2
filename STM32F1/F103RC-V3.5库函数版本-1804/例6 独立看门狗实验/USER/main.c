#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "wdg.h"


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/


//STM32������
//�������Ź�ʵ��  

 int main(void)
 {		
	delay_init();	    	     //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	       //���ڳ�ʼ��Ϊ9600
 	LED_Init();		  	       //��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();              //������ʼ��	 
	delay_ms(500);   	       //���˿��õ���
	IWDG_Init(4,625);        //���Ƶ��Ϊ64,����ֵΪ625,���ʱ��Ϊ1s	   
	LED=0;				           //����LED0
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 IWDG     ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
		if(KEY_Scan(1)==1)
		{
			IWDG_Feed();//���K1����,��ι��
		}
		delay_ms(10);
	};	 
}
  

