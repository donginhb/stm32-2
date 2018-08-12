#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/



//STM32开发板
//定时器中断实验  

	
 int main(void)
 {		
 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 //串口初始化为9600
 	LED_Init();			     //LED端口初始化
	 
	 
	 	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"  STM32 Handler  ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	 
	 
	TIM3_Int_Init(4999,7199);//10Khz的计数频率，计数到5000为500ms  
  
	 while(1)
	{
		//LED=!LED;
		delay_ms(200);		   
	}	 

 
}	 
 
