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
//Mini STM32�����巶������24
//������ʾ ʵ��
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
				
int main(void)
{		 
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk��
	u8 key,t;			  
	  		 	  
	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��  	  
	LCD_Init();			//��ʼ��Һ��		  
	KEY_Init();			//������ʼ��
	LED_Init();         //LED��ʼ��	
	SPI_Flash_Init();	//SPI FLASH��ʼ�� 
			 
	if(Font_Init())//�ֿⲻ����,������ֿ�
	{	
UPD:
		POINT_COLOR=RED;      
		LCD_Clear(WHITE);
		LCD_ShowString(60,50,"Mini STM32");	
		LCD_ShowString(60,70,"Font Updating..."); 	 	 
		//������� 
		SD_Init();		 //��ʼ��SD��   	 	 			   
	 	while(FAT_Init())//FAT ����
		{
			LCD_ShowString(60,90,"FAT SYS ERROR");  
			i= SD_Init();
			if(i)//SD����ʼ�� 
			{						  
				LCD_ShowString(60,110,"SD_CARD ERROR");
			}	  
			delay_ms(500);
			LCD_Fill(60,90,240,126,WHITE);//�����ʾ			  
			delay_ms(500);
			LED0=!LED0;	   
		}	 
		LCD_Fill(60,90,240,126,WHITE);//�����ʾ			  
	 	while(Update_Font()!=0)//������³���
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
	Show_Str(60,50,"Mini STM32������",16,0);				    	 
	Show_Str(60,70,"GBK�ֿ���Գ���",16,0);				    	 
	Show_Str(60,90,"����ԭ��@ALIENTEK",16,0);				    	 
	Show_Str(60,110,"2011��1��1��",16,0);
	Show_Str(60,130,"��KEY0,�����ֿ�",16,0);
 	POINT_COLOR=BLUE;  
	Show_Str(60,150,"������ֽ�:",16,0);				    	 
	Show_Str(60,170,"������ֽ�:",16,0);				    	 
	Show_Str(60,190,"��Ӧ����Ϊ:",16,0);			 
	Show_Str(60,210,"���ּ�����:",16,0);			 
	while(1) //����GBK�ӿ�
	{	 
		fontcnt=0;
		for(i=0x81;i<0xff;i++)
		{		
			fontx[0]=i;
			LCD_ShowNum(148,150,i,3,16);//��ʾ������ֽ�    
			for(j=0x40;j<0xfe;j++)
			{
				if(j==0x7f)continue;
				fontcnt++;
				LCD_ShowNum(148,170,j,3,16);//��ʾ������ֽ�	 
				LCD_ShowNum(148,210,fontcnt,5,16);//��ʾ������ֽ�	 
			 	fontx[1]=j;
				Show_Font(148,190,fontx,16,0);	  
				t=200;
				while(t--)//��ʱ,ͬʱɨ�谴��
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


				 






