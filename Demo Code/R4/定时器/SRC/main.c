//
/*******************************************************************************
*  函数功能：定时器1定时1s
*  编写时间：2010.12.23
*  作    者：雁翎电子
*******************************************************************************/

#include "stm32f10x_lib.h"


ErrorStatus HSEStartUpStatus;

/* 函数申明 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void USART1_Configuration(void);
void TIM1_Configuration(void);
void WWDG_Configuration(void);
void Delay(vu32 nCount); 
void Delayms (vu32 m); 

/* 变量定义 ----------------------------------------------*/

u8 m;
 
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
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE  );
 
   /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //	选中管脚9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // 最高输出速率50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 // 选择A端口
    
  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;			  //选中管脚10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);				  //选择A端口

 
}


/*
********************************************************************************
** 函数名称 ： USART1_Configuration(void)
** 函数功能 ： 串口1初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void USART1_Configuration(void)
{

USART_InitTypeDef USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE  );

USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;			// 时钟低电平活动
USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;				// 时钟低电平
USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;				// 时钟第二个边沿进行数据捕获
USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;		// 最后一位数据的时钟脉冲不从SCLK输出
/* Configure the USART1 synchronous paramters */
USART_ClockInit(USART1, &USART_ClockInitStructure);					// 时钟参数初始化设置
																	 
USART_InitStructure.USART_BaudRate = 115200;						  // 波特率为：115200
USART_InitStructure.USART_WordLength = USART_WordLength_8b;			  // 8位数据
USART_InitStructure.USART_StopBits = USART_StopBits_1;				  // 在帧结尾传输1个停止位
USART_InitStructure.USART_Parity = USART_Parity_No ;				  // 奇偶失能
USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// 硬件流控制失能

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;		  // 发送使能+接收使能
/* Configure USART1 basic and asynchronous paramters */
USART_Init(USART1, &USART_InitStructure);
    
  /* Enable USART1 */
USART_ClearFlag(USART1, USART_IT_RXNE); 			//清中断，以免一启用中断后立即产生中断
USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);		//使能USART1中断源
USART_Cmd(USART1, ENABLE);							//USART1总开关：开启 


}

/*
********************************************************************************
** 函数名称 ： TIM1_Configuration(void)
** 函数功能 ： 定时器1初始化
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
********************************************************************************
*/
void TIM1_Configuration(void)
{
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE );
   /* Time Base configuration */
  TIM_DeInit(TIM1);
  TIM_TimeBaseStructure.TIM_Prescaler = 71;                   //设置预分频器分频系数71，即APB2=72M, TIM1_CLK=72/72=1MHz ，
                                                               //它的取值必须在0x0000和0xFFFF之间
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
  //TIM1_TimeBaseStructure.TIM_Period = 1000;	               // 1ms定时，计数器向上计数到1000后产生更新事件，计数值归零
  TIM_TimeBaseStructure.TIM_Period = 1000*10;	               // 15ms定时	 它的取值必须在0x0000和0xFFFF之间
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;			   //设置了定时器时钟分割，
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0x0;		  // 设置了周期计数器值，它的取值必须在0x00和0xFF之间。

  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);	         // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
   
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);      //清中断，以免一启用中断后立即产生中断   
  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //使能TIM1中断源 
   
  TIM_Cmd(TIM1, ENABLE); 		             //TIM1总开关：开启
 
}

 /*
********************************************************************************
** 函数名称 ： TIM1_UP_IRQHandler(void)
** 函数功能 ： 定时器1中断
** 输    入	： 无
** 输    出	： 无
** 返    回	： 无
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
	
    TIM_ClearITPendingBit(TIM1, TIM_FLAG_Update); //清中断

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
 
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQChannel;    //更新事件 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          //响应优先级2 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断 
  NVIC_Init(&NVIC_InitStructure);                             //写入设置 

  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQChannel;		  //更新事件
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	  //抢占优先级0 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;		  //响应优先级5
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //允许中断
  NVIC_Init(&NVIC_InitStructure);							  //写入设置

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
** 函数功能 ： 短延时函数	  i=1;40us延时
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
