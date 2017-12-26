//file:loadpaper.c

#include "includes.h"

#if LOAD_PAPER_EN>0

#define LOAD_PAPER_TIME_10MS 		 (10*10/(TIM_CCR_VAl_P_MOTOR_SENSOR_SAMPLEING))
#define LOAD_PAPER_TIME_100MS 	 (LOAD_PAPER_TIME_10MS*10)
#define LOAD_PAPER_TIME_1S			 (LOAD_PAPER_TIME_10MS*100)

#define PAPER_SENSOR_SAMPLING_CNT  	(10) /*һ�βɼ���������������*/

#define TIME_MOTOR_ON_BEFORE_DELAY 		(3* LOAD_PAPER_TIME_1S)/*��������⵽�����źţ������������ʱ*/

/* �����ת��ʱ��*/
#define TIME_LOAD_MOTOR_ONCE_ON			(10 * LOAD_PAPER_TIME_10MS )  /*��ֽ��￪��ʱ��*/
#define TIME_LOAD_PAPER_ONCE_DELAY 		(  TIME_LOAD_MOTOR_ONCE_ON  + 1 )	/*��ֽ��ʱ*/


/*��ֽ�����ת��ʱ��*/
#define TIME_UNLOAD_MOTOR_ONCE_ON	  			(20* LOAD_PAPER_TIME_10MS  ) /*��ֽ��￪��ʱ��*/
#define TIME_UNLOAD_PAPER_ONCE_DELAY   	 		( TIME_UNLOAD_MOTOR_ONCE_ON + 2 )	
#define TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY 	( TIME_UNLOAD_MOTOR_ONCE_ON *5 )  /*��ֽ���ʱ�䣬��ֹ��ֽһֱ��ֽ״̬����*/

#define TIME_ALWAYS_UNLOAD_PAPER_DELAY_STOP 	(1* LOAD_PAPER_TIME_10MS)	/*������ֽ,�ڼ�ֹͣ��ֽʱ�� */

#define TIME_AUTO_WATCH_UNLOAD_PAPER_COUNTER  		1	 /*��ֽ���Է�ֽ����*/
#define PAPER_MOTOR_SENSOR_SAMPLING_T   	PAPER_SENSOR_SAMPLING_CNT  /*���ֽ�����������10ms����һ��*/

static vu8 PaperMotorSensorSamplingTime = 0 ;
static vu8 LoadPaperSensorSamplingCnt = 0 , UnloadPaperSensorSamplingCnt = 0 ;	/*�շ�ֽ�������涨ʱ���ڲ�����Ч����������*/

static vu16 AlwaysUnloadPaperWatchDelay = 0 ;	/*������ֽ,�ڼ�ֹͣ��ֽʱ�� */
static vu16 UnloadPaperBeforeDelay = 0 ;				/*��������⵽�����źţ������������ʱ*/
static vu16 UnloadPaperOnceDelay = 0 ;			/*��ֽ���һ�δ�ʱ��*/
static vu16 AlwaysUnloadPaperStopDelay = 0 ; 	/*������ֽ,�ڼ�ֹͣ��ֽʱ�� */
static vu16 LoadPaperBeforeDelay = 0 ;				/*��������⵽�����źţ������������ʱ*/
static vu16 LoadPaperOnceDelay = 0 ;			/*��ֽ���һ�δ�ʱ��*/

//static volatile bool  ShortPaperFlag = FALSE ;	/*ȱֽ��ӡ������ȱֽ*/
//static volatile bool  LoadPaperFlag = FALSE ;	/*��ֽ��ӡ������*/

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
*�շ�ֽ��￪��
**************************************************/
#if 1
/*��ֽ���*/
void Load_MotorOnOff(PaperMotorOnOff  PMOnOff )
{
	if(PMOnOff != P_MOTOR_OFF)
		GPIO_ResetBits( GPIO_LP_MOTOR , LP_MOTOR_PIN );
	else
		GPIO_SetBits( GPIO_LP_MOTOR , LP_MOTOR_PIN );
}

/*��ֽ���*/
void Unload_MotorOnOff(PaperMotorOnOff  PMOnOff )
{
	if(PMOnOff != P_MOTOR_OFF)
		GPIO_ResetBits( GPIO_LP_MOTOR , UNLP_MOTOR_PIN );
	else
		GPIO_SetBits( GPIO_LP_MOTOR , UNLP_MOTOR_PIN );
}
#endif
/*********************************************************
*�����շ�ֽ������̽ͷ����ź�:
*��ֽ���: Low ;    
*��ֽ���: High
*********************************************************/
/**Paper_SensorLoad ��ֽ���: High,Ϊ��Ч*/
bool Paper_SensorLoad( )
{

	if( GPIO_ReadInputDataBit( GPIO_LP_SENSOR , LP_SENSOR_PIN ) != 0x00)/*��ֽ������*/
		return TRUE ;/*��ֽ���м�⵽��ֽ���趯�������ֽ*/
	else
		return FALSE;
	
}
/**Paper_SensorUnload ��ֽ���: Low ;  ��Ч�ź�*/
bool Paper_SensorUnload( )
{

	if( GPIO_ReadInputDataBit( GPIO_LP_SENSOR , UNLP_SENSOR_PIN )!= 0x00) /*��ֽ������*/			
		return FALSE ;/*��ֽ��������⵽ֽ�����ٷ�ֽ��*/
	else
		return TRUE ; /*��ⲻ��ֽ���趯����ֽ�����ֽ*/
	
}

/*
*�շ�ֽ�������ɼ�����
*/

/*******************************************************************************
* Function Name  : LP_AlwaysUnloadPaperWatchDelay
* Description    : ������ֽ���ʱ��
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
* Description    : ��ֽ֮ǰ��ʱʱ��
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
* Description    : ��ֽ֮ǰ��ʱ
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
* Description    : ��ֽʱ��
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
* Description    : ��ֽ���һ�ζ����Ƿ����
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
* Description    : ��ֽʱ��
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
* Description    : ��ֽ���һ�ζ����Ƿ����
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
* Description    : ������ֽ���ʱ��
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

/*10ms �ж�ִ��һ�α�����*/
void Load_PaperSensorSamplingBack(void)
{
	if(PaperMotorSensorSamplingTime!= 0)
	{	
		PaperMotorSensorSamplingTime--;	
		{
			
			//if(LoadPaperDelay == 0 )/*��ֽ�ڼ䲻���*/
			{
				if(Paper_SensorLoad() == TRUE)/*��ֽ���������*/
					LoadPaperSensorSamplingCnt++;
			}
			//if(UnloadPaperDelay == 0 )/*��ֽ�ڼ䲻���*/
			{
				if(Paper_SensorUnload() == TRUE)/*��ֽ�����������*/
					UnloadPaperSensorSamplingCnt++;
			}
		}	
	
	}
	if(AlwaysUnloadPaperStopDelay!= 0)/*����ģʽ�£�ͣ�ٷ�ֽʱ��*/
	{	
		AlwaysUnloadPaperStopDelay--;	
	}
	
	if(UnloadPaperBeforeDelay!= 0)/*��ֽǰ��ʱ*/
	{	
		UnloadPaperBeforeDelay--;			
	}	
	if(LoadPaperBeforeDelay!= 0)	/*��ֽǰ��ʱ*/
	{	
		LoadPaperBeforeDelay--;		
		
	}	
	
	if(UnloadPaperOnceDelay!= 0)	/*��ֽ�ڼ�*/
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
	if(LoadPaperOnceDelay!= 0)/*��ֽ�ڼ�*/
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
*��������⿪ʼ
*/
void Load_PaperSensorSampingOn()
{
	LoadPaperSensorSamplingCnt = 0;
	UnloadPaperSensorSamplingCnt = 0 ;
	PaperMotorSensorSamplingTime = PAPER_MOTOR_SENSOR_SAMPLING_T ; 
}

/*�����Ƿ����*/
bool Load_PaperSensorSampling_IsEnd(void)
{
	if(PaperMotorSensorSamplingTime!=0)
	  return FALSE;
        else
	  return TRUE;
}
/*�Ƿ���Ҫ��ֽ*/
bool Load_PaperIs( )
{
	if(LoadPaperSensorSamplingCnt >=PAPER_SENSOR_SAMPLING_CNT -1)
	{
		LoadPaperSensorSamplingCnt = 0 ;
		return TRUE;
	}
	return FALSE;
}
/*�Ƿ���Ҫ��ֽ*/
bool Unload_PaperIs()
{
	if(UnloadPaperSensorSamplingCnt >=PAPER_SENSOR_SAMPLING_CNT -1)
	{
		UnloadPaperSensorSamplingCnt = 0 ;
		return TRUE;
	}
        return FALSE;
}
/*��������*/
bool Load_PaperSensorSamplingProc()
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:/*��ʼ��--1*/			
			Load_PaperSensorSampingOn();
			
			TaskStatus = TASK_RUN;
		
			break;
			
		case TASK_RUN:
			if(Load_PaperSensorSampling_IsEnd() == TRUE)				
				TaskStatus = TASK_END ; 
						
			break;
		
		//case TASK_END:/*ִ�����*/	
			
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
		
	return FALSE;/*������δִ����*/		
}

/*
*��ֽ����������
*/
void LP_LoadPaperProc( )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch(TaskStatus)
	{
		case TASK_INIT:	/*��ʼ��--1*/	
			
			if( Load_PaperIs( )== TRUE ) /*��ֽ**/
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

				if( Load_PaperIs( )== TRUE ) /*������ֽ**/
				{
					TaskStatus = TASK_RUN1;
					//LP_LoadPaperBeforeDelay(1*LOAD_PAPER_TIME_10MS);
				}
				else /*ֹͣ��ֽ**/
				{
					TaskStatus =  TASK_END ;
				}
			}
			
			break;
			
		case TASK_END:/*ִ�����*/	
			
			TaskStatus = TASK_INIT ; 
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}	
    	
}
	
/*
*��ֽ����������
*/
void LP_UnloadPaperProc( )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	static volatile bool NoPaperFlag = FALSE ;					/*��ֽ--û�а�װֽȦ*/
	static volatile bool ContinueUnloadPaperFlag = FALSE ;	/*��ֽ��ӡ�����У���������ֽģʽ*/
	static volatile u16  time_auto_watch_unload_paper_counter = 0 ;	 /*��ֽ�ظ���ֽ����*/
	
	switch( TaskStatus )
	{
		case TASK_INIT:	/*��ʼ��--1*/			
			if( ( Unload_PaperIs()== TRUE )) /*��ֽ*/
			{
				
				TaskStatus = TASK_RUN;		/*��������ֽģʽ**/
			}
			else
			{
				if( NoPaperFlag ==  TRUE ) 		/*��⵽ֽ��ȥ��ȱֽ���*/
					NoPaperFlag = FALSE ;

				TaskStatus = TASK_END ; 
			}					
			break;
			
		case TASK_RUN:			
			if( NoPaperFlag != TRUE ) 
			{
			
				LP_UnloadPaperBeforeDelay(3*LOAD_PAPER_TIME_1S );		/*����ʱ*/
				//LP_AlwaysUnloadPaperWatchDelay(3*LOAD_PAPER_TIME_1S + TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY) ;/**/
				TaskStatus = TASK_RUN1 ; 
				
			}
			else /*û�а�װֽ, ȱֽ״̬*/
			{
				TaskStatus = TASK_END ; 
			}
										
			break;		
			
		case TASK_RUN1:
			
			if( LP_UnloadPaperBeforeDelay_IsElapsed( )  == TRUE )/*��ֽǰ��ʱ�Ƿ�*/
			{
			
				TaskStatus = TASK_RUN3 ; 
				LP_AlwaysUnloadPaperWatchDelay(TIME_ALWAYS_UNLOAD_PAPER_WATCH_DELAY) ;/*����������ֽģʽ*/					
				
			}						
			break;
		case TASK_RUN2:
			
			LP_UnloadPaperBeforeDelay( TIME_ALWAYS_UNLOAD_PAPER_DELAY_STOP );	 /*����ʱ*/	
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
				if( LP_AlwaysUnloadPaperWatchDelay_IsElapsed( ) == TRUE )/*������ֽʱ�䵽��Ȼȱֽ**/
				{
					time_auto_watch_unload_paper_counter++;
					NoPaperFlag =  TRUE;           /*�ް�װֽ*/
					/*������ֽ���ʱ����൱��һ�η�ֽʱ�����ң������ظ���ֽ����
					��Ϊ��ֽ������ģʽ�¼Ӽ����ֽ������ֽ�ٶ�*/
					if(time_auto_watch_unload_paper_counter >= TIME_AUTO_WATCH_UNLOAD_PAPER_COUNTER)
					{
						TaskStatus = 	TASK_END;
						time_auto_watch_unload_paper_counter = 0 ;
					}
					else
						TaskStatus = TASK_RUN2 ;	/*������ֽ*/
				}
				else
				{
					TaskStatus = TASK_RUN2 ;	/*������ֽ*/
				}
			}
			else		
			{
				
				TaskStatus = TASK_END ; 
			}
			
			break;
			
		case TASK_END:/*ִ�����*/	
						
			TaskStatus = TASK_INIT ; 
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}

}

/*����->����-->�������*/
#ifdef LP_DUB

void LP_PaperCtr( void )
{	
	static volatile TaskStatus_t  TaskStatus = TASK_INIT ;
	
	switch( TaskStatus )
	{
		case TASK_INIT:	/*��ʼ��--1*/	

			if( Load_PaperSensorSamplingProc() == TRUE )	/*����*/			
				TaskStatus = TASK_RUN ; 
						
			break;
			
		case TASK_RUN:	/*�����������, �������*/
			
			LP_LoadPaperProc();
			LP_UnloadPaperProc();
			
			TaskStatus = TASK_END ; 
			break;
		
		case TASK_END:/*ִ�����*/	
			
			TaskStatus = TASK_INIT ;
			
			break;
			
		default:
			TaskStatus = TASK_INIT ;
			break;
	}	
    
}

#endif//#ifdef LP_DUB

#endif//#if LOAD_PAPER_EN>0

