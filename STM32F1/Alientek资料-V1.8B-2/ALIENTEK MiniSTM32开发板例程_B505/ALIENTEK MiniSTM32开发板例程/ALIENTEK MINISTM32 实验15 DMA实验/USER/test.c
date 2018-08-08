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
//Mini STM32开发板范例代码15
//DMA 实验
//正点原子@ALIENTEK
//技术论坛:www.openedv.com

u8 SendBuff[5200];
const u8 TEXT_TO_SEND[]={"ALIENTEK MiniSTM32 DMA 串口实验"};	 
int main(void)
{		
	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;//进度
			   
  	Stm32_Clock_Init(9);//系统时钟设置
	delay_init(72);		//延时初始化
	uart_init(72,9600); //串口1初始化   
	LED_Init();
	KEY_Init();	
	LCD_Init(); 
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,5200);//DMA1通道4,外设为串口1,存储器为SendBuff,长度5200.

 	POINT_COLOR=RED;//设置字体为蓝色	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"DMA USART TEST");	
	LCD_ShowString(60,90,"ATOM@ALIENTEK");
	LCD_ShowString(60,110,"2010/12/30");
	//显示提示信息
	LCD_ShowString(60,130,"Press KEY0 To Start!");

	j=sizeof(TEXT_TO_SEND);	   
	for(i=0;i<5200;i++)//填充ASCII字符集数据
    {
		if(t>=j)//加入换行符
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}else//复制TEXT_TO_SEND语句
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}   	   
    }		 
	POINT_COLOR=BLUE;//设置字体为蓝色	  
	i=0;
	while(1)
	{
		t=KEY_Scan();
		if(t==1)//KEY0按下
		{
			LCD_ShowString(60,150,"Start Transimit....");
			LCD_ShowString(60,170,"   %");//显示百分号
			printf("\n\nDMA DATA:\n"); 	    
		    USART1->CR3=1<<7;           //使能串口1的DMA发送       
			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	  
		    //等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
		    while(1)
		    {
				if(DMA1->ISR&(1<<13))//等待通道4传输完成
				{
					DMA1->IFCR|=1<<13;//清除通道4传输完成标志
					break; 
		        }
				pro=DMA1_Channel4->CNDTR;//得到当前还剩余多少个数据
				pro=1-pro/5200;//得到百分比	  
				pro*=100;      //扩大100倍
				LCD_ShowNum(60,170,pro,3,16);	  
		    }			    
			LCD_ShowNum(60,170,100,3,16);//显示100%	  
			LCD_ShowString(60,150,"Transimit Finished!");//提示传送完成
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






















