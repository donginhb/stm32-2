#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "adc.h"


#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com  ********/

//ADC ʵ��  

uint8_t   DIS_Buffer[64];//��ʾ�ַ���λ�뻺����

u16 adcx;
float temp;

 int main(void)
 {	 

	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
		 	
 	Adc_Init();		  		//ADC��ʼ��

	Lcd_Init();	 //1.44��Һ����--��ʼ������
	
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 ADC     ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	//��ʾ��ʾ��Ϣ

	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"ADC_VAL:");	      
	Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"ADC_VOL:0.000V");
	 
	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		
		sprintf(DIS_Buffer,"0x %x",adcx);             //��ʽ���ַ���
		Gui_DrawFont_GBK16(0+64,80,BLUE,GRAY0,DIS_Buffer);//��ʾADC��ֵ
		
		printf("ADCת������ֵ��0x %x\r\n",adcx);             //�������
		
		temp=(float)adcx*(3.3/4096);
		
		sprintf(DIS_Buffer,"%06.3f V",temp);             //��ʽ���ַ���
		
		Gui_DrawFont_GBK16(0+64,96,BLUE,GRAY0,DIS_Buffer);//��ʾ��ѹֵ
		
    printf("ADC��⵽�ĵ�ѹֵ��%06.3f V \r\n",temp);             //�������
		
		LED=!LED;
		delay_ms(250);	
		
	}
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 

