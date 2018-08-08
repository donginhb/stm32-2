#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"	 	 
//Mini STM32�����巶������4
//�ⲿ�ж�ʵ��
 

//ע��,�˴��뻹���޷�����SWD����!��Ϊʹ�����ж�,û������ͨ�ķ��������Ǽ�Ъ����SWD��! 
int main(void)
{			
 	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	EXTIX_Init();		 //�ⲿ�жϳ�ʼ��
	while(1)
	{	    
		printf("OK\n");	
		delay_ms(1000);	  
	}	 
}

























