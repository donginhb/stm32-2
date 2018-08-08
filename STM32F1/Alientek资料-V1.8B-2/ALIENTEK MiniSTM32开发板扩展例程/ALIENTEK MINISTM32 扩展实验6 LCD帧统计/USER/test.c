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
//Mini STM32������
//��չ����6--LCDˢ��֡��ͳ��(LCD����ģʽ)			 
//����ԭ��@ALIENTEK
//2010/10/12

//�˳����LCD��������,��IO�ڲ��������˼��ٴ���,ʹ��ˢ���ٶ�����˽�һ��.
//�����뿴ILI93XX.c��lcd.h�ļ�!

u16 x=0;
int main(void)
{		
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  
	LED_Init();
 	LCD_Init();
	Timerx_Init(10000,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	while(1)
	{
		LCD_Clear(BLUE);
		x++;
		LCD_Clear(GREEN);
		x++;
		LCD_Clear(RED);
		x++;
	}			    
}




