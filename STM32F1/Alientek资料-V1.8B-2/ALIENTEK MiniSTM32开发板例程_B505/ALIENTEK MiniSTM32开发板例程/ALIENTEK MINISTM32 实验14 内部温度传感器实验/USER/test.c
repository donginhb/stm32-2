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
#include "rtc.h"
#include "wkup.h"
#include "adc.h"
//Mini STM32开发板范例代码14
//内部温度传感器 实验
//正点原子@ALIENTEK
//技术支持论坛：www.openedv.com
int main(void)
{		
	u16 adcx;
	float temp;
	float temperate;	 
  	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化   
	LED_Init();	
	LCD_Init();  	
	Adc_Init();	

	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"TEMPERATE TEST");	
	LCD_ShowString(60,90,"ATOM@feng fan tec");
	LCD_ShowString(60,110,"2010/12/30");	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,"TEMP_VAL:");	      
	LCD_ShowString(60,150,"TEMP_VOL:0.000V");	      
	LCD_ShowString(60,170,"TEMPERATE:00.00C");	      
	while(1)
	{
		adcx=Get_Temp();
		LCD_ShowNum(132,130,adcx,4,16);//显示ADC的值
		temp=(float)adcx*(3.3/4096);
		temperate=temp;//保存温度传感器的电压值
		adcx=temp;
		LCD_ShowNum(132,150,adcx,1,16);     //显示电压值整数部分
		temp-=(u8)temp;				    	//减掉整数部分		  
		LCD_ShowNum(148,150,temp*1000,3,16);//显示电压小数部分
										  
		temperate=(1.43-temperate)/0.0043+25;//计算出当前温度值	 
		LCD_ShowNum(140,170,(u8)temperate,2,16); //显示温度整数部分
		temperate-=(u8)temperate;	  
		LCD_ShowNum(164,170,temperate*100,2,16);//显示温度小数部分
		LED0=!LED0;
		delay_ms(250);
	}
}






















