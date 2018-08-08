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
//Mini STM32开发板范例代码11
//RTC实时时钟 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com	  

const u8 *COMPILED_DATE=__DATE__;//获得编译日期
const u8 *COMPILED_TIME=__TIME__;//获得编译时间

const u8* Week[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int main(void)
{		
	u8 t=0;		
 	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化   
	LED_Init();	  		    
	LCD_Init();	
	RTC_Init();	  
	//RTC_Set(2004,12,31,23,59,55);  //设置时间	   
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"RTC TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,"    -  -  ");	   
	LCD_ShowString(60,162,"  :  :  ");		    
	while(1)
	{								    
		if(t!=timer.sec)
		{
			t=timer.sec;
			LCD_ShowNum(60,130,timer.w_year,4,16);									  
			LCD_ShowNum(100,130,timer.w_month,2,16);									  
			LCD_ShowNum(124,130,timer.w_date,2,16);	 
			switch(timer.week)
			{
				case 0:
					LCD_ShowString(60,148,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60,148,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60,148,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60,148,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60,148,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60,148,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60,148,"Saturday ");
					break;  
			}
			LCD_ShowNum(60,162,timer.hour,2,16);									  
			LCD_ShowNum(84,162,timer.min,2,16);									  
			LCD_ShowNum(108,162,timer.sec,2,16);
			LED0=!LED0;
		}	
		delay_ms(10);								  
	};  
}






















