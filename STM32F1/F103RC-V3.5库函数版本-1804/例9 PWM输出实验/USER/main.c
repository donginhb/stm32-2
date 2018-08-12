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
/********** mcudev.taobao.com  *************/ 


//STM32开发板
//PWM输出实验  

 u16 pwmval=0;	
 
 int main(void)
 {		
 	
	u8 dir=1;	
	delay_init();	    	    //延时函数初始化	  
	NVIC_Configuration(); 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	      //串口初始化为9600
 	LED_Init();			        //LED端口初始化
	 
		Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," Test STM32 PWM ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
 	TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000/900=8Khz

	 while(1)
	{
 		delay_ms(10);	 
		if(dir)pwmval++;
		else pwmval--;

 		if(pwmval>300)dir=0;
		if(pwmval==0)dir=1;										 
		TIM_SetCompare2(TIM3,pwmval);			   
	}	 
 }

