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
#include "dma.h"
#include "24cxx.h"
#include "flash.h"
#include "touch.h"
#include "24l01.h"
#include "mmc_sd.h"
#include "remote.h"
#include "ds18b20.h"
//Mini STM32�����巶������22
//����ң�� ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
							
int main(void)
{		 	
	short temp;    				    
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  	  
	LCD_Init();			//��ʼ��Һ�� 
	LED_Init();         //LED��ʼ��		 
 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DS18B20 TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2011/1/1");
	while(DS18B20_Init())//��ʼ��DS18B20,����18B20
	{
		LCD_ShowString(60,130,"DS18B20 Check Failed!");
		delay_ms(500);		  
		LCD_ShowString(60,130,"Please Check!        ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
    LCD_ShowString(60,130,"DS18B20 Ready!     ");	 
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ	   
	LCD_ShowString(60,150, "Temperate:   . C");	 
	while(1)
	{	  
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140,150,'-',16,0);//��ʾ����	
		}						 
		LCD_ShowNum(148,150,temp/10,2,16);//��ʾ�¶�ֵ	  
		LCD_ShowNum(172,150,temp%10,1,16);//��ʾ�¶�ֵ
		//printf("t1:%d\n",temp);
		delay_ms(200);
		LED0=!LED0;
	}			   
}


				 






