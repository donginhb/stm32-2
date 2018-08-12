#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "flash.h"	


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com 出品  ********/

//STM32开发板
//SPI 实验  

 				 	
//要写入到W25Q16的字符串数组
const u8 TEXT_Buffer[]={"STM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)
	
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;


 int main(void)
 {	 
   u8 key;
	 u16 i=0;

 
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	 
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," Test SPI W25Q16 ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  嵌入式开发网   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	KEY_Init();	 	
	SPI_Flash_Init();  		//SPI FLASH 初始化 


	 
	while(SPI_Flash_ReadID()!=W25Q16)							//检测不到W25Q16
	{
		Gui_DrawFont_GBK16(0,80,RED,GRAY0,"25Q16 Failed! ");
		delay_ms(500);
		Gui_DrawFont_GBK16(0,80,RED,GRAY0,"Please Check! ");
		delay_ms(500);
		LED=!LED;//DS0闪烁
	}
	Gui_DrawFont_GBK16(0,86,RED,GRAY0,"  25Q16 Ready!");
	
	FLASH_SIZE=2*1024*1024;	//FLASH 大小为8M字节
  		
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==1)//KEY_UP按下,写入W25Q16
		{
			Lcd_Clear(GRAY0);//清屏//清除半屏    
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," Write W25Q16....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//从倒数第100个地址处开始,写入SIZE长度的数据
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," Write Finished!");	//提示传送完成
			
			
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Read W25Q16.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//从倒数第100个地址处开始,读出SIZE个字节
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"The Data Readed Is:  ");	//提示传送完成
			Gui_DrawFont_GBK16(0,100,RED,GRAY0,datatemp);					//显示读到的字符串			
			
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



