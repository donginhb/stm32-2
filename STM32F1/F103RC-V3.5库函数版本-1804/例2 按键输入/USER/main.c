#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/

//STM32������ʵ��3
//��������ʵ��  

 u8 t;
 int main(void)
 {
 	
	delay_init();	    	 //��ʱ������ʼ��	  
 	LED_Init();			     //LED�˿ڳ�ʼ��
	KEY_Init();          //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED=0;					//�ȵ������
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 Test Key ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
 		t=KEY_Scan(1);		//�õ���ֵ
		
		if(t)
		{
			t=0;//�����ֵ
		  LED=0;//LED��
		}
		else
		{	
      			
			delay_ms(10); 
			LED=1;//LED��
			
		}

	}	 
 }

