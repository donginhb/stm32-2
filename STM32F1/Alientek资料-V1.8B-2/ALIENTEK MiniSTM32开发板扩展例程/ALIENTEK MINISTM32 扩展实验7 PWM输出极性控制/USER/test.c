#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"
#include "timer.h"	 	 
//Mini STM32��������չʵ�� 7
//PWM��� ʵ��
//����ԭ��@ALIENTEK
//2010.12.25	
   

int main(void)
{				 
 	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	PWM_Init(90,0);	 //����Ƶ��PWMƵ��=72000/900=8Khz
   	//����ͨ��ע�ͣ�TIM3->CCER|=1<<5;��䣬���ۿ�������˽����ȫ������漴�ɿ�����
	//�ڲ��ι۲������½�һ��PORTA.7���źţ����ܿ����޸�TIM3->CCER��5λ��ֵ�����Ľ���ˡ�
	while(1)
	{	
		TIM3->CCER|=1<<5;   //�͵�ƽ��Ч						 
 		delay_ms(10);	 	  					 
		LED0_PWM_VAL=45;	   
 		delay_ms(10);	 
 		LED0_PWM_VAL=0;	  
		delay_ms(10);	 
		LED0_PWM_VAL=45;	   
		delay_ms(10);	 
 		LED0_PWM_VAL=0;	   
		TIM3->CCER&=~(1<<5);//�ߵ�ƽ��Ч 						 
 		delay_ms(10);	 	  					 
		LED0_PWM_VAL=45;	   
 		delay_ms(10);	 
 		LED0_PWM_VAL=0;	  
		delay_ms(10);	 
		LED0_PWM_VAL=45;	   
		delay_ms(10);	 
 		LED0_PWM_VAL=0;	
	}	 
}

























