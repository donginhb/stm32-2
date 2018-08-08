#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"
#include "oled.h" 	
#include "oledhz.h"	
  
//Mini STM32������-��չʵ��3
//OLED������ʾ			 
//����ԭ��@ALIENTEK
//2010/8/22
   
int main(void)
{				  
 	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
												   
	OLED_Init();			//��ʼ��Һ��     
	OLED_Refresh_Gram();	 				    		  
	OLED_ShowString22(20,10,"ALIENTEK");
	OLED_ShowString22(4,32,"STM32"); 
	OLED_ShowFont22(59,32,0,1);
	OLED_ShowFont22(81,32,1,1);
	OLED_ShowFont22(103,32,2,1);
	OLED_Refresh_Gram();	 
		
	while(1) 
	{	
		delay_ms(300);
		LED0=!LED0;
	}	  
}

























