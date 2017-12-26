#include "global.h"

void Platform_Init(void)
{
    RCC_Configuration();
    GPIO_Configuration();
    NVIC_Configuration();
	Timer_Configuration();
	USART_Configuration();			  
	EXTI_Configuration();
    delay_init(72);

	RS485_1_RX;				 //RS485 receive mode
	RS485_2_RX;				 //RS485 receive mode
   
//	IWDG_Configuration(781); //��ʼ���������Ź�5s

}
/*initialize the system clock*/
void RCC_Configuration(void)
{
    RCC_ClocksTypeDef RCC_ClockFreq;
    SystemInit();
    RCC_GetClocksFreq(&RCC_ClockFreq);

}
/*initialize the priority of interruptions used*/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

	/*Configure one bit for preemption priority*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	

    /*UART1*/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /*UART2*/
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /*TIM2*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}
void IWDG_Configuration(u16 time)
{
	/* д��0x5555,�����������Ĵ���д�빦�� */
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	/* ����ʱ�ӷ�Ƶ,40K/256=156HZ(6.4ms)*/
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	
	/* ι��ʱ�� 5s/6.4MS=781 .ע�ⲻ�ܴ���0xfff*/
	IWDG_SetReload(time);
	
	/* ι��*/
	IWDG_ReloadCounter();
	
	/* ʹ�ܹ���*/
	IWDG_Enable();
}
