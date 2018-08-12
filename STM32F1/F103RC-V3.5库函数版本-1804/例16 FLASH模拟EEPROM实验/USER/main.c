#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "stmflash.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com      ********/

//FLASH模拟EEPROM 实验  


//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer[]={"mcudev.taobao.com"};
#define SIZE sizeof(TEXT_Buffer)	 			  	//数组长度
#define FLASH_SAVE_ADDR  0X08070000 				//设置FLASH 保存地址(必须为偶数)

 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	
	KEY_Init();	 		 //初始化KEY
		
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"  STM32 EEProm   ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("嵌入式开发网\r\n");             //串口输出
	printf("mcudev.taobao.com\r\n");             //串口输出
	 
	//显示提示信息

	//FLASH_SetLatency(FLASH_ACR_LATENCY_2);	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==1)//WK_UP按下,写入STM32 FLASH
		{
			key=0;//清除键值
			
			
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Write FLASH....");
			printf("Start Write FLASH....\r\n"); 	
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"FLASH Write Finished!");//提示传送完成
			
			printf("FLASH Write Finished!\r\n"); 	

 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Read FLASH.... ");
			printf("Start Read FLASH.... \r\n"); 	
			
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"The Data Readed Is:  ");//提示传送完成
			
			printf("The Data Readed Is:   \r\n"); 	
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,datatemp);//显示读到的字符串
			printf("mcudev.taobao.com\r\n");             //串口输出
			printf("\r\n \r\n");             //串口输出
			
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED=!LED;//提示系统正在运行	
			i=0;
		}		   
	}   	   
}


