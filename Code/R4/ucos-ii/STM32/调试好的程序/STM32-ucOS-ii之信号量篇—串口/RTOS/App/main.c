#include "includes.h"

static OS_STK   TaskStartStk[TASK_START_STK_SIZE];	// ������ʼ�����ջ��С
static OS_STK   Task1Stk[TASK1_STK_SIZE];			// ���������ջ��С
static OS_STK   Task2Stk[TASK2_STK_SIZE];
static OS_STK   Task3Stk[TASK3_STK_SIZE];
static OS_STK   Task4Stk[TASK4_STK_SIZE];

static void TaskStart(void *p_arg);
static void Task1(void *p_arg);
static void Task2(void *p_arg);
static void Task3(void *p_arg);
static void Task4(void *p_arg);
void Delay(vu32 nCount); 
void Delayms (vu32 m);
OS_EVENT *mutex;
OS_EVENT *key_Sem1;
OS_EVENT *key_Sem2;
int main(void)
{
	INT8U err;
    OSInit();	 //��ʼ�� uC/OS-II 
	mutex=OSMutexCreate(3,&err);	// ���������ź���
	key_Sem1 = OSSemCreate(0);  	    // �����ź���  ��ʼֵΪ0 
	key_Sem2 = OSSemCreate(0);  	    // �����ź���  ��ʼֵΪ0 
    OSTaskCreate(TaskStart,(void*)0,&TaskStartStk[TASK_START_STK_SIZE-1],1); // ������ʼ���񣬸���������ȼ�1 
    OSStart();					   //��ʼ������
	
}

/*
********************************************************************************
**��ʼ�������ȼ�1
********************************************************************************
*/
static void TaskStart(void *p_arg)
{
    (void)p_arg;
    BSP_Init();
   
#if (OS_TASK_STAT_EN > 0)
     OSStatInit();
#endif
    OSTaskCreate(Task1,(void*)0,&Task1Stk[TASK1_STK_SIZE-1],2);  // ����ʼ�����д���Task1�����ȼ�2 
    OSTaskCreate(Task2,(void*)0,&Task2Stk[TASK2_STK_SIZE-1],4);  // ����ʼ�����д���Task2�����ȼ�4
	OSTaskCreate(Task3,(void*)0,&Task3Stk[TASK3_STK_SIZE-1],5);  // ����ʼ�����д���Task1�����ȼ�5 
    OSTaskCreate(Task4,(void*)0,&Task4Stk[TASK4_STK_SIZE-1],6);  // ����ʼ�����д���Task2�����ȼ�6
	 
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;

    while(1)
    {
	   OSTimeDly(10);
       OSTaskSuspend(OS_PRIO_SELF);	  // ��������
    }    
}
/*
********************************************************************************
**����1�����ȼ�2
********************************************************************************
*/
static void Task1(void *p_arg)
{     
   while(1)
    {
		INT8U err;
 		OSTimeDlyHMSM(0,0,1,0);
		OSSemPend(key_Sem1,0,&err);  // �ȴ��ź������ͷ�
		 OSSemPend(key_Sem2,0,&err);  // �ȴ��ź������ͷ�
		USART_SendData(USART1, 0x01);
		USART_SendData(USART1, 0x01);        
			    
     }
}
/*
********************************************************************************
**����2�����ȼ�3
********************************************************************************
*/
static void Task2(void *p_arg)
{	
	INT8U err;
    while(1)
    {

		 OSTimeDlyHMSM(0,0,1,0);		 
         USART_SendData(USART1, 0x02);
		 USART_SendData(USART1, 0x02);
		 OSSemPost(key_Sem1);		 // �ͷ��ź���
     }
}

/*
********************************************************************************
**����3�����ȼ�4
********************************************************************************
*/
static void Task3(void *p_arg)
{
     INT8U err;
	while(1)
    {	
		 //OSSemPend(key_Sem2,0,&err);  // �ȴ��ź������ͷ�
		 OSTimeDlyHMSM(0,0,1,0);		 
         USART_SendData(USART1, 0x03);
	     USART_SendData(USART1, 0x03);
		 //OSSemPost(key_Sem);		 // �ͷ��ź���

     }
}

/*
********************************************************************************
**����4�����ȼ�5
********************************************************************************
*/
static void Task4(void *p_arg)
{
	 INT8U err;
     while(1)
     {
		OSTimeDlyHMSM(0,0,1,0);
	  	//OSSemPend(key_Sem,0,&err);  // �ȴ��ź������ͷ�	
        USART_SendData(USART1, 0x04);
		USART_SendData(USART1, 0x04);
		OSSemPost(key_Sem2);		 // �ͷ��ź���
		                              
       		
      }
}


/*
********************************************************************************
** �������� �� Delay(vu32 nCount)
** �������� �� ����ʱ����	  i=1;40us��ʱ
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
/* 
 void Delay(vu32 t)
{
  u8 j,k;
   for(k=0;k<t;k++)
      for(j=0;j<255;j++);
}
*/
 void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*
********************************************************************************
** �������� �� void Delayms(vu32 m)
** �������� �� ����ʱ����	 m=1,��ʱ1ms
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
 void Delayms(vu32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}

