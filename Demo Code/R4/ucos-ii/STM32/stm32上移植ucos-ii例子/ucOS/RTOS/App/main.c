#include "includes.h"


static OS_STK   TaskStartStk[TASK_START_STK_SIZE];
static OS_STK   TaskLed1Stk[TASK_LED1_STK_SIZE];
static OS_STK   TaskLed2Stk[TASK_LED2_STK_SIZE];

static void TaskCreate(void *p_arg);
static void TaskLed1(void *p_arg);
static void TaskLed2(void *p_arg);


int main(void)
{
    OSInit();
	 
    OSTaskCreate(TaskCreate,(void*)0,&TaskStartStk[TASK_START_STK_SIZE-1],TASK_START_PRIO);
    OSStart();
}

static void TaskCreate(void *p_arg)
{
    (void)p_arg;
    BSP_Init();
   
    #if (OS_TASK_STAT_EN > 0)
     OSStatInit();
    #endif
    OSTaskCreate(TaskLed1,(void*)0,&TaskLed1Stk[TASK_LED1_STK_SIZE-1],TASK_LED1_PRIO);
    OSTaskCreate(TaskLed2,(void*)0,&TaskLed2Stk[TASK_LED2_STK_SIZE-1],TASK_LED2_PRIO);
    while(1)
    {
       OSTaskSuspend(OS_PRIO_SELF);
    }
    
}


static void TaskLed1(void *p_arg)
{
    
    (void)p_arg;
 
   
  while(1){

 
			GPIO_SetBits(GPIOA,GPIO_Pin_8);
			GPIO_SetBits(GPIOA,GPIO_Pin_14);
            OSTimeDlyHMSM(0, 0, 0, 200);

            
			GPIO_ResetBits(GPIOA,GPIO_Pin_8);
			GPIO_ResetBits(GPIOA,GPIO_Pin_14);
            OSTimeDlyHMSM(0, 0, 0, 500);
     
 }
}

static void TaskLed2(void *p_arg)
{
    (void)p_arg;
    while(1)
    {
         GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8))); //根据使用的引脚修改
         OSTimeDlyHMSM(0,0,2,0);
     }
}
