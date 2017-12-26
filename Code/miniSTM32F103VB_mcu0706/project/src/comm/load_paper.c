//file:loadpaper.c

#include "includes.h"

#if LOAD_PAPER_EN>0

#define LOAD_PAPER_TIME_10MS 		 (10*10/(TIM_CCR_VAl_P_MOTOR_SENSOR_SAMPLEING))
#define LOAD_PAPER_TIME_100MS 	 (LOAD_PAPER_TIME_10MS*10)
#define LOAD_PAPER_TIME_1S			 (LOAD_PAPER_TIME_10MS*100)

#define PAPER_SENSOR_SAMPLING_CNT  	(10) /*一次采集传感器采样次数*/

#define TIME_MOTOR_ON_BEFORE_DELAY 		(3* LOAD_PAPER_TIME_1S)/*传感器检测到有用信号，到开启电机延时*/

/* 电机打开转动时间*/
#define TIME_LOAD_MOTOR_ONCE_ON			(10 * LOAD_PAPER_TIME_10MS )  /*收纸马达开启时间*/
#define TIME_LOAD_PAPER_ONCE_DELAY 		(  TIME_LOAD_MOTOR_ONCE_ON  + 1 )	/*收纸延时*/


/*放纸电机打开转动时间*/
#define TIME_UNLOAD_MOTOR_ONCE_ON	  			(20* LOAD_PAPER_TIME_10MS  ) /*放纸马达开启时间*/
#define TIME_UNLOAD_PAPER_ONCE_DELAY   	 		( TIME_UNLOAD_MOTOR_ONCE_ON + 2 )	
#define TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY 	( TIME_UNLOAD_MOTOR_ONCE_ON *5 )  /*放纸监控时间，防止无纸一直放纸状态发生*/

#define TIME_ALWAYS_UNLOAD_PAPER_DELAY_STOP 	(1* LOAD_PAPER_TIME_10MS)	/*连续放纸,期间停止放纸时间 */

#define TIME_AUTO_WATCH_UNLOAD_PAPER_COUNTER  		1	 /*无纸重试放纸次数*/
#define PAPER_MOTOR_SENSOR_SAMPLING_T   	PAPER_SENSOR_SAMPLING_CNT  /*检测纸采样次数间隔10ms采样一次*/

static vu8 PaperMotorSensorSamplingTime = 0 ;
static vu8 LoadPaperSensorSamplingCnt = 0 , UnloadPaperSensorSamplingCnt = 0 ;	/*收放纸传感器规定时间内采样有效次数计数器*/

static vu16 AlwaysUnloadPaperWatchDelay = 0 ;	/*连续放纸,期间停止放纸时间 */
static vu16 UnloadPaperBeforeDelay = 0 ;				/*传感器检测到有用信号，到开启电机延时*/
static vu16 UnloadPaperOnceDelay = 0 ;			/*放纸电机一次打开时间*/
static vu16 AlwaysUnloadPaperStopDelay = 0 ; 	/*连续放纸,期间停止放纸时间 */
static vu16 LoadPaperBeforeDelay = 0 ;				/*传感器检测到有用信号，到开启电机延时*/
static vu16 LoadPaperOnceDelay = 0 ;			/*收纸电机一次打开时间*/

//static volatile bool  ShortPaperFlag = FALSE ;	/*缺纸打印过程中缺纸*/
//static volatile bool  LoadPaperFlag = FALSE ;	/*收纸打印过程中*/

void Init_LoadPaperGpio(void)
{

	  GPIO_InitTypeDef  GPIO_InitStructure;
	 //#####################################
	  /* Configure IO connected to buz *********************/
	  /* Enable GPIO_buz clock */
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LP_MOTOR , ENABLE );
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_LP_SENSOR , ENABLE );
	   
	  GPIO_InitStructure.GPIO_Pin =  LP_MOTOR_PIN | UNLP_MOTOR_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LP_MOTOR;
	  GPIO_Init( GPIO_LP_MOTOR , &GPIO_InitStructure );
	  //****GPIO_LP_MOTOR off**************
  	  GPIO_SetBits( GPIO_LP_MOTOR , LP_MOTOR_PIN );
	  GPIO_SetBits( GPIO_LP_MOTOR , UNLP_MOTOR_PIN );
	  
	  GPIO_InitStructure.GPIO_Pin =  LP_SENSOR_PIN | UNLP_SENSOR_PIN ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_LP_SENSOR ;
	  GPIO_Init( GPIO_LP_SENSOR , &GPIO_InitStructure );
	

}
typedef enum {
	P_MOTOR_ON,
	P_MOTOR_OFF= !P_MOTOR_ON
}PaperMotorOnOff;

/*************************************************
*收放纸马达开关
**************************************************/
#if 1
/*收纸马达*/
void Load_MotorOnOff(PaperMotorOnOff  PMOnOff )
{
	if(PMOnOff != P_MOTOR_OFF)
		GPIO_ResetBits( GPIO_LP_MOTOR , LP_MOTOR_PIN );
	else
		GPIO_SetBits( GPIO_LP_MOTOR , LP_MOTOR_PIN );
}

/*放纸马达*/
void Unload_MotorOnOff(PaperMotorOnOff  PMOnOff )
{
	if(PMOnOff != P_MOTOR_OFF)
		GPIO_ResetBits( GPIO_LP_MOTOR , UNLP_MOTOR_PIN );
	else
		GPIO_SetBits( GPIO_LP_MOTOR , UNLP_MOTOR_PIN );
}
#endif
/*********************************************************
*关于收放纸传感器探头输出信号:
*无纸输出: Low ;    
*有纸输出: High
*********************************************************/
/**Paper_SensorLoad 有纸输出: High,为有效*/
bool Paper_SensorLoad( )
{

	if( GPIO_ReadInputDataBit( GPIO_LP_SENSOR , LP_SENSOR_PIN ) != 0x00)/*收纸传感器*/
		return TRUE ;/*收纸传感检测到有纸，需动作电机收纸*/
	else
		return FALSE;
	
}
/**Paper_SensorUnload 无纸输出: Low ;  有效信号*/
bool Paper_SensorUnload( )
{

	if( GPIO_ReadInputDataBit( GPIO_LP_SENSOR , UNLP_SENSOR_PIN )!= 0x00) /*放纸传感器*/			
		return FALSE ;/*放纸传感器检测到纸不用再放纸了*/
	else
		return TRUE ; /*检测不到纸，需动作放纸电机放纸*/
	
}

/*
*收放纸传感器采集程序
*/

/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 连续放纸监控时间
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_AlwaysUnloadPaperWatchDelay(u16 time)
{
	AlwaysUnloadPaperWatchDelay = time ; //TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY ;
}  

/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay_IsElapsed
* Description    : Check if the delay set by LP_AlwaysUnloadPaperWatchDelay_IsElapsed is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool LP_AlwaysUnloadPaperWatchDelay_IsElapsed(void)
{
	if (AlwaysUnloadPaperWatchDelay != 0)
	{
		return (FALSE);
	}
	else 
	{
		return (TRUE);
	}
} 

/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 放纸之前延时时间
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_UnloadPaperBeforeDelay(u16 time)
{
	UnloadPaperBeforeDelay = time ; //TIME_MOTOR_ON_BEFORE_DELAY ;
}  

/*******************************************************************************
* Function Name  : LP_UnloadPaperDelay_IsElapsed
* Description    : Check if the delay set by LP_UnloadPaperDelay_IsElapsed is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool LP_UnloadPaperBeforeDelay_IsElapsed(void)
{
	if (UnloadPaperBeforeDelay != 0)
	{
		return (FALSE);
	}
	else 
	{
		return (TRUE);
	}
} 

/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 收纸之前延时
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_LoadPaperBeforeDelay(u16 time)
{
	LoadPaperBeforeDelay = time ;  //TIME_MOTOR_ON_BEFORE_DELAY ;
}  

/*******************************************************************************
* Function Name  : LP_UnloadPaperDelay_IsElapsed
* Description    : Check if the delay set by LP_UnloadPaperDelay_IsElapsed is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool LP_LoadPaperBeforeDelay_IsElapsed(void)
{
	if (LoadPaperBeforeDelay != 0)
	{
		return (FALSE);
	}
	else 
	{
		return (TRUE);
	}
} 
/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 收纸时间
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_LoadPaperStartup(void)
{
	LoadPaperOnceDelay = TIME_LOAD_PAPER_ONCE_DELAY ;
}  
/*******************************************************************************
* Function Name  : LP_LoadPaperEnd_IsElapsed
* Description    : 收纸电机一次动作是否结束
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
bool LP_LoadPaperEnd_IsElapsed(void)
{
	if (LoadPaperOnceDelay != 0)
		return (FALSE);	
	else 
		return (TRUE);
	
}
/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 放纸时间
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_UnloadPaperStartup(void)
{
	UnloadPaperOnceDelay = TIME_UNLOAD_PAPER_ONCE_DELAY ;
}  
/*******************************************************************************
* Function Name  : LP_LoadPaperEnd_IsElapsed
* Description    : 放纸电机一次动作是否结束
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
bool LP_UnloadPaperEnd_IsElapsed(void)
{
	if (UnloadPaperOnceDelay != 0)
		return (FALSE);	
	else 
		return (TRUE);
	
}
/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : 连续收纸间隔时间
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void LP_AlwaysUnloadPaperStopDelay(void)
{
	AlwaysUnloadPaperStopDelay = TIME_ALWAYS_UNLOAD_PAPER_DELAY_STOP ;
}  

/*******************************************************************************
* Function Name  : LP_UnloadPaperDelay_IsElapsed
* Description    : Check if the delay set by LP_UnloadPaperDelay_IsElapsed is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool LP_AlwaysUnloadPaperStopDelay_IsElapsed(void)
{
	if (AlwaysUnloadPaperStopDelay != 0)
	{
		return (FALSE);
	}
	else 
	{
		return (TRUE);
	}
} 

/*10ms 中断执行一次本程序*/
void Load_PaperSensorSamplingBack(void)
{
	if(PaperMotorSensorSamplingTime!= 0)
	{	
		PaperMotorSensorSamplingTime--;	
		{
			
			//if(LoadPaperDelay == 0 )/*收纸期间不检测*/
			{
				if(Paper_SensorLoad() == TRUE)/*收纸传感器检测*/
					LoadPaperSensorSamplingCnt++;
			}
			//if(UnloadPaperDelay == 0 )/*放纸期间不检测*/
			{
				if(Paper_SensorUnload() == TRUE)/*放纸传传感器检测*/
					UnloadPaperSensorSamplingCnt++;
			}
		}	
	
	}
	if(AlwaysUnloadPaperStopDelay!= 0)/*连续模式下，停顿放纸时间*/
	{	
		AlwaysUnloadPaperStopDelay--;	
	}
	
	if(UnloadPaperBeforeDelay!= 0)/*放纸前延时*/
	{	
		UnloadPaperBeforeDelay--;			
	}	
	if(LoadPaperBeforeDelay!= 0)	/*收纸前延时*/
	{	
		LoadPaperBeforeDelay--;		
		
	}	
	
	if(UnloadPaperOnceDelay!= 0)	/*放纸期间*/
	{	
		UnloadPaperOnceDelay--;	
		
		if(UnloadPaperOnceDelay >= TIME_UNLOAD_MOTOR_ONCE_ON)
		{
			Unload_MotorOnOff(P_MOTOR_ON);			
		}
		else if(UnloadPaperOnceDelay <= 1)
		{
			Unload_MotorOnOff(P_MOTOR_OFF);
		}
	}	
	if(LoadPaperOnceDelay!= 0)/*收纸期间*/
	{	
		LoadPaperOnceDelay--;
		
		if(LoadPaperOnceDelay >= TIME_LOAD_MOTOR_ONCE_ON)
		{
			Load_MotorOnOff(P_MOTOR_ON);			
		}
		else if (LoadPaperOnceDelay <=  1)
		{
			Load_MotorOnOff(P_MOTOR_OFF);
		}
	}	
	if(AlwaysUnloadPaperWatchDelay!= 0)
	{	
		AlwaysUnloadPaperWatchDelay--;	
	}
	
}
/*
*传感器检测开始
*/
void Load_PaperSensorSampingOn()
{
	LoadPaperSensorSamplingCnt = 0;
	UnloadPaperSensorSamplingCnt = 0 ;
	PaperMotorSensorSamplingTime = PAPER_MOTOR_SENSOR_SAMPLING_T ; 
}

/*采样是否结束*/
bool Load_PaperSensorSampling_IsEnd(void)
{
	if(PaperMotorSensorSamplingTime!=0)
	  return FALSE;
        else
	  return TRUE;
}
/*是否需要收纸*/
bool Load_PaperIs( )
{
	if(LoadPaperSensorSamplingCnt >=PAPER_SENSOR_SAMPLING_CNT -1)
	{
		LoadPaperSensorSamplingCnt = 0 ;
		return TRUE;
	}
	return FALSE;
}
/*是否需要放纸*/
bool Unload_PaperIs()
{
	if(UnloadPaperSensorSamplingCnt >=PAPER_SENSOR_SAMPLING_CNT -1)
	{
		UnloadPaperSensorSamplingCnt = 0 ;
		return TRUE;
	}
        return FALSE;
}
/*采样程序*/
bool Load_PaperSensorSamplingProc()
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*初始化--1*/			
			Load_PaperSensorSampingOn();
			
			TaskStatus = TASK_RUN;
		
			break;
			
		case TASK_RUN:
			if(Load_PaperSensorSampling_IsEnd() == TRUE)				
				TaskStatus = TASK_END ; 
						
			break;
		
		//case TASK_END:/*执行完毕*/	
			
		//	TaskStatus = TASK_INIT ; //ack ok !
			
		//	break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}
	
        if(TaskStatus==TASK_END)
        {	
        	TaskStatus = TASK_INIT ;
		return TRUE;			
        }	
		
	return FALSE;/*该任务未执行完*/		
}

/*
*收纸控制主程序
*/
void LP_LoadPaperProc( )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:	/*初始化--1*/	
			
			if( Load_PaperIs( )== TRUE ) /*收纸**/
			{
				
				TaskStatus = TASK_RUN;						
			}
			else
			{
				TaskStatus = TASK_END ; 
			}	
					
			break;
			
		case TASK_RUN:
			
			LP_LoadPaperBeforeDelay(3*LOAD_PAPER_TIME_1S );
			TaskStatus = TASK_RUN1;
			
			break;
			
		case TASK_RUN1:
			
			if( LP_LoadPaperBeforeDelay_IsElapsed( )  == TRUE )
			{
				LP_LoadPaperStartup( );
				LedAutoOnOff(LED2) ;	
				TaskStatus = TASK_RUN2 ; 
			}
					
			break;
			
		case TASK_RUN2:
			
			//if( LP_LoadPaperEnd_IsElapsed( ) == TRUE )
			{

				if( Load_PaperIs( )== TRUE ) /*继续收纸**/
				{
					TaskStatus = TASK_RUN1;
					//LP_LoadPaperBeforeDelay(1*LOAD_PAPER_TIME_10MS);
				}
				else /*停止收纸**/
				{
					TaskStatus =  TASK_END ;
				}
			}
			
			break;
			
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ; 
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}	
    	
}
	
/*
*放纸控制主程序
*/
void LP_UnloadPaperProc( )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	static volatile bool NoPaperFlag = FALSE ;					/*无纸--没有安装纸圈*/
	static volatile bool ContinueUnloadPaperFlag = FALSE ;	/*收纸打印过程中，非连续放纸模式*/
	static volatile u16  time_auto_watch_unload_paper_counter = 0 ;	 /*无纸重复放纸次数*/
	
	switch( TaskStatus )
	{
		case TASK_INIT:	/*初始化--1*/			
			if( ( Unload_PaperIs()== TRUE )) /*放纸*/
			{
				
				TaskStatus = TASK_RUN;		/*非连续放纸模式**/
			}
			else
			{
				if( NoPaperFlag ==  TRUE ) 		/*检测到纸，去掉缺纸标记*/
					NoPaperFlag = FALSE ;

				TaskStatus = TASK_END ; 
			}					
			break;
			
		case TASK_RUN:			
			if( NoPaperFlag != TRUE ) 
			{
			
				LP_UnloadPaperBeforeDelay(3*LOAD_PAPER_TIME_1S );		/*长延时*/
				//LP_AlwaysUnloadPaperWatchDelay(3*LOAD_PAPER_TIME_1S + TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY) ;/**/
				TaskStatus = TASK_RUN1 ; 
				
			}
			else /*没有安装纸, 缺纸状态*/
			{
				TaskStatus = TASK_END ; 
			}
										
			break;		
			
		case TASK_RUN1:
			
			if( LP_UnloadPaperBeforeDelay_IsElapsed( )  == TRUE )/*放纸前延时是否到*/
			{
			
				TaskStatus = TASK_RUN3 ; 
				LP_AlwaysUnloadPaperWatchDelay(TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY) ;/*进入连续放纸模式*/					
				
			}						
			break;
		case TASK_RUN2:
			
			LP_UnloadPaperBeforeDelay( TIME_ALWAYS_UNLOAD_PAPER_DELAY_STOP );	 /*短延时*/	
			TaskStatus = TASK_RUN3 ; 
			
			break;		
		case TASK_RUN3:	
				if( LP_UnloadPaperBeforeDelay_IsElapsed( )  == TRUE )
				{
					LP_UnloadPaperStartup( );
					LedAutoOnOff(LED3) ;	
					TaskStatus = 	TASK_RUN4;
				}
				
			break;
		case TASK_RUN4:	
			
			if(LP_UnloadPaperEnd_IsElapsed() == TRUE)
			{ 
				TaskStatus = TASK_RUN5 ; 
			}			
			
			break;
	
		case TASK_RUN5:
			
			if( Unload_PaperIs() != FALSE )
			{
				if( LP_AlwaysUnloadPaperWatchDelay_IsElapsed( ) == TRUE )/*连续放纸时间到仍然缺纸**/
				{
					time_auto_watch_unload_paper_counter++;
					NoPaperFlag =  TRUE;           /*无安装纸*/
					/*连续放纸监控时间短相当于一次放纸时间左右，这是重复放纸或者
					认为放纸，连续模式下加间隔放纸减缓放纸速度*/
					if(time_auto_watch_unload_paper_counter >= TIME_AUTO_WATCH_UNLOAD_PAPER_COUNTER)
					{
						TaskStatus = 	TASK_END;
						time_auto_watch_unload_paper_counter = 0 ;
					}
					else
						TaskStatus = TASK_RUN2 ;	/*继续放纸*/
				}
				else
				{
					TaskStatus = TASK_RUN2 ;	/*继续放纸*/
				}
			}
			else		
			{
				
				TaskStatus = TASK_END ; 
			}
			
			break;
			
		case TASK_END:/*执行完毕*/	
						
			TaskStatus = TASK_INIT ; 
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}

}

/*采样->分析-->动作电机*/
#ifdef LP_DUB

void LP_PaperCtr( void )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch( TaskStatus )
	{
		case TASK_INIT:	/*初始化--1*/	

			if( Load_PaperSensorSamplingProc() == TRUE )	/*采样*/			
				TaskStatus = TASK_RUN ; 
						
			break;
			
		case TASK_RUN:	/*分析采样结果, 动作电机*/
			
			LP_LoadPaperProc();
			LP_UnloadPaperProc();
			
			TaskStatus = TASK_END ; 
			break;
		
		case TASK_END:/*执行完毕*/	
			
			TaskStatus = TASK_INIT ;
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}	
    
}

#endif//#ifdef LP_DUB

#endif//#if LOAD_PAPER_EN>0

