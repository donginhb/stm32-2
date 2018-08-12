#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "mmc_sd.h"
#include "ff.h"
#include "flash.h"
#include "exfuns.h"
#include "fattester.h"
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h"	

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com      ********/

//USB读卡器 实验  


//设置USB 连接/断线
//enable:0,断开
//       1,允许连接	   


void usb_port_set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //使能PORTA时钟	   	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//退出断电模式
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // 断电模式
		GPIOA->CRH&=0XFFF00FFF;
		GPIOA->CRH|=0X00033000;
		PAout(12)=0;	    		  
	}
} 



 int main(void)
 {	 
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;

	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	
	KEY_Init();	 	//按键初始化
	 
	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 USB DISK  ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("嵌入式开发网\r\n");             //串口输出
	printf("mcudev.taobao.com\r\n");             //串口输出	
	 
	 
 	SPI_Flash_Init();  		//SPI FLASH 初始化 
		

	if(SPI_FLASH_TYPE!=W25Q16)
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"W25Q16 Error!");	//检测SD卡错误
	else //SPI FLASH 正常
	{   															  
 	   	Mass_Memory_Size[0]=1024*1024*2;//前2M字节
	    Mass_Block_Size[0] =512;        //512个字节.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
		  Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"SPI FLASH Size:2048KB");	 
	}
	
	
	delay_ms(800);
	
 	usb_port_set(0); 	//USB先断开
	
	delay_ms(300);
	
  usb_port_set(1);	//USB再次连接	   
	
 	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Connecting...");//提示SD卡已经准备了	 
   	//USB配置
 	USB_Interrupts_Config(); 
	
 	Set_USBClock();
	
 	USB_Init();
	
	delay_ms(1800);	

	
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
			Lcd_Clear(GRAY0);//清屏			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Writing...");//提示USB正在写入数据	 
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Reading...");//提示USB正在读出数据  		 
			}	 										  
			if(USB_STATUS_REG&0x04)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Write Err ");//提示写入错误
			else 
				Lcd_Clear(GRAY0);//清屏		  
			if(USB_STATUS_REG&0x08)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Read  Err ");//提示读出错误
			else 
				Lcd_Clear(GRAY0);//清屏	  
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Connected    ");//提示USB连接已经建立
			else 
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		
		tct++;
		
		if(tct==200)
		{
			tct=0;
			LED=!LED;//提示系统在运行
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
}

