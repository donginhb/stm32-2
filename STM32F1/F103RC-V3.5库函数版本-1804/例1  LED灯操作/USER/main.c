#include "led.h"
#include "delay.h"
#include "sys.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/


//STM32开发板实验1
//LED灯实验  
//mcudev.taobao.com


 int main(void)
 {	
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"    STM32 LED    ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		delay_ms(300);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		delay_ms(300);
	}
 }

