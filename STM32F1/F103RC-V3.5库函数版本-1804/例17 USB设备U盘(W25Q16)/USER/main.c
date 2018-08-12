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

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com      ********/

//USB������ ʵ��  


//����USB ����/����
//enable:0,�Ͽ�
//       1,��������	   


void usb_port_set(u8 enable)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //ʹ��PORTAʱ��	   	 
	if(enable)_SetCNTR(_GetCNTR()&(~(1<<1)));//�˳��ϵ�ģʽ
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  // �ϵ�ģʽ
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

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	
	KEY_Init();	 	//������ʼ��
	 
	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0," STM32 USB DISK  ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("Ƕ��ʽ������\r\n");             //�������
	printf("mcudev.taobao.com\r\n");             //�������	
	 
	 
 	SPI_Flash_Init();  		//SPI FLASH ��ʼ�� 
		

	if(SPI_FLASH_TYPE!=W25Q16)
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"W25Q16 Error!");	//���SD������
	else //SPI FLASH ����
	{   															  
 	   	Mass_Memory_Size[0]=1024*1024*2;//ǰ2M�ֽ�
	    Mass_Block_Size[0] =512;        //512���ֽ�.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
		  Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"SPI FLASH Size:2048KB");	 
	}
	
	
	delay_ms(800);
	
 	usb_port_set(0); 	//USB�ȶϿ�
	
	delay_ms(300);
	
  usb_port_set(1);	//USB�ٴ�����	   
	
 	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Connecting...");//��ʾSD���Ѿ�׼����	 
   	//USB����
 	USB_Interrupts_Config(); 
	
 	Set_USBClock();
	
 	USB_Init();
	
	delay_ms(1800);	

	
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			Lcd_Clear(GRAY0);//����			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Writing...");//��ʾUSB����д������	 
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}	 										  
			if(USB_STATUS_REG&0x04)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Write Err ");//��ʾд�����
			else 
				Lcd_Clear(GRAY0);//����		  
			if(USB_STATUS_REG&0x08)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Read  Err ");//��ʾ��������
			else 
				Lcd_Clear(GRAY0);//����	  
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED)
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else 
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		
		tct++;
		
		if(tct==200)
		{
			tct=0;
			LED=!LED;//��ʾϵͳ������
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
	};  										    			    
}

