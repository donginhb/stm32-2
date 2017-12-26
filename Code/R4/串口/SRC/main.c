//
/*******************************************************************************
*  �������ܣ����ڷ�������
*  ��дʱ�䣺2010.12.22
*  ��    �ߣ�����
*******************************************************************************/

#include "stm32f10x_lib.h"

GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/* �������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void USART2_Configuration(void);
void USART3_Configuration(void);
void USART4_Configuration(void);
void USART5_Configuration(void);
void WWDG_Configuration(void);
void Delay(u32 nTime);
void Delayms(vu32 m);  
/* �������� ----------------------------------------------*/


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
  USART2_Configuration();
  USART3_Configuration();
  //USART4_Configuration();  
  //USART5_Configuration();

  NVIC_Configuration();
 
  //WWDG_Configuration();
 
 
  while(1)
  {
		USART_SendData(USART1, 0x01);
		Delayms(10);
		USART_SendData(USART1, 0x02);
		Delayms(10);
		USART_SendData(USART1, 0x03);
		Delayms(10);
		USART_SendData(USART1, 0x04);
		Delayms(5);
		USART_SendData(USART2, 0x02);
		Delayms(5);
		USART_SendData(USART3, 0x03);
		Delayms(5);
		
		
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

  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //	ѡ�йܽ�2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
    
  /* Configure USART2 Rx (PA.03) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			  //ѡ�йܽ�3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //ѡ��A�˿�


  /* Configure USART3 Tx (PB.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //	ѡ�йܽ�10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 // ѡ��B�˿�
    
  /* Configure USART3 Rx (PB.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //ѡ�йܽ�11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);				  //ѡ��B�˿�

   /* Configure USART4 Tx (PC.10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //	ѡ�йܽ�10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // ѡ��C�˿�
    
  /* Configure USART4 Rx (PC.11) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;			  //ѡ�йܽ�11
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOC, &GPIO_InitStructure);				  //ѡ��C�˿�

   /* Configure USART5 Tx (PC.12) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //	ѡ�йܽ�12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // ѡ��C�˿�
    
  /* Configure USART5 Rx (PD.2) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;			  //ѡ�йܽ�2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);				  //ѡ��D�˿�


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

RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 |RCC_APB2Periph_USART1, ENABLE  );

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
** �������� �� USART2_Configuration(void)
** �������� �� ����2��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void USART2_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// ʱ�ӵ͵�ƽ�
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// ʱ�ӵ͵�ƽ
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// ʱ�ӵڶ������ؽ������ݲ���
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// ���һλ���ݵ�ʱ�����岻��SCLK���
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART2, &USART_ClockInitStructure);					// ʱ�Ӳ�����ʼ������
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // ������Ϊ��115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART2, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART2, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);		//ʹ��USART2�ж�Դ
USART_Cmd(USART2, ENABLE);							//USART2�ܿ��أ����� 
}


/*
********************************************************************************
** �������� �� USART3_Configuration(void)
** �������� �� ����3��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/
void USART3_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// ʱ�ӵ͵�ƽ�
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// ʱ�ӵ͵�ƽ
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// ʱ�ӵڶ������ؽ������ݲ���
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// ���һλ���ݵ�ʱ�����岻��SCLK���
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART3, &USART_ClockInitStructure);					// ʱ�Ӳ�����ʼ������
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // ������Ϊ��57600
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
/* Configure USART3 basic and asynchronous paramters */
USART_Init(USART3, &USART_InitStructure);
    
  /* Enable USART3 */
USART_ClearFlag(USART3, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);		//ʹ��USART3�ж�Դ
USART_Cmd(USART3, ENABLE);							//USART3�ܿ��أ����� 
}

/*
********************************************************************************
** �������� �� USART4_Configuration(void)
** �������� �� ����4��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/

void USART4_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE  );
													 
	USART_InitStructure.USART_BaudRate = 115200;						  // ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��
	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
	
	USART_Init(UART4, &USART_InitStructure);
	    
	 
	USART_ClearFlag(UART4, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
	USART_ITConfig(UART4,USART_IT_RXNE, ENABLE);		//ʹ��USART4�ж�Դ
	USART_Cmd(UART4, ENABLE);							//USART4�ܿ��أ����� 

 
}

/*
********************************************************************************
** �������� �� USART4_Configuration(void)
** �������� �� ����4��ʼ��
** ��    ��	�� ��
** ��    ��	�� ��
** ��    ��	�� ��
********************************************************************************
*/

void USART5_Configuration(void)
{

	
	USART_InitTypeDef USART_InitStructure;
    //USART_ClockInitTypeDef  USART_ClockInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE  );
													 
	USART_InitStructure.USART_BaudRate =115200;						  // ������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8λ����
	USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // ��֡��β����1��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;				  // ��żʧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// Ӳ��������ʧ��
	
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // ����ʹ��+����ʹ��
	
	USART_Init(UART5, &USART_InitStructure);
	    
	 
	USART_ClearFlag(UART5, USART_IT_RXNE); 			//���жϣ�����һ�����жϺ����������ж�
	USART_ITConfig(UART5,USART_IT_RXNE, ENABLE);		//ʹ��USART5�ж�Դ
	USART_Cmd(UART5, ENABLE);							//USART5�ܿ��أ����� 

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
 
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_Init(&NVIC_InitStructure);

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
** �������� �� ��ʱ����
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
