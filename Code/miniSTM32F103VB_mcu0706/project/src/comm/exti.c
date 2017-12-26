//file: exti.c

#include "stm32f10x_lib.h"
#include "platform_config.h"

#include "includes.h"

void Init_ExtiGpio( void )
{

	GPIO_InitTypeDef GPIO_InitStructure;
	 /* ------Enable GPIO_key2 * 4 clock --------------------------*/
	 RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA  , ENABLE );
	 
	/* Configure GPIO Pin as input floating */
	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_0 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
}

void Init_ExtiSet(u8 GPIO_PortSourceGPIO ,u8 GPIO_PinSource, u32 EXTI_line , FunctionalState NewStatus )
{
	EXTI_InitTypeDef EXTI_InitStructure;
	    /* Connect Key Button EXTI Line to Key Button GPIO Pin */
	GPIO_EXTILineConfig( GPIO_PortSourceGPIO,  GPIO_PinSource );

	/* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
	EXTI_InitStructure.EXTI_Line = EXTI_line ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
}
	
void Init_ExtiNVIC(u8 IRQChannel , FunctionalState NewStatus )
{
	  NVIC_InitTypeDef NVIC_InitStructure;
	  
	    /* Configure one bit for preemption priority */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
	 /* Enable the EXTI0 Interrupt PC0*/
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2 ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = NewStatus;
	NVIC_Init(&NVIC_InitStructure);
	
}
void Exti
void Init_Exti( void )
{

	Init_ExtiNVIC(EXTI0_IRQChannel , ENABLE );
	Init_ExtiGpio( );
	Init_ExtiSet( GPIO_PortSourceGPIOA ,  GPIO_PinSource0 , EXTI_Line0, ENABLE );
	
}

int PluseCnt = 0 ;

void ExtiTest(void)
{
	Init_Exti( );
	while(1)
	{
		
		Delaynus(10);
	}
}

