//file: servo.c
/*
*Init_ServoGpio内的GPIO_Pin_8 GPIO_Pin_9要设为LOW, Init_ServoPWM 内TIM_OCIdleState为Reset
*
*/
/*******************************************************************************
* Function Name  : Init_ServoGpio
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/

#include "includes.h"
#if SERVO_PWM_EN>0
//s16 hMeasurementArray[2];
static volatile s16 hMeasurementArray = 0 ;
static volatile bool PWMValChangFlag = FALSE;

void Init_ServoGpio( void )
{
        GPIO_InitTypeDef GPIO_InitStructure;

	//#############################################
	  /* Configure IO connected to in1 in2 SERVO *SETP***gpioe***********/
	  /* Enable GPIO_SERVO clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_SERVO | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1 , ENABLE);
	/* Channel 1, 1N out remap  to PE8, 9*/
	 GPIO_PinRemapConfig(  GPIO_FullRemap_TIM1 , ENABLE );
	 
	  /* GPIOE Configuration: Channel 1, 1N as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_SERVO;
	
	  GPIO_Init(GPIO_SERVO, &GPIO_InitStructure);	

	//  GPIO_ResetBits(GPIO_SERVO , GPIO_Pin_8 | GPIO_Pin_9 );
	  
}
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/

void Init_ServoPWM( void )
{

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
		
	 /* TIM1 Configuration ---------------------------------------------------
   Generates 7 PWM signals with 4 different duty cycles:
   TIM1CLK = 72 MHz, Prescaler = 0, TIM1 counter clock = 72 MHz
   TIM1 frequency = TIM1CLK/(SERVO_PWM_PEROD + 1) = 20.00 KHz ---TIM_Period = 3599;
  - TIM1 Channel1 & Channel1N duty cycle = TIM1->CCR1 / (SERVO_PWM_PEROD + 1) = 55% 
  - TIM1 Channel2 & Channel2N duty cycle = TIM1->CCR2 / (SERVO_PWM_PEROD + 1) = 37.5% 
  - TIM1 Channel3 & Channel3N duty cycle = TIM1->CCR3 / (SERVO_PWM_PEROD + 1) = 25%
  - TIM1 Channel4 duty cycle = TIM1->CCR4 / (SERVO_PWM_PEROD + 1) = 12.5% 
  ----------------------------------------------------------------------- */
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = SERVO_PWM_PEROD_DEFAULT ;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(SERVO_PWM_TIM, &TIM_TimeBaseStructure);

  /* Channel 1,  Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = SERVO_PWM_TIM_CCR_VAL_DEFAULT ;  
  /*******************************************************
  *TIM_OCNPolarity和TIM_OCPolarity 同设置为LOW 或
  *HIGH 则输出波形即为互补  同为low 或high 
  *区别会使电机转动方向不同
  *******************************************************/  
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low ;		//TIM_OCPolarity_High ; 	/*互补*/
  TIM_OCInitStructure.TIM_OCNPolarity =  TIM_OCNPolarity_Low ; 	//TIM_OCNPolarity_High;	/*互补*/
  
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set ; //ch2= 1   TIM_OCIdleState_Reset  , TIM_OCIdleState_Set
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set ; //ch1 = 0  TIM_OCNIdleState_Reset , TIM_OCNIdleState_Set

  TIM_OC1Init(SERVO_PWM_TIM, &TIM_OCInitStructure);

#if 0
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
  TIM_OC4Init(TIM1, &TIM_OCInitStructure);
#endif

  /* TIM1 counter enable */
  TIM_Cmd(SERVO_PWM_TIM, ENABLE);

  /* TIM1 Main Output DISABLE */
  TIM_CtrlPWMOutputs( SERVO_PWM_TIM, DISABLE );

}
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/

void Init_Servo(void)
{
	Init_ServoGpio( ) ;
	Init_ServoPWM( );
	//ServoSetDir(DIR_T1) ;
}

/*******************************************************************************
* Function Name  : 
* Description    : 伺服pwm占空比调整
* Input             :dutycycle  example: 65% 写为65 ， 为百分比
* Output         : None
* Return         : None
*******************************************************************************/
void ServoPWMDutyCycleAdj(u8  dutycycle)
{
	u16 tmpccr1;
	tmpccr1  = (u16)( dutycycle * (SERVO_PWM_PEROD_DEFAULT + 1)/100 -1) ;
	 SERVO_PWM_TIM->CCR1 =  tmpccr1;	
}

/*******************************************************************************
* Function Name  : 
* Description    : 伺服pwm占空比调整
* Input             :dutycycle  example: 定时器CCR 寄存器值调整
* Output         : None
* Return         : None
*******************************************************************************/
void ServoPWMDutyAdj(s16  RegVal)
{
	SERVO_PWM_TIM->CCR1 =  RegVal;	
}
/*******************************************************************************
* Function Name  : 
* Description    : 伺服pwm占空比调整
* Input             :dutycycle  example: 定时器CCR 寄存器值调整
* Output         : None
* Return         : None
*******************************************************************************/
s16 ServoPWMDutyAdjGet( void )
{
	return SERVO_PWM_TIM->CCR1 ;	
}
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
void ServoSetDir(SevroDir dir)
{
	u16 tmpccer = 0;
		
	   /* TIM1 Main Output DIsable */
	// TIM_CtrlPWMOutputs(SERVO_PWM_TIM, DISABLE);
	 /* Get the TIMx CCER register value */
 	tmpccer = SERVO_PWM_TIM->CCER;	
	
	switch(dir)
	{
		case DIR_T1:
			
			  /* Set the Output Compare Polarity */
			  tmpccer |= TIM_OCPolarity_Low;
			  /* Set the Output N State */
			  tmpccer |= TIM_OCNPolarity_Low;
			break;
			
		case DIR_T2:
			
			 /* Set the Output Compare Polarity */
			  tmpccer &= ~TIM_OCPolarity_Low ;
			  /* Set the Output N State */
			  tmpccer &= ~TIM_OCNPolarity_Low ;
			break;
			
		default:
			
			break;	
	}

	SERVO_PWM_TIM->CCER = tmpccer ;	
	//TIM_CtrlPWMOutputs(SERVO_PWM_TIM, ENABLE);	
	
}


/*******************************************************************************
* Function Name : MCDAC_Output
* Description : provides a short description of the function
* Input : details the input parameters.
* Output : details the output parameters.
* Return : details the return value.
*******************************************************************************/
void MC_ServoPWM_Update_Output(void)
{
	if(PWMValChangFlag == TRUE)
	{
		PWMValChangFlag = FALSE ;
 		ServoPWMDutyAdj(hMeasurementArray);
	}
}

/*******************************************************************************
* Function Name : MC_Servo_Send_Output_Value
* Description : provides a short description of the function
* Input : details the input parameters.
* Output : details the output parameters.
* Return : details the return value.
*******************************************************************************/
void MC_ServoPWM_Update_Value(u8 bVariable, s16 hValue)
{
	hMeasurementArray = hValue;
	PWMValChangFlag = TRUE;
}


 

//u16 DutyClcyleRegVal = SERVO_PWM_TIM_CCR_VAL;

/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
void ServoTest( void )
{
#if 0
		 
		#if 1
		static u8 tdir = 0 ;
		static ServoSprotStatus ServoSpeedAdjStep= SERVO_SPEED_UP;
		static u8 DutyClcyle = 50;
		#endif
		static u8 ServoEnable = ENABLE ;
		if(ServoEnable == ENABLE)
		{
			ServoEnable = DISABLE ;
			TIM_CtrlPWMOutputs(TIM1, ENABLE);	
		}
		while(1)
		{
		#if 1
		if(TB_ServoDelayNms_IsElapsed( ) == TRUE)
		{
		switch(ServoSpeedAdjStep)
		{
			
			case SERVO_SPEED_UP :
				/*加速*/
				{
					DutyClcyle += 5;
					ServoPWMDutyCycleAdj(DutyClcyle);					
					TB_ServoDelayNms(200 );	/**/
			
				}	
				
				if (DutyClcyle>= 63)
						ServoSpeedAdjStep = SERVO_SPEED_FIX;
				
				break;
				
			case SERVO_SPEED_FIX :
				TB_ServoDelayNms( 2000 );	/*匀速*/
				
				ServoSpeedAdjStep = SERVO_SPEED_DOWN;
				break;
				
			case SERVO_SPEED_DOWN :
				/*减速*/
				{
					DutyClcyle -= 5;						
					ServoPWMDutyCycleAdj(DutyClcyle);					
					
					TB_ServoDelayNms( 200 );/**/
				}	
				
				if (DutyClcyle <= 55 )
						ServoSpeedAdjStep = SERVO_DIR_CHANGE;
				
				break;
				
			case SERVO_DIR_CHANGE:
				/*换向*/		 
				if (tdir ==0)
				{
					ServoSetDir(DIR_T2) ;
					tdir =1;
				}
				else
				{
					ServoSetDir(DIR_T1) ;
					tdir =0;
				}					
				TB_ServoDelayNms( 1000 );/**/				
				DutyClcyle = 50;

				ServoSpeedAdjStep = SERVO_SPEED_UP;
				break;
				
			default:
				
				ServoSpeedAdjStep = SERVO_SPEED_UP;
				break;
			
		}	
		}
		#endif
	}                 		
	
#endif   
}
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
/*******************************************************************************
* Function Name  : 
* Description    : None
* Input             :None
* Output         : None
* Return         : None
*******************************************************************************/
#endif //#if PID_REG_EN>0


