#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "flash.h"	


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/

//STM32������
//SPI ʵ��  

 				 	
//Ҫд�뵽W25Q16���ַ�������
const u8 TEXT_Buffer[]={"STM32 SPI TEST"};
#define SIZE sizeof(TEXT_Buffer)
	
	u8 datatemp[SIZE];
	u32 FLASH_SIZE;


 int main(void)
 {	 
   u8 key;
	 u16 i=0;

 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," Test SPI W25Q16 ");
  Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"  Ƕ��ʽ������   ");	 
	Gui_DrawFont_GBK16(0,64,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	KEY_Init();	 	
	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 


	 
	while(SPI_Flash_ReadID()!=W25Q16)							//��ⲻ��W25Q16
	{
		Gui_DrawFont_GBK16(0,80,RED,GRAY0,"25Q16 Failed! ");
		delay_ms(500);
		Gui_DrawFont_GBK16(0,80,RED,GRAY0,"Please Check! ");
		delay_ms(500);
		LED=!LED;//DS0��˸
	}
	Gui_DrawFont_GBK16(0,86,RED,GRAY0,"  25Q16 Ready!");
	
	FLASH_SIZE=2*1024*1024;	//FLASH ��СΪ8M�ֽ�
  		
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==1)//KEY_UP����,д��W25Q16
		{
			Lcd_Clear(GRAY0);//����//�������    
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," Write W25Q16....");
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);		//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," Write Finished!");	//��ʾ�������
			
			
 			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"Read W25Q16.... ");
			SPI_Flash_Read(datatemp,FLASH_SIZE-100,SIZE);				//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
			Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"The Data Readed Is:  ");	//��ʾ�������
			Gui_DrawFont_GBK16(0,100,RED,GRAY0,datatemp);					//��ʾ�������ַ���			
			
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



