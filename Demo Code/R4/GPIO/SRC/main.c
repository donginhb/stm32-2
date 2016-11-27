//
/*******************************************************************************
*  函数功能：GPIO功能测试
*  编写时间：2010.12.22
*  作    者：雁翎电子
*******************************************************************************/

#include "stm32f10x_lib.h"


GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

#define	PA0_H	    GPIO_SetBits(GPIOA, GPIO_Pin_0)		 // PA0 高电平
#define	PA0_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_0)	 // PA0 低电平

#define	PA1_H	    GPIO_SetBits(GPIOA, GPIO_Pin_1)		 // PA1 高电平
#define	PA1_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_1)	 // PA1 低电平  

#define	PA2_H	    GPIO_SetBits(GPIOA, GPIO_Pin_2)		 // PA2 高电平
#define	PA2_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_2)	 // PA2 低电平 

#define	PA3_H	    GPIO_SetBits(GPIOA, GPIO_Pin_3)		 // PA3 高电平
#define	PA3_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_3)	 // PA3 低电平

#define	PA4_H	    GPIO_SetBits(GPIOA, GPIO_Pin_4)		 // PA4 高电平
#define	PA4_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_4)	 // PA4 低电平  

#define	PA5_H	    GPIO_SetBits(GPIOA, GPIO_Pin_5)		 // PA5 高电平
#define	PA5_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_5)	 // PA5 低电平

#define	PA6_H	    GPIO_SetBits(GPIOA, GPIO_Pin_6)		 // PA6 高电平
#define	PA6_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_6)	 // PA6 低电平

#define	PA7_H	    GPIO_SetBits(GPIOA, GPIO_Pin_7)		 // PA7 高电平
#define	PA7_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_7)	 // PA7 低电平  

#define	PA8_H	    GPIO_SetBits(GPIOA, GPIO_Pin_8)		 // PA8 高电平
#define	PA8_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_8)	 // PA8 低电平

#define	PA9_H	    GPIO_SetBits(GPIOA, GPIO_Pin_9)		 // PA9 高电平
#define	PA9_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_9)	 // PA9 低电平

#define	PA10_H	    GPIO_SetBits(GPIOA, GPIO_Pin_10)	 // PA10 高电平
#define	PA10_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_10)	 // PA10 低电平

#define	PA11_H	    GPIO_SetBits(GPIOA, GPIO_Pin_11)	 // PA11 高电平
#define	PA11_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_11)	 // PA11 低电平

#define	PA12_H	    GPIO_SetBits(GPIOA, GPIO_Pin_12)	 // PA10 高电平
#define	PA12_L	    GPIO_ResetBits(GPIOA, GPIO_Pin_12)	 // PA10 低电平

#define	PB0_H	    GPIO_SetBits(GPIOB, GPIO_Pin_0)	     // PB0 高电平
#define	PB0_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_0)	 // PB0低电平

#define	PB1_H	    GPIO_SetBits(GPIOB, GPIO_Pin_1)	     // PB1 高电平
#define	PB1_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_1)	 // PB1低电平

#define	PB2_H	    GPIO_SetBits(GPIOB, GPIO_Pin_2)	     // PB2 高电平
#define	PB2_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_2)	 // PB2低电平

#define	PB5_H	    GPIO_SetBits(GPIOB, GPIO_Pin_5)	     // PB5 高电平
#define	PB5_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_5)	 // PB5低电平

#define	PB6_H	    GPIO_SetBits(GPIOB, GPIO_Pin_6)	     // PB6 高电平
#define	PB6_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_6)	 // PB6低电平

#define	PB7_H	    GPIO_SetBits(GPIOB, GPIO_Pin_7)	     // PB7 高电平
#define	PB7_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_7)	 // PB7低电平

#define	PB8_H	    GPIO_SetBits(GPIOB, GPIO_Pin_8)	     // PB8 高电平
#define	PB8_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_8)	 // PB8低电平

#define	PB9_H	    GPIO_SetBits(GPIOB, GPIO_Pin_9)	     // PB9 高电平
#define	PB9_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_9)	 // PB9低电平

#define	PB10_H	    GPIO_SetBits(GPIOB, GPIO_Pin_10)	 // PB10 高电平
#define	PB10_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_10)	 // PB10低电平

#define	PB11_H	    GPIO_SetBits(GPIOB, GPIO_Pin_11)	 // PB11 高电平
#define	PB11_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_11)	 // PB11低电平

#define	PB12_H	    GPIO_SetBits(GPIOB, GPIO_Pin_12)	  // PB12 高电平
#define	PB12_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_12)	 // PB12低电平

#define	PB13_H	    GPIO_SetBits(GPIOB, GPIO_Pin_13)	  // PB13 高电平
#define	PB13_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_13)	 // PB13低电平

#define	PB14_H	    GPIO_SetBits(GPIOB, GPIO_Pin_14)	 // PB14 高电平
#define	PB14_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_14)	 // PB14低电平

#define	PB15_H	    GPIO_SetBits(GPIOB, GPIO_Pin_15)	 // PB15 高电平
#define	PB15_L	    GPIO_ResetBits(GPIOB, GPIO_Pin_15)	 // PB15低电平


#define	PC13_H	    GPIO_SetBits(GPIOC, GPIO_Pin_13)	 // PC13 高电平
#define	PC13_L	    GPIO_ResetBits(GPIOC, GPIO_Pin_13)	 // PC13低电平






/* 函数申明 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void WWDG_Configuration(void);
void Delay(u32 nTime); 
void Delayms(vu32 m); 
/* 变量定义 ----------------------------------------------*/


/*
********************************************************************************
** 函数名称 ： main(void)
** 函数功能 ： 主函数
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
** 函数名称 ： RCC_Configuration(void)
** 函数功能 ： 时钟初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
** 函数名称 ： GPIO_Configuration(void)
** 函数功能 ： 端口初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口
    
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
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);				 // 选择B端口
    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;			
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				 // 选择C端口
    
  
 

}




/*
********************************************************************************
** 函数名称 ： NVIC_Configuration(void)
** 函数功能 ： 中断初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
** 函数名称 ： WWDG_Configuration(void)
** 函数功能 ： 看门狗初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
** 函数名称 ： Delay(vu32 nCount)
** 函数功能 ： 延时函数
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
 void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}


/*
********************************************************************************
** 函数名称 ： void Delayms(vu32 m)
** 函数功能 ： 长延时函数	 m=1,延时1ms
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
** 函数名称 ： WWDG_IRQHandler(void)
** 函数功能 ： 窗口提前唤醒中断
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/ 

void WWDG_IRQHandler(void)
{
  /* Update WWDG counter */
  WWDG_SetCounter(0x50);
	
  /* Clear EWI flag */
  WWDG_ClearFlag();
  
}

/*************结束***************/
