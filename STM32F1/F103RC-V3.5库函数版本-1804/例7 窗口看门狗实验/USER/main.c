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
/********** mcudev.taobao.com  *************/


//STM32������
//���ڿ��Ź�ʵ��  


 int main(void)
 {		
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 //���ڳ�ʼ��Ϊ9600
 	LED_Init();
	KEY_Init();          //������ʼ��	 
	LED=0;
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 IWDG     ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	 
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
 	while(1)
	{
		LED=1;			  	   
	}   
}
  

