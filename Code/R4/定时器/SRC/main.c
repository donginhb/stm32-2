//
/*******************************************************************************
*  �������ܣ���ʱ��1��ʱ1s
*  ��дʱ�䣺2010.12.23
*  ��    �ߣ��������
*******************************************************************************/

#include "stm32f10x_lib.h"


ErrorStatus HSEStartUpStatus;

/* �������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void TIM1_Configuration(void);
void WWDG_Configuration(void);
void Delay(vu32 nCount); 
void Delayms (vu32 m); 

/* �������� ----------------------------------------------*/

u8 m;
 
/*
********************************************************************************
** �������� �� main(void)
** �������� �� ������
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
int main(void)

{
  RCC_Configuration();
  GPIO_Configuration();
  USART1_Configuration();
  TIM1_Configuration(); 
  NVIC_Configuration();			   	 
  while(1)
  {
  
   Delayms(300);

  }    
}

/*
********************************************************************************
** �������� �� RCC_Configuration(void)
** �������� �� ʱ�ӳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void RCC_Configuration(void)
{   
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
      
}

/*
********************************************************************************
** �������� �� GPIO_Configuration(void)
** �������� �� �˿ڳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );
 
   /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //	ѡ�йܽ�9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //ѡ�йܽ�10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //ѡ��A�˿�

 
}


/*
********************************************************************************
** �������� �� USART1_Configuration(void)
** �������� �� ����1��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void USART1_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// ʱ�ӵ͵�ƽ�
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// ʱ�ӵ͵�ƽ
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// ʱ�ӵڶ������ؽ������ݲ���
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// ���һλ���ݵ�ʱ�����岻��SCLK���
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART1, &USART_ClockInitStructure);					// ʱ�Ӳ�����ʼ������
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // ������Ϊ��115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART1, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//ʹ��USART1�ж�Դ
USART_Cmd(USART1, ENABLE);							//USART1�ܿ��أ����� 


}

/*
********************************************************************************
** �������� �� TIM1_Configuration(void)
** �������� �� ��ʱ��1��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void TIM1_Configuration(void)
{
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
   /* Time Base configuration */
  TIM_DeInit(TIM1);
  TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //����Ԥ��Ƶ����Ƶϵ��71����APB2=72M, TIM1_CLK=72/72=1MHz ��
                                                               //����ȡֵ������0x0000��0xFFFF֮��
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���ģʽ
  //TIM1_TimeBaseStructure.TIM_Period = 1000;	               // 1ms��ʱ�����������ϼ�����1000����������¼�������ֵ����
  TIM_TimeBaseStructure.TIM_Period = 1000*10;	               // 15ms��ʱ	 ����ȡֵ������0x0000��0xFFFF֮��
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;			   //�����˶�ʱ��ʱ�ӷָ
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;		  // ���������ڼ�����ֵ������ȡֵ������0x00��0xFF֮�䡣

  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);	         // ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
   
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);      //���жϣ�����һ�����жϺ����������ж�   
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ��TIM1�ж�Դ 
   
  TIM_Cmd(TIM1, ENABLE); 		             //TIM1�ܿ��أ�����
 
}

 /*
********************************************************************************
** �������� �� TIM1_UP_IRQHandler(void)
** �������� �� ��ʱ��1�ж�
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/ 
void TIM1_UP_IRQHandler(void)
{	
	m++;
	if(m>=100)
    {
		m=0;
		USART_SendData(USART1, 0x55);
	}
	
    TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //���ж�

}


/*
********************************************************************************
** �������� �� NVIC_Configuration(void)
** �������� �� �жϳ�ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure;  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQChannel;    //�����¼� 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //��Ӧ���ȼ�2 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж� 
  NVIC_Init(&NVIC_InitStructure);                             //д������ 

  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;		  //�����¼�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  //��ռ���ȼ�0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		  //��Ӧ���ȼ�5
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //�����ж�
  NVIC_Init(&NVIC_InitStructure);							  //д������

}

 /*
********************************************************************************
** �������� �� WWDG_Configuration(void)
** �������� �� ���Ź���ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void WWDG_Configuration(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
  	
  WWDG_SetPrescaler(WWDG_Prescaler_8);	              //  WWDG clock counter = (PCLK1/4096)/8 = 244 Hz (~4 ms)  
  WWDG_SetWindowValue(0x41);		                 // Set Window value to 0x41
  WWDG_Enable(0x50);		       // Enable WWDG and set counter value to 0x7F, WWDG timeout = ~4 ms * 64 = 262 ms 
  WWDG_ClearFlag();			       // Clear EWI flag
  WWDG_EnableIT();			       // Enable EW interrupt
}

/*
********************************************************************************
** �������� �� Delay(vu32 nCount)
** �������� �� ����ʱ����	  i=1;40us��ʱ
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/

 void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*
********************************************************************************
** �������� �� void Delayms(vu32 m)
** �������� �� ����ʱ����	 m=1,��ʱ1ms
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
 void Delayms(vu32 m)
{
  u32 i;
  
  for(; m != 0; m--)	
       for (i=0; i<50000; i++);
}

/*
********************************************************************************
** �������� �� WWDG_IRQHandler(void)
** �������� �� ������ǰ�����ж�
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/ 

void WWDG_IRQHandler(void)
{
  /* Update WWDG counter */
  WWDG_SetCounter(0x50);
	
  /* Clear EWI flag */
  WWDG_ClearFlag();
  
}

/*************����***************/
