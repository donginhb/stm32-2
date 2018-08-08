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
#include "adc.h"
//Mini STM32�����巶������14
//�ڲ��¶ȴ����� ʵ��

int main(void)
{		
	u16 adcx;
	float temp;
	float temperate;	 
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��   
	LED_Init();	
	LCD_Init();  	
	Adc_Init();	

	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"TEMPERATE TEST");	
	LCD_ShowString(60,90,"ATOM@feng fan tec");
	LCD_ShowString(60,110,"2011/12/30");	
	//��ʾʱ��
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(60,130,"TEMP_VAL:");	      
	LCD_ShowString(60,150,"TEMP_VOL:0.000V");	      
	LCD_ShowString(60,170,"TEMPERATE:00.00C");	      
	while(1)
	{
		adcx=Get_Temp();
		LCD_ShowNum(132,130,adcx,4,16);//��ʾADC��ֵ
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//�����¶ȴ������ĵ�ѹֵ
		adcx=temp;
		LCD_ShowNum(132,150,adcx,1,16);     //��ʾ��ѹֵ��������
		temp-=(u8)temp;				    	//������������		  
		LCD_ShowNum(148,150,temp*1000,3,16);//��ʾ��ѹС������
										  
		temperate=(1.43-temperate)/0.0043+25;//�������ǰ�¶�ֵ	 
		LCD_ShowNum(140,170,(u8)temperate,2,16); //��ʾ�¶���������
		temperate-=(u8)temperate;	  
		LCD_ShowNum(164,170,temperate*100,2,16);//��ʾ�¶�С������
		LED0=!LED0;
		delay_ms(250);
	}
}






















