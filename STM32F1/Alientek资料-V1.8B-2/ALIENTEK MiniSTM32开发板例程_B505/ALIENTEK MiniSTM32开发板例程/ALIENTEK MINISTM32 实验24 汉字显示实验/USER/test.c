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
#include "touch.h"
#include "24l01.h"
#include "mmc_sd.h"
#include "remote.h"
#include "ds18b20.h"
#include "mouse.h"
#include "text.h"
#include "fat.h"
#include "fontupd.h"
//Mini STM32开发板范例代码24
//汉字显示 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
				
int main(void)
{		 
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk码
	u8 key,t;			  
	  		 	  
	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化  	  
	LCD_Init();			//初始化液晶		  
	KEY_Init();			//按键初始化
	LED_Init();         //LED初始化	
	SPI_Flash_Init();	//SPI FLASH初始化 
			 
	if(Font_Init())//字库不存在,则更新字库
	{	
UPD:
		POINT_COLOR=RED;      
		LCD_Clear(WHITE);
		LCD_ShowString(60,50,"Mini STM32");	
		LCD_ShowString(60,70,"Font Updating..."); 	 	 
		//字体更新 
		SD_Init();		 //初始化SD卡   	 	 			   
	 	while(FAT_Init())//FAT 错误
		{
			LCD_ShowString(60,90,"FAT SYS ERROR");  
			i= SD_Init();
			if(i)//SD卡初始化 
			{						  
				LCD_ShowString(60,110,"SD_CARD ERROR");
			}	  
			delay_ms(500);
			LCD_Fill(60,90,240,126,WHITE);//清除显示			  
			delay_ms(500);
			LED0=!LED0;	   
		}	 
		LCD_Fill(60,90,240,126,WHITE);//清除显示			  
	 	while(Update_Font()!=0)//字体更新出错
		{						  
			LCD_ShowString(60,90,"SYSTEM FILE LOST");		  
			delay_ms(500);    
			LCD_ShowString(60,90,"Please Check....");
			delay_ms(500);    
			LED0=!LED0;	
		};			 
		LCD_Clear(WHITE);
	}  
	POINT_COLOR=RED;      
	Show_Str(60,50,"Mini STM32开发板",16,0);				    	 
	Show_Str(60,70,"GBK字库测试程序",16,0);				    	 
	Show_Str(60,90,"正点原子@ALIENTEK",16,0);				    	 
	Show_Str(60,110,"2011年1月1日",16,0);
	Show_Str(60,130,"按KEY0,更新字库",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,"内码高字节:",16,0);				    	 
	Show_Str(60,170,"内码低字节:",16,0);				    	 
	Show_Str(60,190,"对应汉字为:",16,0);			 
	Show_Str(60,210,"汉字计数器:",16,0);			 
	while(1) //遍历GBK子库
	{	 
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//显示内码高字节    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//显示内码低字节	 
				LCD_ShowNum(148,210,fontcnt,5,16);//显示内码低字节	 
			 	fontx[1]=j;
				Show_Font(148,190,fontx,16,0);	  
				t=200;
				while(t--)//延时,同时扫描按键
				{
					delay_ms(1);
					key=KEY_Scan();
					if(key==1)goto UPD;
				}
				LED0=!LED0;
			}   
		}			 		   
	}
}


				 






