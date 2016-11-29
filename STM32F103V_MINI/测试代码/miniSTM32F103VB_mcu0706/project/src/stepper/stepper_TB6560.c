/*-------------------------------------------
*file: setpper.c
*Description: contorl setp motor
*--------------------------------------------*/

#include "includes.h"

#if STEPPER_TB6560_EN>0
/******************************************************************************
* Function Name  : Stepper_GpioInitTB6560
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_GpioInitTB6560( void )
{

        GPIO_InitTypeDef GPIO_InitStructure;
	  /* Configure IO connected to 164 --tb6560**************/
	  /* Enable GPIO_SERVO clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_STEP_164 , ENABLE);

	  GPIO_InitStructure.GPIO_Pin = STEP_164_CLK_PIN |STEP_164_D12_PIN ;
	  							
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_STEP_164 ;
	  
	GPIO_Init(GPIO_STEP_164 , &GPIO_InitStructure);

	GPIO_ResetBits(GPIO_STEP_164 , STEP_164_CLK_PIN );
	GPIO_ResetBits(GPIO_STEP_164 , STEP_164_D12_PIN );
	 
	  /* Configure IO connected to tb6560*********************/
	  /* Enable GPIO_STEP_tb clock  output  init*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_SETP , ENABLE);

	GPIO_InitStructure.GPIO_Pin = STEP_TB_RST_PIN | STEP_TB_EN_PIN | STEP_TB_CLK_PIN | STEP_TB_CW_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_STEP_TB ;
	GPIO_Init(GPIO_STEP_TB , &GPIO_InitStructure);
	  
	  //------------input----------------------------
	GPIO_InitStructure.GPIO_Pin = STEP_TB_PROTECT_PIN | STEP_TB_MO_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_STEP_TB;
	GPIO_Init( GPIO_STEP_TB , &GPIO_InitStructure );
	
	/*TB6560 , ctr pin*/
	GPIO_ResetBits(GPIO_STEP_TB , STEP_TB_RST_PIN );
	GPIO_ResetBits(GPIO_STEP_TB , STEP_TB_EN_PIN );	
	GPIO_ResetBits(GPIO_STEP_TB , STEP_TB_CLK_PIN );
	GPIO_ResetBits(GPIO_STEP_TB , STEP_TB_CW_PIN );	
	Delaynus(100);
	
}

/*******************************************************************************
* Function Name  : Stepper_ResetTB6560
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_ResetTB6560(void)
{
	
	GPIO_ResetBits( GPIO_STEP_TB, STEP_TB_RST_PIN);	
	Delaynus(1000);
	GPIO_SetBits( GPIO_STEP_TB, STEP_TB_RST_PIN );		/*RST = H*/	
}
/*******************************************************************************
* Function Name  : Stepper_EnableTB6560
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_EnableTB6560 ( void )
{

	GPIO_SetBits( GPIO_STEP_TB , STEP_TB_EN_PIN );		/*ENABLE = H*/
	Delaynus(10);
	
}
/*******************************************************************************
* Function Name  : Stepper_SetDirTB6560
* Description    : 转动方向设定
* Input          : dir , STEP_DIR_CW & STEP_DIR_CCW
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_SetDirTB6560( SetpperDir dir )
{	

	if(dir == STEP_DIR_CW) //
		GPIO_ResetBits( GPIO_STEP_TB , STEP_TB_CW_PIN );		/*CW  = L 设置方向*/

	else if(dir == STEP_DIR_CCW) 	//SETPER_DIR_CCW
		GPIO_SetBits ( GPIO_STEP_TB , STEP_TB_CW_PIN );		/* CCW = H 设置方向*/
	
	Delaynus(1);
	
}

/*******************************************************************************
* Function Name  : Stepper_Set164Value
* Description    : 164 set tb6560 cur ,  phase , dcy.
* Input          : val , 164 output data.
* Output         : None
* Return         : None
*******************************************************************************/

void Stepper_Set164Value( u8 val )
{

	u8 temp = val ;	
       u8  i ;
	   
	for( i = 0 ; i < 8 ; i ++)
	{
		if( ( temp & 0x80 ) == 0 ) 
		{
			/* 164_D12  = L */
			GPIO_ResetBits( GPIO_STEP_164 , STEP_164_D12_PIN );
		}
		else
		{
			/* 164_D12  = H */
			GPIO_SetBits( GPIO_STEP_164 , STEP_164_D12_PIN );
		}
		
		Delaynus(1);
		
		 /*164_CLK  = L*/
		GPIO_ResetBits( GPIO_STEP_164 , STEP_164_CLK_PIN );
		Delaynus(1);
		
		 /*164_CLK  = H*/
		GPIO_SetBits( GPIO_STEP_164 , STEP_164_CLK_PIN );
		Delaynus(1);
		 
                temp <<= 1;

	}
	
}

/*******************************************************************************
* Function Name  : Stepper_ModeSetTB6560
* Description    : 164 set tb6560 cur ,  phase , dcy.
* Input             : 1, mode , 只有两个可选值: STEP_WORK_MODE  or STEP_WEAK_MODE
*			     2, run_dir 转动方向合法值: STEP_DIR_CW or STEP_DIR_CCW
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_SetCurTB6560( SetpperCurMode mode )
{

	u8 temp = STEP_164_DCY_00 |STEP_164_EXC_PHASE_2W12  ;
	switch(mode)
	{
		case STEP_CUR_WORK_MODE:
			temp |=  ( STEP_164_TQ_75)  ;
			
			break;
			
		case STEP_CUR_WEAK_MODE :
			temp |=  ( STEP_164_TQ_20)  ;
			
			break;
			
		default :
			
			break;			
	}
	
	Stepper_Set164Value(temp);	
	
}
/*******************************************************************************
* Function Name  : Stepper_ModeSetTB6560
* Description    : 164 set tb6560 cur ,  phase , dcy.
* Input             : 1, mode , 只有两个可选值: STEP_WORK_MODE  or STEP_WEAK_MODE
*			     2, run_dir 转动方向合法值: STEP_DIR_CW or STEP_DIR_CCW
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_ModeSetTB6560( SetpperCurMode mode , SetpperDir run_dir)
{

	Stepper_SetCurTB6560(mode) ;
	Stepper_SetDirTB6560(run_dir);
	
}
/*******************************************************************************
* Function Name  : Init_Setpper
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_InitTB6560(void)
{

	Stepper_GpioInitTB6560( );
	
	Stepper_ResetTB6560();	
	Stepper_EnableTB6560();

	Stepper_ModeSetTB6560( STEP_CUR_WEAK_MODE , STEP_DIR_CW );	
	
}
/*******************************************************************************
* Function Name  : Stepper_Setp
* Description    : 电机走num 步
* Input          : num , 所走的步数
* Output         : None
* Return         : None
*******************************************************************************/
void Stepper_StepTB6560( u16 num )
{
	while(num--)
	{
		//GPIO_ResetBits( GPIO_STEP_TB, STEP_TB_CLK_PIN );//fclk = 4.7K 最好
		GPIO_WriteBit(GPIO_STEP_TB, STEP_TB_CLK_PIN, (BitAction)(1-GPIO_ReadOutputDataBit(GPIO_STEP_TB, STEP_TB_CLK_PIN)));
		Delaynus(50 * 2);		/*100us*/
		//GPIO_SetBits( GPIO_STEP_TB , STEP_TB_CLK_PIN );
		//Delaynus(50 * 2);
	}
}
#if 0
#define STEPPER_STEP_NUM 2000
/*******************************************************************************
* Function Name  :API_SetpperForward 
* Description    : 固定步进数STEPPER_STEP_NUM
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void API_StepperForward(void)
{

	//Set_TB6560Mode( STEP_WORK_MODE , STEP_DIR_CW );	
	API_Stepper_Setp(STEPPER_STEP_NUM);
	//Set_TB6560Mode( STEP_WEAK_MODE , STEP_DIR_CW );
	
}
/*******************************************************************************
* Function Name  : API_SetpperBackward
* Description    : 固定步进数2000
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void API_StepperBackward(void)
{

	//Set_TB6560Mode( STEP_WORK_MODE , STEP_DIR_CCW );	
	
	API_Stepper_Setp( STEPPER_STEP_NUM );
	
	//Set_TB6560Mode( STEP_WEAK_MODE , STEP_DIR_CCW );	
	
}
#endif

#endif //#if STEPPER_TB6560_EN>0
