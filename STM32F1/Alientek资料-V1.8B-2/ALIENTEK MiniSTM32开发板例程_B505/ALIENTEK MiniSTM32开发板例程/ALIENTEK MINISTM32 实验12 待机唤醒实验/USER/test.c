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
//Mini STM32�����巶������12
//�������� ʵ��
//����ԭ��@ALIENTEK
//����֧����̳��www.openedv.com
int main(void)
{		
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��   
	LED_Init();	  		    
  	WKUP_Init();
	while(1)
	{
		LED0=!LED0;
		delay_ms(250);
	}
}






















