#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"

#include "usart.h"	 
#include "tsensor.h"

#include "GUI.h"
#include "Lcd_Driver.h"


//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com ��Ʒ  ********/

//�ڲ��¶ȴ����� ʵ��  

uint8_t  DIS_Buffer[64];//��ʾ�ַ���λ�뻺����

	u16 adcx;
	float temp;
 	float temperate;

 int main(void)
 {	 

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	 	
  T_Adc_Init();		  		//ADC��ʼ��

	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"  STM32 TSENSOR  ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	 
	
		//��ʾ��ʾ��Ϣ

	Gui_DrawFont_GBK16(0,80,BLUE,GRAY0,"TEMP_VAL:");	      
	Gui_DrawFont_GBK16(0,96,BLUE,GRAY0,"TEMP_VOL:");
  Gui_DrawFont_GBK16(0,112,BLUE,GRAY0,"TEMP_CVL:");

	while(1)
	{
		adcx=T_Get_Adc_Average(ADC_CH_TEMP,10);
		
		sprintf(DIS_Buffer,"0x%x",adcx);             //��ʽ���ַ���
		Gui_DrawFont_GBK16(0+72,80,BLUE,GRAY0,DIS_Buffer);//��ʾADC��ֵ
		
		printf("Ƕ��ʽ������\r\n");             //�������
		printf("mcudev.taobao.com\r\n");             //�������
		printf("\r\n");             //�������
		printf("ADCת������ֵ��0x %x\r\n",adcx);             //�������
		
		
		temp=(float)adcx*(3.3/4096);
		
		temperate=temp;//�����¶ȴ������ĵ�ѹֵ
		
		sprintf(DIS_Buffer,"%6.3fV",temperate);             //��ʽ���ַ���
		
		Gui_DrawFont_GBK16(0+72,96,BLUE,GRAY0,DIS_Buffer);//��ʾ��ѹֵ
		
    printf("�¶ȴ������ĵ�ѹֵ��%6.3f \r\n",temp);             //�������
										  
		
		temperate=(1.43-temperate)/0.0043+25;		//�������ǰ�¶�ֵ	
		
		sprintf(DIS_Buffer,"%5.2fC",temperate);             //��ʽ���ַ���
		
		Gui_DrawFont_GBK16(0+72,112,BLUE,GRAY0,DIS_Buffer);//��ʾ��ѹֵ
		
    printf("�¶ȴ��������¶�ֵ��%6.2f ��\r\n",temp);             //�������
		
		printf("\r\n");             //�������
		
		LED=!LED;
		delay_ms(250);
		
	}
 }

