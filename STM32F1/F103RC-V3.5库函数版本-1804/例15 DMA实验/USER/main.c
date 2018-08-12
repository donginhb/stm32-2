#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "dma.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com  ********/

//DMA 实验  

uint8_t  DIS_Buffer[64];//显示字符区位码缓冲区

u8 SendBuff[5200];
const u8 TEXT_TO_SEND[]={" mcudev.taobao.com \r\n 嵌入式开发网\r\n STM32 DMA 串口实验\r\n "};	

	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;//进度

 int main(void)
 {	 


	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	
 	KEY_Init();				//按键初始化	
		 	
 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,5168);//DMA1通道4,外设为串口1,存储器为SendBuff,长度5168.    

	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 DMA     ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("嵌入式开发网\r\n");             //串口输出
	printf("mcudev.taobao.com\r\n");             //串口输出
	 
	 
	//显示提示信息	
	j=sizeof(TEXT_TO_SEND);	
	
	for(i=0;i<5168;i++)//填充ASCII字符集数据
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
	
	i=0;
		
	while(1)
	{
		t=KEY_Scan(0);
		
		if(t)//KEY0按下
		{
			t=0;//清除键值
			
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Transimit....");
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"   %");//显示百分号
			
			printf("\r\nDMA DATA:\r\n"); 	
			
			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送  
			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！	
			
		    //等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
		    while(1)
		    {
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//判断通道4传输完成
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
					break; 
		        }
				pro=DMA_GetCurrDataCounter(DMA1_Channel4);//得到当前还剩余多少个数据
				pro=1-pro/5168;//得到百分比	  
				pro*=100;      //扩大100倍
				
        sprintf(DIS_Buffer,"  %3.1f",pro);             //格式化字符串			
        Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,DIS_Buffer);//显示百分号						
			
						
		    }
				
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"  100%");//显示百分号//显示100%	  
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Transimit Finished!");//提示传送完成
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
