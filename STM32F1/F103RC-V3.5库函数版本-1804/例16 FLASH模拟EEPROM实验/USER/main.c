#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "stmflash.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com      ********/

//FLASHģ��EEPROM ʵ��  


//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"mcudev.taobao.com"};
#define SIZE sizeof(TEXT_Buffer)	 			  	//���鳤��
#define FLASH_SAVE_ADDR  0X08070000 				//����FLASH �����ַ(����Ϊż��)

 int main(void)
 {	 
	u8 key;
	u16 i=0;
	u8 datatemp[SIZE];

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	
	KEY_Init();	 		 //��ʼ��KEY
		
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"  STM32 EEProm   ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("Ƕ��ʽ������\r\n");             //�������
	printf("mcudev.taobao.com\r\n");             //�������
	 
	//��ʾ��ʾ��Ϣ

	//FLASH_SetLatency(FLASH_ACR_LATENCY_2);	  
	while(1)
	{
		key=KEY_Scan(0);
		if(key==1)//WK_UP����,д��STM32 FLASH
		{
			key=0;//�����ֵ
			
			
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Write FLASH....");
			printf("Start Write FLASH....\r\n"); 	
			STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)TEXT_Buffer,SIZE);
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"FLASH Write Finished!");//��ʾ�������
			
			printf("FLASH Write Finished!\r\n"); 	

 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Start Read FLASH.... ");
			printf("Start Read FLASH.... \r\n"); 	
			
			STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)datatemp,SIZE);
			
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"The Data Readed Is:  ");//��ʾ�������
			
			printf("The Data Readed Is:   \r\n"); 	
			Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,datatemp);//��ʾ�������ַ���
			printf("mcudev.taobao.com\r\n");             //�������
			printf("\r\n \r\n");             //�������
			
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED=!LED;//��ʾϵͳ��������	
			i=0;
		}		   
	}   	   
}


