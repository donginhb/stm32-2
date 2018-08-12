#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "tsensor.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/

//内部温度传感器 实验  

uint8_t  DIS_Buffer[64];//显示字符区位码缓冲区

	u16 adcx;
	float temp;
 	float temperate;

 int main(void)
 {	 

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	 	
  T_Adc_Init();		  		//ADC初始化

	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"  STM32 TSENSOR  ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	
		//显示提示信息

	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"TEMP_VAL:");	      
	Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"TEMP_VOL:");
  Gui_DrawFont_GBK16(0,112,BLUE,GRAY0,"TEMP_CVL:");

	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		
		sprintf(DIS_Buffer,"0x%x",adcx);             //格式化字符串
		Gui_DrawFont_GBK16(0+72,80,BLUE,GRAY0,DIS_Buffer);//显示ADC的值
		
		printf("嵌入式开发网\r\n");             //串口输出
		printf("mcudev.taobao.com\r\n");             //串口输出
		printf("\r\n");             //串口输出
		printf("ADC转换数据值：0x %x\r\n",adcx);             //串口输出
		
		
		temp=(float)adcx*(3.3/4096);
		
		temperate=temp;//保存温度传感器的电压值
		
		sprintf(DIS_Buffer,"%6.3fV",temperate);             //格式化字符串
		
		Gui_DrawFont_GBK16(0+72,96,BLUE,GRAY0,DIS_Buffer);//显示电压值
		
    printf("温度传感器的电压值：%6.3f \r\n",temp);             //串口输出
										  
		
		temperate=(1.43-temperate)/0.0043+25;		//计算出当前温度值	
		
		sprintf(DIS_Buffer,"%5.2fC",temperate);             //格式化字符串
		
		Gui_DrawFont_GBK16(0+72,112,BLUE,GRAY0,DIS_Buffer);//显示电压值
		
    printf("温度传感器的温度值：%6.2f ℃\r\n",temp);             //串口输出
		
		printf("\r\n");             //串口输出
		
		LED=!LED;
		delay_ms(250);
		
	}
 }

