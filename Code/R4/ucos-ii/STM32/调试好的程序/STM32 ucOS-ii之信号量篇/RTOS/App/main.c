#include "includes.h"

static OS_STK   TaskStartStk[TASK_START_STK_SIZE];	// ������ʼ�����ջ��С
static OS_STK   Task1Stk[TASK1_STK_SIZE];			// ���������ջ��С
static OS_STK   Task2Stk[TASK2_STK_SIZE];



static void TaskStart(void *p_arg);
static void Task1(void *p_arg);
static void Task2(void *p_arg);


void Delay(vu32 nCount); 
void Delayms (vu32 m);

OS_EVENT *mutex;
OS_EVENT *key_Sem;

u8 m; 
int main(void)
{
	INT8U err;
    OSInit();	 //��ʼ�� uC/OS-II 
	mutex=OSMutexCreate(3,&err);	// ���������ź���
	key_Sem = OSSemCreate(0);  	    // �����ź���  ��ʼֵΪ0 
    OSTaskCreate(TaskStart,(void*)0,&TaskStartStk[TASK_START_STK_SIZE-1],1); // ������ʼ���񣬸���������ȼ�1 
    OSStart();					   //��ʼ������
	D1_H;D2_H;D3_H;D4_H;D5_H;D6_H;D7_H;D1_H;D8_H;D9_H;D10_H;D11_H;D12_H;D13_H;D14_H;D15_H;D16_H;D18_H;
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
   while(1){
 		    
		    D1_L;
            Delayms(100);            
			D1_H;
			m++;
			if(m>=3)  
			{
				m=0;
			    OSSemPost(key_Sem);		 // �ͷ��ź���
			}          
			
			OSTimeDlyHMSM(0,0,1,0);
     
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
		
		 OSSemPend(key_Sem,0,&err);  // �ȴ��ź������ͷ�
         D2_L; 
         Delayms(100);
		 D2_H; 
		 //OSSemPost(key_Sem);		 // �ͷ��ź���
		 OSTimeDlyHMSM(0,0,1,0);
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

