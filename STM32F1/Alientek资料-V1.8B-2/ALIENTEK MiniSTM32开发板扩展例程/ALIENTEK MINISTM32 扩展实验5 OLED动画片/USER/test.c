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
#include "movie.h"	   
  
//Mini STM32开发板
//扩展例程5--OLED动画显示			 
//正点原子@ALIENTEK
//2010/8/22
   
int main(void)
{	
	u8 t=0;			  
 	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口  		   
	OLED_Init();		 //初始化液晶    		
	OLED_ShowString(0,0,"ALIENTEK");
	OLED_ShowString(0,16,"Mini STM32");
	OLED_ShowString(0,32,"MOVIE SHOW");
	OLED_Refresh_Gram();
	delay_ms(800);
	OLED_ShowString(0,48,"Read...");
	OLED_Refresh_Gram();
	delay_ms(1000);
	OLED_Clear();
	while(1) 
	{	
		Movie_Show_Img(14,12,t);//图片显示在最中央
		OLED_Refresh_Gram();
		if(t<12)delay_ms(600);
		else if(t<14)delay_ms(1000);	  
		else if(t<15)delay_ms(1800);
		else if(t<19)delay_ms(800);
		else if(t<20)delay_ms(1800);
		else if(t<130)delay_ms(100);
		else if(t<132)
		{
			delay_ms(1500);
			delay_ms(1500);
		}else if(t<133)delay_ms(1000);
		else if(t<140)delay_ms(100);
		else if(t<141)
		{
			delay_ms(1800);
			delay_ms(1200);
		} 
		t++;			  
		if(t>140)t=0;
		LED0=!LED0;
	}	  
}

























