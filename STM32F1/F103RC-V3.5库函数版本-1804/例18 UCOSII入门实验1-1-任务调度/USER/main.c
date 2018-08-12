#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "includes.h"

#include "GUI.h"
#include "Lcd_Driver.h"

//STM32F103核心板例程
//库函数版本例程
/************** 嵌入式开发网  **************/
/********** mcudev.taobao.com       ********/

//UCOSII实验1-任务调度  
	 

/////////////////////////UCOSII任务堆栈设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//创建任务堆栈空间	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数接口
void start_task(void *pdata);	
 			   
//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED1_STK_SIZE  		    		64
//创建任务堆栈空间	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数接口
void led1_task(void *pdata);


//LED2任务
//设置任务优先级
#define LED2_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED2_STK_SIZE  					64
//创建任务堆栈空间	
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//任务函数接口
void led2_task(void *pdata);

	
 int main(void)
 {
	delay_init();	     //延时初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	LED_Init();		  	 //初始化与LED连接的硬件接口
	
  uart_init(9600);	 	//串口初始化为9600	 
	Lcd_Init();	 //1.44寸液晶屏--初始化配置
	Lcd_Clear(GRAY0);//清屏
	Gui_DrawFont_GBK16(0,16,RED,GRAY0,"   STM32 UCOS ");
  Gui_DrawFont_GBK16(0,32,BLUE,GRAY0,"  嵌入式开发网  ");	 
	Gui_DrawFont_GBK16(0,48,BLUE,GRAY0,"mcudev.taobao.com "); 
	printf("嵌入式开发网\r\n");             //串口输出
	printf("mcudev.taobao.com\r\n");             //串口输出 
	 
	 
	OSInit();   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();
	 
 }

 
	  
//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);						   
 	OSTaskCreate(led2_task,(void *)0,(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],LED2_TASK_PRIO);	 				   
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED1任务
void led1_task(void *pdata)
{	 	
	while(1)
	{

		delay_ms(1000);
		
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," UCOS Task1 Run");	
		
		printf("UCOS  任务1 运行\r\n");             //串口输出
		printf("嵌入式开发网\r\n");             //串口输出
		printf("mcudev.taobao.com\r\n");             //串口输出
		printf("\r\n");             //串口输出
	};
}

//LED2任务
void led2_task(void *pdata)
{	  
	while(1)
	{
		LED=0;
		delay_ms(300);
		LED=1;
		delay_ms(300);
		
		Gui_DrawFont_GBK16(0,80,BLUE,GRAY0," UCOS Task2 Run");	 
		
		printf("UCOS  任务2 运行\r\n");             //串口输出
		printf("嵌入式开发网\r\n");             //串口输出
		printf("mcudev.taobao.com\r\n");             //串口输出
		printf("\r\n");             //串口输出
		
	};
}


