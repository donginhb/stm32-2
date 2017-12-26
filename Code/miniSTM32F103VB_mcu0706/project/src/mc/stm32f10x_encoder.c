/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : stm32f10x_encoder.c 
* Author             : IMS Systems Lab  
* Date First Issued  : 21/11/07
* Description        : This file contains the software implementation for the
*                      encoder unit
********************************************************************************
* History:
* 21/11/07 v1.0
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
//#include "platform_config.h"
#include "includes.h"

#if ENCODER_EN>0

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define ENCODER_PPR           	(u16)(400)   // number of pulses per revolution
#define COUNTER_RESET    0	//   (u16) ((((s32)(ALIGNMENT_ANGLE)*4*ENCODER_PPR/360)\
                                                //              -1)/POLE_PAIR_NUM)
#define ICx_FILTER      		(u8)6 // 6<-> 670nsec

#define TIMx_PRE_EMPTION_PRIORITY 		1
#define TIMx_SUB_PRIORITY 				0

//#define SPEED_SAMPLING_TIME   PID_SPEED_SAMPLING_TIME


/* Private functions ---------------------------------------------------------*/
s16 ENC_Calc_Rot_Speed(void );
void ENC_Reset_Position(void);
void ENC_Clear_Speed_Buffer(void);

/* Private variables ---------------------------------------------------------*/
static volatile s16 hPrevious_angle, hSpeed_Buffer[SPEED_BUFFER_SIZE] ;
static volatile s16 hRot_Speed;
static volatile u8 bSpeed_Buffer_Index = 0;
static volatile u16 hEncoder_Timer_Overflow; /*计数器溢出次数*/
static bool bIs_First_Measurement = TRUE;

static volatile s32 hRot_Position;/*小车当前的位置*/
static volatile u16 hEncoder_Timer_Position_Overflow  ; /*计数器溢出次数，小车单程所走的光栅格数*4  (每格产生四个边沿)*/
static bool bIs_First_Measurement_Position= TRUE;
  static volatile s16 hPrevious_Position ;
  #define X_ENC_N
/*******************************************************************************
* Function Name  : ENC_GpioInit
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_GpioInit(void )
{
	/* Encoder unit connected to TIM3, 4X mode */    
	GPIO_InitTypeDef GPIO_InitStructure;
	//Y轴小车运动
	/* Enable GPIOA, clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	  GPIO_StructInit(&GPIO_InitStructure);
	  /* Configure PA.00,01 as encoder input */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  //  x轴 走纸
	   /* Enable GPIOA, clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	  
	  GPIO_StructInit(&GPIO_InitStructure);
	  /* Configure PB.06,07 as encoder input */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}
/*******************************************************************************
* Function Name  : ENC_NVICInit
* Description    : 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_NVICInit( void )
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	  /* Enable the TIM2 Update Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = ENCODER_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  
	#ifdef X_ENC
	 /* Enable the TIM4 Update Interrupt */
	  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQChannel;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = TIMx_PRE_EMPTION_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = TIMx_SUB_PRIORITY;
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	  NVIC_Init(&NVIC_InitStructure);
	  #endif
	  
	  
}
/*******************************************************************************
* Function Name  : ENC_TimInit
* Description    : TIM2 init  counter
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_TimInit( void )
{
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_ICInitTypeDef TIM_ICInitStructure;
	
	   /* TIM2 clock source enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_ENC_TIM ,  ENABLE);
	   
	#ifdef X_ENC
	  /* TIM4 clock source enable */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	#endif
		  
	 /* Timer configuration in Encoder mode */
  TIM_DeInit(ENCODER_TIMER);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
  TIM_TimeBaseStructure.TIM_Period = ENCODER_RASTER_T1T2_EDGE_NUM -1;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
  TIM_TimeBaseInit(ENCODER_TIMER, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(ENCODER_TIMER, TIM_EncoderMode_TI12, 
                             TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
  TIM_ICStructInit(&TIM_ICInitStructure);
  
  TIM_ICInitStructure.TIM_ICFilter = ICx_FILTER;
  TIM_ICInit(ENCODER_TIMER, &TIM_ICInitStructure);
  
 // Clear all pending interrupts
  TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
  TIM_ITConfig(ENCODER_TIMER, TIM_IT_Update, ENABLE);
  //Reset counter
  ENCODER_TIMER->CNT = COUNTER_RESET;
  ENC_Clear_Speed_Buffer();
  ENC_Reset_Position();
  TIM_Cmd(ENCODER_TIMER, ENABLE);  
  
}
/*******************************************************************************
* Function Name  : ENC_Init
* Description    : General Purpose Timer x set-up for encoder speed/position 
*                  sensors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Init(void)
{
	ENC_NVICInit();
	ENC_GpioInit();	
  	ENC_TimInit() ;
}

/*******************************************************************************
* Function Name  : ENC_ResetEncoder
* Description    : Write the encoder counter with the value corresponding to
*                  ALIGNMENT_ANGLE
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_ResetEncoder(void)
{
  //Reset counter
	ENCODER_TIMER->CNT = COUNTER_RESET;
}

/*******************************************************************************
* Function Name  : ENC_Clear_Speed_Buffer
* Description    : Clear speed buffer used for average speed calculation  
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Clear_Speed_Buffer(void)
{   
  u32 i;

  for (i=0;i<SPEED_BUFFER_SIZE;i++)
  {
    hSpeed_Buffer[i] = 0;
  }
  bIs_First_Measurement = TRUE;
  
}
/*******************************************************************************
* Function Name  : ENC_Reset_Position
* Description    : Clear s 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ENC_Reset_Position(void)
{   
	
	bIs_First_Measurement_Position = TRUE;
	ENC_ResetEncoder();
  
}

/**************************************************************************
*stm32f编码器接口关于换向计数器CNT上升计数和下降计数
*当前为上升计数，换向后为下降计数，
*在上升计数的基础上减计数户即down
*反之亦然。
***************************************************************************/
u16  ENC_Timer_Position_Get(void)
{	
	//s16 CurCnt = 0  ;
	
	if( bIs_First_Measurement_Position == TRUE )	
	{
		bIs_First_Measurement_Position = FALSE ;
		
		hEncoder_Timer_Position_Overflow = 0;  	
		if (hEncoder_Timer_Position_Overflow != 0) 
		{
		 	hEncoder_Timer_Position_Overflow = 0;  	
		}
		
	}

	return (u16)ENCODER_TIMER->CNT ;
}
/*******************************************************************************
* Function Name  : ENC_Calc_Rot_Speed
* Description    : Compute return latest speed measurement 
* Input          : None
* Output         : s16
* Return         : Return the speed in 0.1Hz inch.     此函数输出数值单位: 英尺/10s(  inch/10s  )
*******************************************************************************/
s16 ENC_Calc_Rot_Speed(void)
{   
// ServoCarPosCtr_t  *c = CarPos ;
  s32 wDelta_angle;
  u16 hCurrent_angle_sample_one, hCurrent_angle_sample_two;
  signed long long temp;
  s16 haux;
  u16 hEnc_Timer_Overflow_sample_one, hEnc_Timer_Overflow_sample_two;
  
  if (!bIs_First_Measurement)
  {
	
	  {		
		    // 1st reading of overflow counter    
		    hEnc_Timer_Overflow_sample_one = hEncoder_Timer_Overflow; 
		    // 1st reading of encoder timer counter
		    hCurrent_angle_sample_one = ENCODER_TIMER->CNT;
		    // 2nd reading of overflow counter
		    hEnc_Timer_Overflow_sample_two = hEncoder_Timer_Overflow;  
		    // 2nd reading of encoder timer counter
		    hCurrent_angle_sample_two = ENCODER_TIMER->CNT;      

		    // Reset hEncoder_Timer_Overflow and read the counter value for the next
		    // measurement
		    hEncoder_Timer_Overflow = 0;
		    haux = ENCODER_TIMER->CNT;   
		    
		    if (hEncoder_Timer_Overflow != 0) 
		    {
		      haux = ENCODER_TIMER->CNT; 
		      hEncoder_Timer_Overflow = 0;            
		    }
		     
		    if (hEnc_Timer_Overflow_sample_one != hEnc_Timer_Overflow_sample_two)
		    { //Compare sample 1 & 2 and check if an overflow has been generated right 
		      //after the reading of encoder timer. If yes, copy sample 2 result in 
		      //sample 1 for next process 
		      hCurrent_angle_sample_one = hCurrent_angle_sample_two;
		      hEnc_Timer_Overflow_sample_one = hEnc_Timer_Overflow_sample_two;
		    }
		    
		    if ( (ENCODER_TIMER->CR1 & TIM_CounterMode_Down) == TIM_CounterMode_Down)  
		    {// encoder timer down-counting 定向为反向转动
		      wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle - 
		                    (hEnc_Timer_Overflow_sample_one) * ENCODER_RASTER_T1T2_EDGE_NUM);
		    }
		    else  
		    {//encoder timer up-counting , 定为正向转动
				wDelta_angle = (s32)(hCurrent_angle_sample_one - hPrevious_angle + 
		             		(hEnc_Timer_Overflow_sample_one) * ENCODER_RASTER_T1T2_EDGE_NUM);
		    }	  
	  }
	
    // speed computation as delta angle * 1/(speed sempling time)
    temp = (signed long long)(wDelta_angle * SPEED_SAMPLING_FREQ  );	/*每个PID_SPEED_SAMPLING_FREQ 码盘产生 脉冲数,Encoder T1+T2 边沿数/秒 */
  // temp *= 10;  /*0.1 Hz inch  inch/10s   ,  计数值扩大10倍，因此得到值单位为0.1Hz*/
   //temp *=   60; /*Encoder T1+T2 边沿数 /分*/   
    temp = (long ) temp*254 /(ENCODER_PPR_LINE*10); /*计数出temp = ( mm/1s )   */
    //temp = (long ) temp/(ENCODER_PPR_LINE); /*计数出temp = ( mm/1s )   */
   
  } //is first measurement, discard it
  else
  {
	bIs_First_Measurement = FALSE;
	temp = 0;
	
	hEncoder_Timer_Overflow = 0;
	haux = ENCODER_TIMER->CNT;       
	// Check if Encoder_Timer_Overflow is still zero. In case an overflow IT 
	// occured it resets overflow counter and wPWM_Counter_Angular_Velocity
    if (hEncoder_Timer_Overflow != 0) 
    {
		haux = ENCODER_TIMER->CNT; 
		hEncoder_Timer_Overflow = 0;            
    }
  }
  
hPrevious_angle = haux;  
 
  return((s16) temp);
  
}
/*******************************************************************************
* Function Name  : ENC_Get_Mechanical_Speed
* Description    : Export the value of the smoothed motor speed computed in 
*                  ENC_Calc_Average_Speed function  
* Input          : None
* Output         : s16
* Return         : Return motor speed in 0.1 Hz resolution. This routine 
                   will return the average mechanical speed of the motor.  此函数输出数值单位: 转/10s      
*******************************************************************************/
s16  ENC_Get_Mechanical_Speed(void)
{
	//if(hRot_Speed<0)
		//hRot_Speed = -hRot_Speed;
	return(hRot_Speed);
}

/*******************************************************************************
* Function Name  : ENC_Calc_Average_Speed
* Description    : Compute smoothed motor speed based on last SPEED_BUFFER_SIZE
                   informations and store it variable  
* Input          : None
* Output         : s16
* Return         : Return rotor speed in  0.1Hz resolution. This routine 
                   will return the average mechanical speed of the motor.
*******************************************************************************/
void ENC_Calc_Average_Speed(void )
{  

  s32 wtemp;
  u32 i;
   
  wtemp = ENC_Calc_Rot_Speed();
        
/* Compute the average of the read speeds */  
  hSpeed_Buffer[bSpeed_Buffer_Index] = (s16)wtemp;
  bSpeed_Buffer_Index++;
  
  if (bSpeed_Buffer_Index == SPEED_BUFFER_SIZE) 
  {
	 bSpeed_Buffer_Index = 0;
  }

  wtemp=0;

  for (i=0; i<SPEED_BUFFER_SIZE; i++)
  {
	wtemp += hSpeed_Buffer[i];
  }
  wtemp = (s32) wtemp /SPEED_BUFFER_SIZE;
//  wtemp = (s32) wtemp >>3 ;
 hRot_Speed = ((s16)(wtemp));

}


void EncoderTest( void )
{

	#if 0
	while(1)
	{
		if ( TB_LCMDisplayDelayNms_IsElapsed() == TRUE )
		{
			//LedAutoOnOff(LED2);		
			TB_LCMDisplayDelayNms( 200 );
		}
		//ServoTest();
	}
	#endif
	
}

/*******************************************************************************
* Function Name  : ENCODER_TIM_IRQHandler
* Description    : This function handles TIM Update interrupt request.
                   Encoder unit connected to TIM   counter mode;
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void TIM2_IRQHandler(void)
void ENCODER_TIM_IRQHandler(void)
{  
  /* Clear the interrupt pending flag */
  TIM_ClearFlag(ENCODER_TIMER, TIM_FLAG_Update);
  
  if (hEncoder_Timer_Overflow != U16_MAX)  
	hEncoder_Timer_Overflow++;
  else
  	hEncoder_Timer_Overflow = 0  ;
  
  if(hEncoder_Timer_Position_Overflow!=U16_MAX)  	
  	hEncoder_Timer_Position_Overflow++;
  else
  	hEncoder_Timer_Position_Overflow = 0; 
  
}

#endif //#if ENCODER_EN>0

/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
