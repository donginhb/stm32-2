#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com  *************/ 


//STM32������
//PWM���ʵ��  

 u16 pwmval=0;	
 
 int main(void)
 {		
 	
	u8 dir=1;	
	delay_init();	    	    //��ʱ������ʼ��	  
	NVIC_Configuration(); 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	      //���ڳ�ʼ��Ϊ9600
 	LED_Init();			        //LED�˿ڳ�ʼ��
	 
		Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," Test STM32 PWM ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
 	TIM3_PWM_Init(899,0);	 //����Ƶ��PWMƵ��=72000/900=8Khz

	 while(1)
	{
 		delay_ms(10);	 
		if(dir)pwmval++;
		else pwmval--;

 		if(pwmval>300)dir=0;
		if(pwmval==0)dir=1;										 
		TIM_SetCompare2(TIM3,pwmval);			   
	}	 
 }

