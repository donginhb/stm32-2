#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "exti.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/


//STM32开发板实验
//外部中断实验  

	
 int main(void)
 {		
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
 	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();         	//初始化与按键连接的硬件接口
	EXTIX_Init();		 	//外部中断初始化
	LED=0;					//点亮LED0
	 
	  Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   Test IO EXTI   ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{	    
		printf("OK\r\n");	
		delay_ms(1000);	  
	}
 }

