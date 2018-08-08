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
//Mini STM32�����巶������17
//SPI ʵ��
//


//Ҫд�뵽W25X16���ַ�������
const u8 TEXT_Buffer[]={"MiniSTM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)	 
int main(void)
{		
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];
			   
  	Stm32_Clock_Init(9);//ϵͳʱ������
	delay_init(72);		//��ʱ��ʼ��
	uart_init(72,9600); //����1��ʼ��   
	LED_Init();	   		//LED��ʼ��
	KEY_Init();	   		//������ʼ��
	LCD_Init();    		//TFTLCDҺ����ʼ��
	SPI_Flash_Init();   //SPI FLASH ��ʼ�� 


 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(60,50,"Mini STM32");	
	LCD_ShowString(60,70,"SPI TEST");	
	LCD_ShowString(60,90,"ATOM@feng fan tec");
	LCD_ShowString(60,110,"2010/6/11");	
			 
	while(SPI_Flash_ReadID()!=FLASH_ID)//��ⲻ��W25X16
	{	   
		i=SPI_Flash_ReadID();
		printf("ID:%d",i);
		LCD_ShowString(60,130,"W25X16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(60,130,"   Please Check!    ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	LCD_ShowString(60,130,"W25X16 Ready!");
	//��ʾ��ʾ��Ϣ
	LCD_ShowString(60,150,"KEY0:Write KEY2:Read");

	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	while(1)
	{
		key=KEY_Scan();
		if(key==1)//KEY0����,д��SPI FLASH
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(60,170,"Start Write W25X16....");
			SPI_Flash_Write((u8*)TEXT_Buffer,1000,SIZE);//��1000�ֽڴ���ʼ,д��SIZE���ȵ�����
			LCD_ShowString(60,170,"W25X16 Write Finished!");//��ʾ�������
		}
		if(key==3)//WK_UP����,��ȡд����ַ����ַ�������ʾ
		{
 			LCD_ShowString(60,170,"Start Read W25X16.... ");
			SPI_Flash_Read(datatemp,1000,SIZE);//��1000��ַ����ʼ,����SIZE���ֽ�
			LCD_ShowString(60,170,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(60,190,datatemp);//��ʾ�������ַ���
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}






















