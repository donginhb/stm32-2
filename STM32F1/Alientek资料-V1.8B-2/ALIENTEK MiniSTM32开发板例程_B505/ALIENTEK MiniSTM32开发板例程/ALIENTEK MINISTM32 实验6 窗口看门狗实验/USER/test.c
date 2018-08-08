#include <stm32f10x_lib.h>
#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h" 
#include "key.h"
#include "exti.h"
#include "wdg.h"	 	 
//Mini STM32开发板范例代码6
//窗口看门狗实验
//正点原子@ALIENTEK
//技术支持论坛：www.openedv.com
   
int main(void)
{	
  	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	LED_Init();		  	 //初始化与LED连接的硬件接口
	LED0=0;
	delay_ms(300);	  
	WWDG_Init(0X7F,0X5F,3);//计数器值为7f,窗口寄存器为5f,分频数为8	   
 	while(1)
	{
		LED0=1;			  	   
	}	 
}

























