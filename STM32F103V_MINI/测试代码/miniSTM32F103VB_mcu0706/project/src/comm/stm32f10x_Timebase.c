/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_Timebase.c
* Author             : Jian-guo JIANG
* Date First Issued  : 2008.5.14
* Description        : This module handles time base. 
********************************************************************************
* History:
* 2008.5.14: V1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
//#include "stm32f10x_lib.h"
/* Include of other module interface headers ---------------------------------*/
/* Local includes ------------------------------------------------------------*/

#include "includes.h"
#include "stm32f10x_it.h"

#define SYS_RUN_LED_LIGHT_TIME    (2*500)
#define TIME_1MS	(72000)
#define TIME_10MS	(72000 * 10)
#define TIME_500US	(36000)
#define SYSTICK_VALUE  TIME_500US
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static vu16 hTimebase_nms = 0;
static vu16 hServoCarPosDelayN500us = 0;
static vu16 hTimebase_display_500us = 0;
#if PID_REG_EN>0
static vu8  hCalcSpeed_Timebase_500us = SPEED_SAMPLING_TIME ;
static vu16 hSpeedMeas_Timebase_500us = SPEED_SAMPLING_TIME ;
//static vu8  hSpeedCtr_Timebase_500us = SPEED_CTR_TIME_BASE ;
#if SERVO_PWM_EN>0
vu8  bPID_Speed_Sampling_Time_500us = PID_SPEED_SAMPLING_TIME;
#endif //#if SERVO_PWM_EN>0
#else
static vu16 hSpeedMeas_Timebase_500us = 0 ;
vu8 bPID_Speed_Sampling_Time_500us = 0;
#endif
static vu16 bServo_Run_Status_500us = 2 * 300;
static vu16 hLCMDisplayDelayN500us = 0 ;
static vu16 hServoDelayN500us = 0 ;

static vu16 hSysRunLed_Time_500us = SYS_RUN_LED_LIGHT_TIME ;
vu16  DutyClcyleRegVal;
/*******************************************************************************
* Function Name  : TB_Init
* Description    : TimeBase peripheral initialization. The base time is set to 
*                  500usec and the related interrupt is enabled  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TB_Init(void)
{   
  /* Select AHB clock(HCLK) as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
  /* SysTick interrupt each 500usec with Core clock equal to 72MHz */
  SysTick_SetReload(SYSTICK_VALUE);
  /* Enable SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);

  /* Configure the SysTick handler priority */
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 2, 0); 
  /* Enable SysTick interrupt */
  SysTick_ITConfig(ENABLE);
}

/*******************************************************************************
* Function Name  : TB_Set_Delay_nms
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_Delay_nms(u16 nms)
{
	hTimebase_nms = nms;
}  

/*******************************************************************************
* Function Name  : TB_DisplayDelay_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_Delay_IsElapsed(void)
{
	if (hTimebase_nms == 0)
	{
		return (TRUE);
	}
	else 
	{
		return (FALSE);
	}
} 
/*******************************************************************************
* Function Name  : TB_LCMDisplayDelayN500us
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_LCMDisplayDelayNms(u16 nms)
{
	hLCMDisplayDelayN500us = 2*nms;
}  

/*******************************************************************************
* Function Name  : TB_LCMDisplayDelayN500us_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_LCMDisplayDelayNms_IsElapsed(void)
{
	if (hLCMDisplayDelayN500us == 0)
	{
		return (TRUE);
	}
	else 
	{
		return (FALSE);
	}
} 
/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_ServoCarPosDelayNms(u16 nms)
{
	hServoCarPosDelayN500us  = 2*nms;
}  

/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_ServoCarPosDelayNms_IsElapsed(void)
{
	if (hServoCarPosDelayN500us == 0)
	{
		return (TRUE);
	}
	else 
	{
		return (FALSE);
	}
} 
/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_ServoStatusRepDelayNms(u16 nms)
{
	hServoDelayN500us  = 2*nms;
}  

/*******************************************************************************
* Function Name  : TB_ServoStatusRepDelayNms_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_ServoStatusRepDelayNms_IsElapsed(void)
{
	if (hServoDelayN500us == 0)
	{
		return (TRUE);
	}
	else 
	{
		return (FALSE);
	}
} 
/*******************************************************************************
* Function Name  : TB_LCMDisplayDelayN500us
* Description    : Set Delay utilized by main.c module.
* Input          : Time out value
* Output         : None
* Return         : None
*******************************************************************************/
void TB_ServoDelayNms(u16 nms)
{
	hServoDelayN500us =2* nms;
}  

/*******************************************************************************
* Function Name  : TB_LCMDisplayDelayN500us_IsElapsed
* Description    : Check if the delay set by TB_Set_DisplayDelay_500us is elapsed.   
* Input          : None
* Output         : True if delay is elapsed, false otherwise 
* Return         : None
*******************************************************************************/
bool TB_ServoDelayNms_IsElapsed(void)
{
	if (hServoDelayN500us == 0)
	{
		return (TRUE);
	}
	else 
	{
		return (FALSE);
	}
} 
//extern volatile u16  DutyClcyleRegVal;
/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{   
  
#if PID_REG_EN>0
	s16 NewDuty;
	s16 NewSpeed ;
	s32  tSpeedErr; 
	static s16 rCurDuty  ;	
#endif //#if PID_REG_EN>0

	if(hServoCarPosDelayN500us !=0)
		hServoCarPosDelayN500us--;
	if (hTimebase_nms != 0)   
		hTimebase_nms --;
  
	if(hLCMDisplayDelayN500us!=0)
		hLCMDisplayDelayN500us--;
  
	if(hServoDelayN500us!=0)
		hServoDelayN500us--;

  	#if PID_REG_EN>0	
	if(hCalcSpeed_Timebase_500us != 0)
	{
		hCalcSpeed_Timebase_500us--;
	}
	else
	{
		hCalcSpeed_Timebase_500us = SPEED_SAMPLING_TIME;
		//ENC_Calc_Average_Speed must be called ONLY every SPEED_MEAS_TIMEBASE ms		
		ENC_Calc_Average_Speed();  
	}
	
	if (hSpeedMeas_Timebase_500us !=0)
	{
		hSpeedMeas_Timebase_500us--;
	}	
	else
	{		
		hSpeedMeas_Timebase_500us = PID_SPEED_SAMPLING_TIME;
			
		if ( PID_Speed_InitStructure.PID_Reg_EN ==TRUE )
		{
			NewSpeed =  ENC_Get_Mechanical_Speed();/*转速*/
			if(NewSpeed<0) /*因正反转而如此处理*/
				NewSpeed= -NewSpeed;
	
			/*pid adj*/
			tSpeedErr = PID_Speed_Regulator( NewSpeed );		
			rCurDuty = ServoPWMDutyAdjGet() ;
			NewDuty = PID_MCSpeedToPWMRegVal( tSpeedErr , rCurDuty );	
			
			#if SERVO_PWM_EN>0
			if( NewDuty != rCurDuty )
			{	
				rCurDuty = NewDuty ;
				MC_ServoPWM_Update_Value( SERVO_SPEED , NewDuty );	
			
			}
			#endif //#if SERVO_PWM_EN>0
		}     
		
		
	}
	#if SERVO_PWM_EN>0
	  if (bPID_Speed_Sampling_Time_500us != 0 )  
	  {
		bPID_Speed_Sampling_Time_500us --;
	  }
	  else
	  { 
		bPID_Speed_Sampling_Time_500us = SPEED_CTR_500us;       
	      {
		       MC_ServoPWM_Update_Output( );
			//DutyChangFlags = FALSE ;	
			//LedAutoOnOff(LED2); 		
	      }   
	    
	  }	  
	  #endif //#if SERVO_PWM_EN>0
	#endif

	 if (hSysRunLed_Time_500us != 0)
	{
		hSysRunLed_Time_500us--;
	}	
	else
	{
		hSysRunLed_Time_500us = SYS_RUN_LED_LIGHT_TIME;
		  /*1Hz */
		LedAutoOnOff(LED2);
	}
}

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
