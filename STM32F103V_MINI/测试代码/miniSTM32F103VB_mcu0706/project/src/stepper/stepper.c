/*-------------------------------------------
*file: setpper.c
*Description: contorl setp motor
*--------------------------------------------*/

#include "includes.h"

#if STEPPER_EN>0

typedef struct {
	SetpperDir Dir;
	SetpperCurMode Wmode;
}StepperMode_t;

static StepperMode_t StepperModeStruct;

void Stepper_SetCur( SetpperCurMode cur_mode );
/*步进电机轮和所带轮直径比例:1:6*/
/*******************************************************************************
* Function Name  : MC_ServoCapPos_NVICInit
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_Stepper_NVICInit( void )
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  /* Enable the STEPPER_TIMER Update Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = STEPPER_IRQChannel ;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =7;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  
}
/*功能开关*/
void MC_StepperFunSw(FunctionalState NewState)
{
	TIM_Cmd(STEPPER_TIMER, NewState);  
}
/*
*20081226  STEPPER_CLK_FRQ_4K2 TB6560 最好
*20090107  STEPPER_CLK_FRQ_10K 最好
*/

#if STEPPER_TB6560_EN>0
#define STEPPER_CLK_FRQ_4K0  (u32)(1000*10/40)
#define STEPPER_CLK_FRQ_4K2  (u32)(1000*10/42)
#define STEPPER_CLK_FRQ_4K5   (u32)(1000*10/45)
#define MC_STEPPER_TIME   (u16)STEPPER_CLK_FRQ_4K2   /*1000/MC_STEPPER_TIME  = us ,*/		
#elif STEPPER_A3979_EN>0
#define STEPPER_CLK_FRQ_10K    (u32)(1000*10/100)
#define MC_STEPPER_TIME   (u16)STEPPER_CLK_FRQ_10K   /*1000/MC_STEPPER_TIME  = us ,*/	
#endif

/*******************************************************************************
* Function Name  : MC_ServoCapPos_TimInit
* Description    : TIM2 init  counter
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MC_Stepper_TimInit( void )
{
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  /* ---------------------------------------------------------------
    STEPPER_TIMER Configuration: generate 4 signals with 4 different delays:
    STEPPER_TIMER = 36 MHz, Prescaler = 35999, STEPPER_TIMER counter clock = 1 MHz   
  --------------------------------------------------------------- */
	 /* Enable STEPPER_TIMER APB1 clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_STEPPER ,  ENABLE);

	TIM_TimeBaseStructure.TIM_Prescaler = 36-1;    //250us
	TIM_TimeBaseStructure.TIM_Period = MC_STEPPER_TIME ;  	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	TIM_TimeBaseInit(STEPPER_TIMER, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(STEPPER_TIMER, ENABLE);	
	TIM_ITConfig(STEPPER_TIMER, TIM_IT_Update, ENABLE);
	
	MC_StepperFunSw( DISABLE);  
  
}
static vu16 StepperNum = 0 ;
void MC_StepperNumClear(void)
{
	MC_StepperFunSw( DISABLE); 
	StepperNum = 0 ;
}
void MC_StepperNumSet( u16 Num)
{
	StepperNum =( u16 ) 2*Num;
	if(StepperModeStruct.Wmode != STEP_CUR_WORK_MODE)
	{
		StepperModeStruct.Wmode = STEP_CUR_WORK_MODE ;
		Stepper_SetCur(STEP_CUR_WORK_MODE);
	}
	
	MC_StepperFunSw( ENABLE);  		
}
/*上次设定是否结束*/
bool MC_StepperNum_IsElapsed(void)
{
	if(StepperNum != 0 )
		return FALSE;
	else
		return TRUE;
}

void  Init_Stepper(void)
{
	#if STEPPER_TB6560_EN>0
		Stepper_InitTB6560( );
	#endif
	
	#if STEPPER_A3979_EN>0
		Stepper_InitA3979( );
	#endif
	
	MC_StepperNumClear();

	StepperModeStruct.Dir = STEP_DIR_CCW ;
	StepperModeStruct.Wmode = STEP_CUR_WEAK_MODE ;
	
	MC_Stepper_NVICInit();
	MC_Stepper_TimInit();
   
}
void Stepper_ModeSet( SetpperCurMode mode , SetpperDir run_dir)
{
	#if STEPPER_TB6560_EN>0
		Stepper_ModeSetTB6560( mode , run_dir );
	#endif
	
	#if STEPPER_A3979_EN>0
		Stepper_ModeSetA3979( mode , run_dir );
	#endif
}
void Stepper_SetCur( SetpperCurMode cur_mode )
{
	
	#if STEPPER_TB6560_EN>0
		Stepper_SetCurTB6560( cur_mode  );
	#endif
	
	#if STEPPER_A3979_EN>0
		Stepper_SetCurA3979( cur_mode );
	#endif
}
static void Stepper_SetDir( SetpperDir run_dir)
{
	
	#if STEPPER_TB6560_EN>0
		Stepper_SetDirTB6560( run_dir  );
	#endif
	
	#if STEPPER_A3979_EN>0
		Stepper_SetDirA3979( run_dir );
	#endif
}

/*******************************************************************************
* Function Name  :StepperFeedPaper 
* Description    : 走纸
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void StepperFeedPaper(u16 Num , SetpperDir Dir)
{

	if(StepperModeStruct.Dir != Dir)
	{
		MC_StepperNumClear();
		StepperModeStruct.Dir = Dir;
		Stepper_SetDir(  Dir );			

	}		
	//if( MC_StepperNum_IsElapsed() == TRUE )	
	{
		MC_StepperNumSet(Num);		
	}
	
}
/*******************************************************************************
* Function Name  :StepperFeedPaper 
* Description    :打印进纸 纸
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void StepperPrintFeedPaper(u16 Num )
{
	StepperFeedPaper( Num , STEP_DIR_CCW );
}
#if 1
#define STEPPER_STEP_NUM 2000
/*******************************************************************************
* Function Name  :API_SetpperForward 
* Description    : 固定步进数SETPPER_SETP_NUM   进纸
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void API_StepperForward(void)
{

	StepperFeedPaper(STEPPER_STEP_NUM , STEP_DIR_CCW );

}
/*******************************************************************************
* Function Name  : API_SetpperBackward
* Description    : 固定步进数2000  退纸
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void API_StepperBackward(void)
{

	StepperFeedPaper(STEPPER_STEP_NUM , STEP_DIR_CW );
		
}

#endif
/*定时捕中断*/
void SetpperBack(void)
{
	
	#if 1
	
	if(StepperNum != 0 )
	{
		StepperNum--;
		
		#if STEPPER_TB6560_EN>0
			GPIO_WriteBit(GPIO_STEP_TB, STEP_TB_CLK_PIN, (BitAction)(1-GPIO_ReadOutputDataBit(GPIO_STEP_TB, STEP_TB_CLK_PIN)));
		#endif
		
		#if STEPPER_A3979_EN>0
			GPIO_WriteBit(GPIO_STEP_A3979_CLK , STEP_A3979_CLK_PIN, (BitAction)(1-GPIO_ReadOutputDataBit(GPIO_STEP_A3979_CLK, STEP_A3979_CLK_PIN)));
		#endif
		
		if(StepperNum == 0)
		{
			MC_StepperFunSw( DISABLE); /*关定时器*/
			#if STEPPER_TB6560_EN>0
			GPIO_ResetBits(GPIO_STEP_TB, STEP_TB_CLK_PIN);  /*置时钟*/
			#endif
			
			#if STEPPER_A3979_EN>0
			GPIO_ResetBits( GPIO_STEP_A3979_CLK , STEP_A3979_CLK_PIN );
			#endif
			Stepper_SetCur( STEP_CUR_WEAK_MODE );
			
		}
	}

	#endif
	
}


/**api  function--dec-------------------------------------------------------------
*1, 进纸
*	1.1 手动--手动测试
	1.2 自动--打印
*2 , 退纸
	2.1 手动
	2.2
*-----------------------------------------------------------------------------*/

/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
bool  StepperTest(void)
{

	#if 1
    static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
    static bool Flag = TRUE;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/	

			Stepper_SetDir( STEP_DIR_CW );
			TaskStatus = TASK_RUN;
			break;			

		case TASK_INIT1:/*初始化--1*/	
			
			Stepper_SetDir( STEP_DIR_CCW);			
			TaskStatus = TASK_RUN;
			
			break;
			
		case TASK_RUN:	
			MC_StepperNumSet(STEPPER_STEP_NUM);	
						
			TaskStatus = TASK_RUN1 ; 
						
			break;
			
		case TASK_RUN1:
			if( MC_StepperNum_IsElapsed() == TRUE )				
			{
				TaskStatus = TASK_RUN2 ; 
				
				TB_Delay_nms(4000);
			}
		
			break;	
			
		case TASK_RUN2:
			if(TB_Delay_IsElapsed() == TRUE)			
			{
					
				LedAutoOnOff(LED2);	
				if(Flag == TRUE)
				{
					TaskStatus = TASK_INIT1 ; 
					Flag = FALSE;
				}
				else
				{
					TaskStatus = TASK_INIT ; 
					Flag = TRUE;
				}
			}
			break;
			
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ; //ack ok !
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_END)
        {	
        	TaskStatus = TASK_INIT ;
		return TRUE;	
		
        }	
#endif	

	return FALSE;/*该任务未执行完*/		

}

#endif //#if SETPPER_EN>0

