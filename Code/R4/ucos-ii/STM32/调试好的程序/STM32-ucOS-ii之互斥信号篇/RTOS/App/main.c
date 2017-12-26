#include "includes.h"

static OS_STK   TaskStartStk[TASK_START_STK_SIZE];	// ������ʼ�����ջ��С
static OS_STK   Task1Stk[TASK1_STK_SIZE];			// ���������ջ��С
static OS_STK   Task2Stk[TASK2_STK_SIZE];
static OS_STK   Task3Stk[TASK3_STK_SIZE];


static void TaskStart(void *p_arg);
static void Task1(void *p_arg);
static void Task2(void *p_arg);
static void Task3(void *p_arg);
void Delayms (vu32 m);

OS_EVENT *mutex;


int main(void)
{
	INT8U err;
    OSInit();	 //��ʼ�� uC/OS-II 
	mutex=OSMutexCreate(2,&err);	// ���������ź��� 	// ����2��Ϊ�̳����ȼ�����
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
     OSStatInit();	 // ��ʼ��ͳ������
#endif
    OSTaskCreate(Task1,(void*)0,&Task1Stk[TASK1_STK_SIZE-1],3);  // ����ʼ�����д���Task1�����ȼ�3 
    OSTaskCreate(Task2,(void*)0,&Task2Stk[TASK2_STK_SIZE-1],4);  // ����ʼ�����д���Task2�����ȼ�4
	OSTaskCreate(Task3,(void*)0,&Task3Stk[TASK3_STK_SIZE-1],5);  // ����ʼ�����д���Task3�����ȼ�5 
   

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
  	INT8U err;
 	while(1)
  	{
 		  OSMutexPend(mutex, 0, &err);
		  D1_L;
          Delayms(100);            
		  D1_H;
          OSTimeDlyHMSM(0,0,1,0);
		  OSMutexPost(mutex);
		
     
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
		 OSMutexPend(mutex, 0, &err);
         D2_L; 
         Delayms(100);
		 D2_H; 
		 OSTimeDlyHMSM(0,0,3,0);		 		
		 OSMutexPost(mutex);
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
		 
		 OSMutexPend(mutex, 0, &err);
         D3_L;
         Delayms(100);  
		 D3_H;
		 OSTimeDlyHMSM(0,0,1,0);
		 OSMutexPost(mutex);
     }
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

