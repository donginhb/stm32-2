#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "wdg.h"


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/


//STM32开发板
//独立看门狗实验  

 int main(void)
 {		
	delay_init();	    	     //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	       //串口初始化为9600
 	LED_Init();		  	       //初始化与LED连接的硬件接口
	KEY_Init();              //按键初始化	 
	delay_ms(500);   	       //让人看得到灭
	IWDG_Init(4,625);        //与分频数为64,重载值为625,溢出时间为1s	   
	LED=0;				           //点亮LED0
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 IWDG     ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
		if(KEY_Scan(1)==1)
		{
			IWDG_Feed();//如果K1按下,则喂狗
		}
		delay_ms(10);
	};	 
}
  

