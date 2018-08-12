#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/

//STM32开发板实验3
//按键输入实验  

 u8 t;
 int main(void)
 {
 	
	delay_init();	    	 //延时函数初始化	  
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	LED=0;					//先点亮红灯
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 Test Key ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com ");  
	 
	while(1)
	{
 		t=KEY_Scan(1);		//得到键值
		
		if(t)
		{
			t=0;//清除键值
		  LED=0;//LED亮
		}
		else
		{	
      			
			delay_ms(10); 
			LED=1;//LED灭
			
		}

	}	 
 }

