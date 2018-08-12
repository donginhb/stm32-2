#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "adc.h"


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com  ********/

//ADC 实验  

uint8_t   DIS_Buffer[64];//显示字符区位码缓冲区

u16 adcx;
float temp;

 int main(void)
 {	 

	
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
		 	
 	Adc_Init();		  		//ADC初始化

	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 ADC     ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	//显示提示信息

	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"ADC_VAL:");	      
	Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"ADC_VOL:0.000V");
	 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		
		sprintf(DIS_Buffer,"0x %x",adcx);             //格式化字符串
		Gui_DrawFont_GBK16(0+64,80,BLUE,GRAY0,DIS_Buffer);//显示ADC的值
		
		printf("ADC转换数据值：0x %x\r\n",adcx);             //串口输出
		
		temp=(float)adcx*(3.3/4096);
		
		sprintf(DIS_Buffer,"%06.3f V",temp);             //格式化字符串
		
		Gui_DrawFont_GBK16(0+64,96,BLUE,GRAY0,DIS_Buffer);//显示电压值
		
    printf("ADC检测到的电压值：%06.3f V \r\n",temp);             //串口输出
		
		LED=!LED;
		delay_ms(250);	
		
	}
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

