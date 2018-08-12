#include "led.h"
#include "delay.h"
#include "sys.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/


//STM32������ʵ��1
//LED��ʵ��  
//mcudev.taobao.com


 int main(void)
 {	
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"    STM32 LED    ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		delay_ms(300);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		delay_ms(300);
	}
 }

