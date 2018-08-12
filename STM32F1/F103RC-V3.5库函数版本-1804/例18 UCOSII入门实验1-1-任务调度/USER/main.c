#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "includes.h"

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com       ********/

//UCOSIIʵ��1-�������  
	 

/////////////////////////UCOSII�����ջ����///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//���������ջ�ռ�	
OS_STK START_TASK_STK[START_STK_SIZE];
//�������ӿ�
void start_task(void *pdata);	
 			   
//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			7 
//���������ջ��С
#define LED1_STK_SIZE  		    		64
//���������ջ�ռ�	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//�������ӿ�
void led1_task(void *pdata);


//LED2����
//�����������ȼ�
#define LED2_TASK_PRIO       			6 
//���������ջ��С
#define LED2_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//�������ӿ�
void led2_task(void *pdata);

	
 int main(void)
 {
	delay_init();	     //��ʱ��ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	
  uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600	 
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 UCOS ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("Ƕ��ʽ������\r\n");             //�������
	printf("mcudev.taobao.com\r\n");             //������� 
	 
	 
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();
	 
 }

 
	  
//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);						   
 	OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);	 				   
	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}

//LED1����
void led1_task(void *pdata)
{	 	
	while(1)
	{

		delay_ms(1000);
		
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," UCOS Task1 Run");	
		
		printf("UCOS  ����1 ����\r\n");             //�������
		printf("Ƕ��ʽ������\r\n");             //�������
		printf("mcudev.taobao.com\r\n");             //�������
		printf("\r\n");             //�������
	};
}

//LED2����
void led2_task(void *pdata)
{	  
	while(1)
	{
		LED=0;
		delay_ms(300);
		LED=1;
		delay_ms(300);
		
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," UCOS Task2 Run");	 
		
		printf("UCOS  ����2 ����\r\n");             //�������
		printf("Ƕ��ʽ������\r\n");             //�������
		printf("mcudev.taobao.com\r\n");             //�������
		printf("\r\n");             //�������
		
	};
}


