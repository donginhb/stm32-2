/*-------------------------------------------
*file: setpper_A3979.c
*Description: contorl setp motor
*--------------------------------------------*/

#include "includes.h"

#if STEPPER_A3979_EN>0

/******************************************************************************
* Function Name  : Stepper_GpioInitA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_GpioInitA3979( void )
{

        GPIO_InitTypeDef GPIO_InitStructure;	 
	  /* Configure IO connected to A3979*********************/
	  /* Enable GPIO_setp_A3979 clock  output  init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB_STEP_A3979 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD_STEP_A3979 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE_STEP_A3979 , ENABLE);
	//
	GPIO_InitStructure.GPIO_Pin = STEP_A3979_MS1_PIN | STEP_A3979_MS2_PIN ; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIOB_SPEED_STEP_A3979 ;
	GPIO_Init(GPIOB_STEP_A3979 , &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_MS1_PIN );
	GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_MS2_PIN );
	//		
	GPIO_InitStructure.GPIO_Pin = STEP_A3979_SIC1_PIN | STEP_A3979_SIC2_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIOD_SPEED_STEP_A3979 ;
	GPIO_Init(GPIOD_STEP_A3979 , &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOD_STEP_A3979 , STEP_A3979_SIC1_PIN );
	GPIO_ResetBits(GPIOD_STEP_A3979 , STEP_A3979_SIC2_PIN );
	//
	GPIO_InitStructure.GPIO_Pin = STEP_A3979_DIR_PIN | STEP_A3979_RST_PIN\
							|STEP_A3979_EN_PIN|STEP_A3979_CLK_PIN ;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIOE_SPEED_STEP_A3979 ;
	GPIO_Init(GPIOE_STEP_A3979 , &GPIO_InitStructure);	
	
	GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_DIR_PIN );	
	GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_RST_PIN );	
	GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_EN_PIN );	
	GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_CLK_PIN );
	Delaynus(100);
	
}

/*******************************************************************************
* Function Name  : Stepper_ResetA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
static void Stepper_ResetA3979(void)
{
	
	GPIO_ResetBits(GPIO_STEP_A3979_RST , STEP_A3979_RST_PIN );	
	Delaynus(1000);
	GPIO_SetBits( GPIO_STEP_A3979_RST, STEP_A3979_RST_PIN );		/*RST = H*/	
}
/*******************************************************************************
* Function Name  : Stepper_EnableA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
static void Stepper_EnableA3979 ( void )
{

	GPIO_ResetBits( GPIO_STEP_A3979_EN , STEP_A3979_EN_PIN );		/*ENABLE = L */
	Delaynus(10);
	
}


/*******************************************************************************
* Function Name  : Stepper_SetSetpModeA3979
* Description    : 设置细分，即微步模式
* Input             : *			 
* Output         : None
* Return         : None
*other:
//--Excitation settings----M2 M1----细分-----------------
*PIN13  PIN12
*MS1	MS2
*L		L	--FULL SETP
*L		H	--HALF SETP
*H		L	--1/4   SETP
*H		H	--1/16 SETP
*************************************************
*******************************************************************************/
static void Stepper_SetSetpModeA3979(StepperPhase sp)
{
	switch(sp)
	{
		case STEP_FULL:
			GPIO_ResetBits( GPIO_STEP_A3979_MS1 , STEP_A3979_MS1_PIN );
			GPIO_ResetBits( GPIO_STEP_A3979_MS2 , STEP_A3979_MS2_PIN );
			break;
			
		case STEP_HALF:
			GPIO_ResetBits( GPIO_STEP_A3979_MS1 , STEP_A3979_MS1_PIN );
			GPIO_SetBits( GPIO_STEP_A3979_MS2 , STEP_A3979_MS2_PIN );
			break;
			
		case STEP_QUARTER:
			GPIO_SetBits( GPIO_STEP_A3979_MS1 , STEP_A3979_MS1_PIN );
			GPIO_ResetBits( GPIO_STEP_A3979_MS2 , STEP_A3979_MS2_PIN );
			break;
	
		case STEP_MAX:
			GPIO_SetBits( GPIO_STEP_A3979_MS1 , STEP_A3979_MS1_PIN );
			GPIO_SetBits( GPIO_STEP_A3979_MS2 , STEP_A3979_MS2_PIN );
			break;
			
		default:			
			break;
	}
	
}
/*******************************************************************************
* Function Name  : Stepper_SetDirA3979
* Description    : 转动方向设定
* Input          :     run_dir 转动方向合法值: SETPPER_DIR_CW or SETPPER_DIR_CCW
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_SetDirA3979( SetpperDir dir )
{	

	switch(dir ) 
	{
		case STEP_DIR_CW:
			GPIO_ResetBits( GPIO_STEP_A3979_DIR , STEP_A3979_DIR_PIN );	/*CW  = L 设置方向*/
			break;
			
		case STEP_DIR_CCW:
			GPIO_SetBits ( GPIO_STEP_A3979_DIR , STEP_A3979_DIR_PIN );		/* CCW = H 设置方向*/
			break;
			
		default:
			break;
	}	
}
/*******************************************************************************
* Function Name  : Stepper_SetTQA3979
* Description    : 设置电流大小
* Input             : 1, stm , 只有两个可选值: 
*			 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_SetCurA3979( SetpperCurMode  scm )
{
	Stepper_SetSetpModeA3979(STEP_MAX);
	switch(scm)
	{
		case STEP_CUR_WEAK_MODE:			
			GPIO_ResetBits( GPIO_STEP_A3979_SIC1 , STEP_A3979_SIC1_PIN );
			GPIO_SetBits( GPIO_STEP_A3979_SIC2 , STEP_A3979_SIC2_PIN );
			
			break;
			
		case STEP_CUR_WORK_MODE:				
			GPIO_SetBits( GPIO_STEP_A3979_SIC1 ,   STEP_A3979_SIC1_PIN );
			GPIO_ResetBits( GPIO_STEP_A3979_SIC2 , STEP_A3979_SIC2_PIN );
			
			break;						
		default :
			
			break;			
	}	
	
}
/*******************************************************************************
* Function Name  : Stepper_SetModeA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
//void Stepper_SetModeA3979( SetpperDir dir, SetpperCurMode stm, StepperPhase sp )
void Stepper_ModeSetA3979( SetpperCurMode stm , SetpperDir dir )
{

	Stepper_SetDirA3979(dir);
	Stepper_SetCurA3979(stm);	
	Stepper_SetSetpModeA3979(STEP_MAX);
	 
}
/*******************************************************************************
* Function Name  : Stepper_InitA3979
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_InitA3979(void)
{

	Stepper_GpioInitA3979( );
	Stepper_ResetA3979();
	Stepper_EnableA3979();
	Stepper_ModeSetA3979( STEP_CUR_WEAK_MODE , STEP_DIR_CW );	
	
}
/*******************************************************************************
* Function Name  : Stepper_Setp
* Description    : 电机走num 步
* Input          : num , 所走的步数
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_SetpA3979( u16 num )
{
	while(num--)
	{
		//GPIO_ResetBis( GPIO_STEP_A3979, STEP_A3979_STEP_PIN );//fclk = 4.7K 最好
		GPIO_WriteBit( GPIO_STEP_A3979_CLK, STEP_A3979_CLK_PIN, (BitAction)(1-GPIO_ReadOutputDataBit(GPIO_STEP_A3979_CLK, STEP_A3979_CLK_PIN)) );
		Delaynus( 50 * 2 );		/*100us*/

	}
}
#if 0 /*IO test*/
void Stepper_TestIOA3979( void  )
{		
	//while(1)
	{
		#if STEPPER_A3979_EN>0
		GPIO_ResetBits(GPIOC_STEP_A3979 , STEP_A3979_RST_PIN );	
		GPIO_SetBits(GPIOC_STEP_A3979 , STEP_A3979_RST_PIN );	
		
		GPIO_SetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC1_PIN );	
		GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC1_PIN );
		
		GPIO_SetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC2_PIN );
		GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC2_PIN );	
		
		GPIO_SetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC3_PIN );
		GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_SIC3_PIN );
		
		GPIO_SetBits(GPIOB_STEP_A3979 , STEP_A3979_CLK_PIN );	
		GPIO_ResetBits(GPIOB_STEP_A3979 , STEP_A3979_CLK_PIN );	
		
		GPIO_SetBits(GPIOE_STEP_A3979 , STEP_A3979_DIR_PIN );	
		GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_DIR_PIN );		
		
		GPIO_SetBits(GPIOE_STEP_A3979 , STEP_A3979_EN_PIN );	
		GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_EN_PIN );	
			
		GPIO_SetBits(GPIOE_STEP_A3979 , STEP_A3979_MS1_PIN );
		GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_MS1_PIN );
		
		GPIO_SetBits(GPIOE_STEP_A3979 , STEP_A3979_MS2_PIN );
		GPIO_ResetBits(GPIOE_STEP_A3979 , STEP_A3979_MS2_PIN );
		
		#endif
	}	
}
#endif

#endif //#if SETPPER_TB6560_EN>0

