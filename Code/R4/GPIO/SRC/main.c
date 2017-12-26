//
/*******************************************************************************
*  �������ܣ�GPIO���ܲ���
*  ��дʱ�䣺2010.12.22
*  ��    �ߣ��������
*******************************************************************************/

#include "stm32f10x_lib.h"


GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

#define	PA0_H	    GPIO_SetBits(GPIOA, GPIO_Pin_0)		 // PA0 �ߵ�ƽ
#define	PA0_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_0)	 // PA0 �͵�ƽ

#define	PA1_H	    GPIO_SetBits(GPIOA, GPIO_Pin_1)		 // PA1 �ߵ�ƽ
#define	PA1_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_1)	 // PA1 �͵�ƽ  

#define	PA2_H	    GPIO_SetBits(GPIOA, GPIO_Pin_2)		 // PA2 �ߵ�ƽ
#define	PA2_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_2)	 // PA2 �͵�ƽ 

#define	PA3_H	    GPIO_SetBits(GPIOA, GPIO_Pin_3)		 // PA3 �ߵ�ƽ
#define	PA3_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_3)	 // PA3 �͵�ƽ

#define	PA4_H	    GPIO_SetBits(GPIOA, GPIO_Pin_4)		 // PA4 �ߵ�ƽ
#define	PA4_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_4)	 // PA4 �͵�ƽ  

#define	PA5_H	    GPIO_SetBits(GPIOA, GPIO_Pin_5)		 // PA5 �ߵ�ƽ
#define	PA5_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_5)	 // PA5 �͵�ƽ

#define	PA6_H	    GPIO_SetBits(GPIOA, GPIO_Pin_6)		 // PA6 �ߵ�ƽ
#define	PA6_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_6)	 // PA6 �͵�ƽ

#define	PA7_H	    GPIO_SetBits(GPIOA, GPIO_Pin_7)		 // PA7 �ߵ�ƽ
#define	PA7_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_7)	 // PA7 �͵�ƽ  

#define	PA8_H	    GPIO_SetBits(GPIOA, GPIO_Pin_8)		 // PA8 �ߵ�ƽ
#define	PA8_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_8)	 // PA8 �͵�ƽ

#define	PA9_H	    GPIO_SetBits(GPIOA, GPIO_Pin_9)		 // PA9 �ߵ�ƽ
#define	PA9_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_9)	 // PA9 �͵�ƽ

#define	PA10_H	    GPIO_SetBits(GPIOA, GPIO_Pin_10)	 // PA10 �ߵ�ƽ
#define	PA10_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_10)	 // PA10 �͵�ƽ

#define	PA11_H	    GPIO_SetBits(GPIOA, GPIO_Pin_11)	 // PA11 �ߵ�ƽ
#define	PA11_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_11)	 // PA11 �͵�ƽ

#define	PA12_H	    GPIO_SetBits(GPIOA, GPIO_Pin_12)	 // PA10 �ߵ�ƽ
#define	PA12_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_12)	 // PA10 �͵�ƽ

#define	PB0_H	    GPIO_SetBits(GPIOB, GPIO_Pin_0)	     // PB0 �ߵ�ƽ
#define	PB0_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_0)	 // PB0�͵�ƽ

#define	PB1_H	    GPIO_SetBits(GPIOB, GPIO_Pin_1)	     // PB1 �ߵ�ƽ
#define	PB1_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_1)	 // PB1�͵�ƽ

#define	PB2_H	    GPIO_SetBits(GPIOB, GPIO_Pin_2)	     // PB2 �ߵ�ƽ
#define	PB2_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_2)	 // PB2�͵�ƽ

#define	PB5_H	    GPIO_SetBits(GPIOB, GPIO_Pin_5)	     // PB5 �ߵ�ƽ
#define	PB5_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_5)	 // PB5�͵�ƽ

#define	PB6_H	    GPIO_SetBits(GPIOB, GPIO_Pin_6)	     // PB6 �ߵ�ƽ
#define	PB6_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_6)	 // PB6�͵�ƽ

#define	PB7_H	    GPIO_SetBits(GPIOB, GPIO_Pin_7)	     // PB7 �ߵ�ƽ
#define	PB7_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_7)	 // PB7�͵�ƽ

#define	PB8_H	    GPIO_SetBits(GPIOB, GPIO_Pin_8)	     // PB8 �ߵ�ƽ
#define	PB8_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_8)	 // PB8�͵�ƽ

#define	PB9_H	    GPIO_SetBits(GPIOB, GPIO_Pin_9)	     // PB9 �ߵ�ƽ
#define	PB9_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_9)	 // PB9�͵�ƽ

#define	PB10_H	    GPIO_SetBits(GPIOB, GPIO_Pin_10)	 // PB10 �ߵ�ƽ
#define	PB10_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_10)	 // PB10�͵�ƽ

#define	PB11_H	    GPIO_SetBits(GPIOB, GPIO_Pin_11)	 // PB11 �ߵ�ƽ
#define	PB11_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_11)	 // PB11�͵�ƽ

#define	PB12_H	    GPIO_SetBits(GPIOB, GPIO_Pin_12)	  // PB12 �ߵ�ƽ
#define	PB12_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_12)	 // PB12�͵�ƽ

#define	PB13_H	    GPIO_SetBits(GPIOB, GPIO_Pin_13)	  // PB13 �ߵ�ƽ
#define	PB13_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_13)	 // PB13�͵�ƽ

#define	PB14_H	    GPIO_SetBits(GPIOB, GPIO_Pin_14)	 // PB14 �ߵ�ƽ
#define	PB14_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_14)	 // PB14�͵�ƽ

#define	PB15_H	    GPIO_SetBits(GPIOB, GPIO_Pin_15)	 // PB15 �ߵ�ƽ
#define	PB15_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_15)	 // PB15�͵�ƽ


#define	PC13_H	    GPIO_SetBits(GPIOC, GPIO_Pin_13)	 // PC13 �ߵ�ƽ
#define	PC13_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_13)	 // PC13�͵�ƽ






/* �������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
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
  
  NVIC_Configuration();
 
  //WWDG_Configuration();
 
 
 
  while(1)
  {
	PA0_L; PA1_L; PA2_L; PA3_L; PA4_L; PA5_L; PA6_L; PA7_L; PA8_L; PA9_L; PA10_L; PA11_L; PA12_L;
	PB0_L; PB1_L; PB2_L; PB5_L; PB6_L; PB7_L; PB8_L; PB9_L; PB10_L; PB11_L; PB12_L;	 PB13_L; PB14_L; PB15_L; 
	PC13_L; 

	Delayms(50);
	PA0_H; PA1_H; PA2_H; PA3_H; PA4_H; PA5_H; PA6_H; PA7_H; PA8_H; PA9_H; PA10_H; PA11_H; PA12_H;
	PB0_H; PB1_H; PB2_H; PB5_H; PB6_H; PB7_H; PB8_H; PB9_H; PB10_H; PB11_H; PB12_H;	 PB13_H; PB14_H; PB15_H; 
	PC13_H;
	
	Delayms(50);	
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
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE  );
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  |
                                GPIO_Pin_1  |
								GPIO_Pin_2  |
								GPIO_Pin_3  |
								GPIO_Pin_4  |
								GPIO_Pin_5  |
								GPIO_Pin_6  |
								GPIO_Pin_7  |
								GPIO_Pin_8  |
								GPIO_Pin_9  |
								GPIO_Pin_10 |
								GPIO_Pin_11 |
								GPIO_Pin_12 ;			
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // ѡ��A�˿�
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  |
                                GPIO_Pin_1  |
								GPIO_Pin_2  |
								GPIO_Pin_5  |
								GPIO_Pin_6  |
								GPIO_Pin_7  |
								GPIO_Pin_8  |
								GPIO_Pin_9  |
								GPIO_Pin_10 |
								GPIO_Pin_11 |
								GPIO_Pin_12 |
								GPIO_Pin_13 |
								GPIO_Pin_14 |
								GPIO_Pin_15 ;			
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 // ѡ��B�˿�
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;			
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // ѡ��C�˿�
    
  
 

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
