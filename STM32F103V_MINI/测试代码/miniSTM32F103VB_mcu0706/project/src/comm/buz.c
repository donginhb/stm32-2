//file: buz.c

#include "stm32f10x_lib.h"
#include "platform_config.h"

#include "includes.h"

#if BUZ_EN>0

/*******************************************************************************
* Function Name  : Init_BuzGpio
* Description    : None
* Input             :None 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Init_BuzGpio(void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
	//#############################################
	  /* Configure IO connected to buz *********************/
	  /* Enable GPIO_buz clock */
	  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIO_BUZ , ENABLE );

	  GPIO_InitStructure.GPIO_Pin = BUZ_PIN6 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init( GPIO_BUZ , &GPIO_InitStructure );

	//buz off**********************
  	GPIO_SetBits(GPIO_BUZ , BUZ_PIN6);
}

/*******************************************************************************
* Function Name  : Buz_On
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Buz_On(void)
{

	//buz on**********************
  	GPIO_ResetBits( GPIO_BUZ , BUZ_PIN6 );
	
}
/*******************************************************************************
* Function Name  : Buz_Off
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/
void Buz_Off(void)
{

	//buz off**********************
  	GPIO_SetBits( GPIO_BUZ , BUZ_PIN6 );
	
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input             : 			    
* Output         : None
* Return         : None
*******************************************************************************/

#endif //#if BUZ_EN>0

