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
#include "dma.h"
#include "24cxx.h"
#include "flash.h" 		 
//Mini STM32开发板范例代码17
//SPI 实验
//


//要写入到W25X16的字符串数组
const u8 TEXT_Buffer[]={"MiniSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
			   
  	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化   
	LED_Init();	   		//LED初始化
	KEY_Init();	   		//按键初始化
	LCD_Init();    		//TFTLCD液晶初始化
	SPI_Flash_Init();   //SPI FLASH 初始化 


 	POINT_COLOR=RED;//设置字体为蓝色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"SPI TEST");	
	LCD_ShowString(60,90,"ATOM@feng fan tec");
	LCD_ShowString(60,110,"2010/6/11");	
			 
	while(SPI_Flash_ReadID()!=FLASH_ID)//检测不到W25X16
	{	   
		i=SPI_Flash_ReadID();
		printf("ID:%d",i);
		LCD_ShowString(60,130,"W25X16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"   Please Check!    ");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
	LCD_ShowString(60,130,"W25X16 Ready!");
	//显示提示信息
	LCD_ShowString(60,150,"KEY0:Write KEY2:Read");

	POINT_COLOR=BLUE;//设置字体为蓝色	  
	while(1)
	{
		key=KEY_Scan();
		if(key==1)//KEY0按下,写入SPI FLASH
		{
			LCD_Fill(0,170,239,319,WHITE);//清除半屏    
 			LCD_ShowString(60,170,"Start Write W25X16....");
			SPI_Flash_Write((u8*)TEXT_Buffer,1000,SIZE);//从1000字节处开始,写入SIZE长度的数据
			LCD_ShowString(60,170,"W25X16 Write Finished!");//提示传送完成
		}
		if(key==3)//WK_UP按下,读取写入的字符传字符串并显示
		{
 			LCD_ShowString(60,170,"Start Read W25X16.... ");
			SPI_Flash_Read(datatemp,1000,SIZE);//从1000地址处开始,读出SIZE个字节
			LCD_ShowString(60,170,"The Data Readed Is:  ");//提示传送完成
			LCD_ShowString(60,190,datatemp);//显示读到的字符串
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}






















