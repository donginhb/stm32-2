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
//Mini STM32开发板
//扩展例程6--LCD刷屏帧数统计(LCD快速模式)			 
//正点原子@ALIENTEK
//2010/10/12

//此程序的LCD驱动部分,对IO口操作进行了加速处理,使得刷屏速度提高了近一倍.
//具体请看ILI93XX.c和lcd.h文件!

u16 x=0;
int main(void)
{		
  	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  
	LED_Init();
 	LCD_Init();
	Timerx_Init(10000,7199);//10Khz的计数频率，计数到5000为500ms 
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




