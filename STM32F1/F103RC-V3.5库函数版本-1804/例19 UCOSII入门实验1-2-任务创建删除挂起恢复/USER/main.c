#include "led.h"

#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "includes.h" 	 

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103���İ�����
//�⺯���汾����
/************** Ƕ��ʽ������  **************/
/********** mcudev.taobao.com       ********/

//UCOSIIʵ��2-2-���񴴽���ɾ�������𣬻ָ� 
 
 
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
 			   
//LED����
//�����������ȼ�
#define LED_TASK_PRIO       			7 
//���������ջ��С
#define LED_STK_SIZE  		    		64
//���������ջ�ռ�	
OS_STK LED_TASK_STK[LED_STK_SIZE];
//�������ӿ�
void led_task(void *pdata);


//����������
//�����������ȼ�
#define BEEP_TASK_PRIO       			5 
//���������ջ��С
#define BEEP_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];
//�������ӿ�
void beep_task(void *pdata);


//����ɨ������
//�����������ȼ�
#define KEY_TASK_PRIO       			3 
//���������ջ��С
#define KEY_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//�������ӿ�
void key_task(void *pdata);
			
 int main(void)
 {	 
  
 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
 
	KEY_Init();				//������ʼ��
	Lcd_Init();	 //1.44��Һ����--��ʼ������
	Lcd_Clear(GRAY0);//����
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"    STM32 UCOS   ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  Ƕ��ʽ������  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("Ƕ��ʽ������\r\n");             //�������
	printf("mcudev.taobao.com\r\n");             //������� 	 
	 
	 
	 
	 
	OSInit();  	 			//��ʼ��UCOSII		 			  
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
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);						    				   
 	//OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);	 				   				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}	  
//LED����
void led_task(void *pdata)
{   
	while(1)
	{  
	      LED=0;//LED��������������
	   		delay_ms(500);
	}									 
}	   

//����������
void beep_task(void *pdata)
{
	while(1)
	{  	
	   if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ) //�ж��Ƿ���ɾ������
		 {
		 OSTaskDel(OS_PRIO_SELF);						   //ɾ��������TaskLed
		 }
		 
	   delay_ms(60);
    	 
		 delay_ms(940);
	}									 
}

//����ɨ������
void key_task(void *pdata)
{	
	u8 key;		    						 
	while(1)
	{
		key=KEY_Scan(0);
		
		if(key==0)
		{
			  LED=1;//LED�������������
			
		    OSTaskSuspend(LED_TASK_PRIO);//����LED����LEDֹͣ��˸
			
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," LED Task Stop");	
		
				printf("LED Task ����\r\n");             //�������
				printf("Ƕ��ʽ������\r\n");             //�������
				printf("mcudev.taobao.com\r\n");             //�������
				printf("\r\n");             //�������
			
		}
		else 
		{
		    OSTaskResume(LED_TASK_PRIO);	//�ָ�LED����LED�ָ���˸
			
				Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," LED Task Run  ");	
		
				printf("LED Task ����\r\n");             //�������
				printf("Ƕ��ʽ������\r\n");             //�������
				printf("mcudev.taobao.com\r\n");             //�������
				printf("\r\n");             //�������
			
			
		}
//		else if (key==KEY_UP)
//		{
//		  OSTaskDelReq(BEEP_TASK_PRIO);	//����ɾ��BEEP������������˯�ߣ��޷��ָ�
//		}
//		else if(key==KEY_DOWN)
//		{
//		 OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);//���´�������beep	 				   				   
//		}   
 		delay_ms(10);
	}
}


